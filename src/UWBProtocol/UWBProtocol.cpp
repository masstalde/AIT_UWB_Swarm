#include "UWBProtocol.h"

using ait::UWBProtocol;

UWBProtocol::UWBProtocol(uint8_t address)
: address_(address)
{
    timer_.start();
}

uint8_t UWBProtocol::getAddress() const
{
    return address_;
}

void UWBProtocol::sendRangingFrame(DW1000* dw_ptr, uint8_t remote_address, uint8_t type)
{
    rangingFrame_.address = address_;
    rangingFrame_.remote_address = remote_address;
    rangingFrame_.type = type;
    dw_ptr->sendFrame(reinterpret_cast<uint8_t*>(&rangingFrame_), sizeof(rangingFrame_));
}

void UWBProtocol::sendDelayedRangingFrame(DW1000* dw_ptr, uint8_t remote_address, uint8_t type, uint64_t timestamp_send)
{
    rangingFrame_.address = address_;
    rangingFrame_.remote_address = remote_address;
    rangingFrame_.type = type;
    dw_ptr->sendDelayedFrame(reinterpret_cast<uint8_t*>(&rangingFrame_), sizeof(rangingFrame_), timestamp_send);
}

void UWBProtocol::sendReportFrame(DW1000* dw_ptr, uint8_t remote_address, int64_t timediff_slave,
    uint64_t timestamp_master_request_1_recv,
    uint64_t timestamp_slave_reply_send,
    uint64_t timestamp_master_request_2_recv)
//void UWBProtocol::sendReportFrame(DW1000* dw_ptr, uint8_t remote_address, int64_t timediff_slave)
{
    reportFrame_.address = address_;
    reportFrame_.remote_address = remote_address;
    reportFrame_.type = SLAVE_REPORT;
    reportFrame_.timediff_slave = timediff_slave;
    reportFrame_.timestamp_master_request_1_recv = timestamp_master_request_1_recv;
    reportFrame_.timestamp_slave_reply_send = timestamp_slave_reply_send;
    reportFrame_.timestamp_master_request_2_recv = timestamp_master_request_2_recv;
    dw_ptr->clearSentFlag();
    dw_ptr->sendFrame(reinterpret_cast<uint8_t*>(&reportFrame_), sizeof(reportFrame_));
}

bool UWBProtocol::receiveAnyFrameBlocking(DW1000* dw_ptr, float timeout, uint64_t* timestamp_recv, ReceptionStats* stats)
{
    float time_before = timer_.read();
    bool status = false;
    // Polling
    while (!status && timer_.read() < time_before + timeout)
    {
        status = dw_ptr->hasReceivedFrame();
    }

    if (status)
    {
        uint16_t frame_length = dw_ptr->getFramelength();
        if (frame_length > sizeof(receivedFrame_))
        {
            ERROR_PRINTF_VA("Received frame is bigger than allowed: %d vs %d\r\n", frame_length, sizeof(receivedFrame_));
            return false;
        }
        dw_ptr->readRegister(DW1000_RX_BUFFER, 0, (uint8_t*)&receivedFrame_, frame_length);

        //DEBUG_PRINTF_VA("Received frame: address=%d, remote_address=%d, type=%d\r\n", receivedFrame_.address, receivedFrame_.remote_address, receivedFrame_.type);

        if (stats != NULL)
        {
            uint16_t std_noise = dw_ptr->getStdNoise();
            uint16_t preamble_acc_count = dw_ptr->getPACC();
            uint16_t first_path_index = dw_ptr->getFPINDEX();
            uint16_t first_path_amp_1 = dw_ptr->getFPAMPL1();
            uint16_t first_path_amp_2 = dw_ptr->getFPAMPL2();
            uint16_t first_path_amp_3 = dw_ptr->getFPAMPL3();
            uint16_t channel_impulse_response_power = dw_ptr->getCIRPWR();
            uint8_t prf = dw_ptr->getPRF();
            stats->std_noise = std_noise;
            stats->preamble_acc_count = preamble_acc_count;
            stats->first_path_index = first_path_index;
            stats->first_path_amp_1 = first_path_amp_1;
            stats->first_path_amp_2 = first_path_amp_2;
            stats->first_path_amp_3 = first_path_amp_3;
            stats->channel_impulse_response_power = channel_impulse_response_power;
            stats->prf = prf;
        }

        if (timestamp_recv != NULL)
        {
            *timestamp_recv = dw_ptr->getRXTimestamp();
        }

        //After receveing anything, RX re-enabled (flag clears automatically)
		dw_ptr->startRX();

    }

    return status;
}

bool UWBProtocol::receiveTrackerFrameBlocking(DW1000* dw_ptr, float timeout, uint64_t* timestamp_recv, ReceptionStats* stats)
{
    float time_before = timer_.read();
    while (timer_.read() - time_before < timeout)
    {
        bool recv_status = receiveAnyFrameBlocking(dw_ptr, timeout, timestamp_recv, stats);
        if (recv_status)
        {
            if (receivedFrame_.remote_address == address_)
            {
                return true;
            }
        }
    }
    return false;
}

bool UWBProtocol::receiveSlaveFrameBlocking(DW1000* dw_ptr, uint8_t type, float timeout, uint64_t* timestamp_recv, ReceptionStats* stats )
{
    float time_before = timer_.read();
    while (timer_.read() - time_before < timeout)
    {
        bool recv_status = receiveAnyFrameBlocking(dw_ptr, timeout, timestamp_recv, stats);
        if (recv_status)
        {
            if (receivedFrame_.remote_address == address_ && receivedFrame_.type == type)
            {
                return true;
            }
        }
    }
    return false;
}

bool UWBProtocol::receiveMasterFrameBlocking(DW1000* dw_ptr, uint8_t remote_address, uint8_t type, float timeout, uint64_t* timestamp_recv, ReceptionStats* stats )
{
    float time_before = timer_.read();
    while (timer_.read() - time_before < timeout)
    {
        bool recv_status = receiveAnyFrameBlocking(dw_ptr, timeout, timestamp_recv, stats);
        if (recv_status)
        {
            if (receivedFrame_.remote_address == remote_address && receivedFrame_.type == type)
            {
                return true;
            }
        }
    }
    return false;
}

bool UWBProtocol::sendFrameBlocking(DW1000* dw_ptr, uint8_t* frame, int frame_size, float timeout, uint64_t* timestamp_send)
{
    float time_before = timer_.read();
    bool status = false;

    dw_ptr->sendFrame(frame, frame_size);			//Send the frame and re-enable RX

    // Polling
    while (!status && timer_.read() < time_before + timeout)
    {
        status = dw_ptr->hasSentFrame();
    }
    if (status)
    {
    	//RangingFrame* ranging_frame = reinterpret_cast<RangingFrame*>(frame);
    	//DEBUG_PRINTF_VA("Sent frame: address=%d, remote_address=%d, type=%d\r\n", ranging_frame->address, ranging_frame->remote_address, ranging_frame->type);
        if (timestamp_send != NULL)
        {
            *timestamp_send = dw_ptr->getTXTimestamp();
        }
    }

    return status;
}

bool UWBProtocol::sendDelayedFrameBlocking(DW1000* dw_ptr, uint8_t* frame, int frame_size, float timeout, uint64_t* timestamp_send)
{

	float time_before = timer_.read();
	bool status = false;

    dw_ptr->sendDelayedFrame(frame, frame_size, *timestamp_send);

    // Polling
    while (!status && timer_.read() < time_before + timeout)
    {
        status = dw_ptr->hasSentFrame();
    }
    if (status)
    {
    	//DEBUG_PRINTF_VA("Sent delayed frame: address=%d, remote_address=%d, type=%d\r\n", ranging_frame->address, ranging_frame->remote_address, ranging_frame->type);
        if (timestamp_send != NULL)
        {
            *timestamp_send = dw_ptr->getTXTimestamp();
        }
    }
    return status;
}

bool UWBProtocol::sendRangingFrameBlocking(DW1000* dw_ptr, uint8_t remote_address, uint8_t type, float timeout, uint64_t* timestamp_send)
{
    rangingFrame_.address = address_;
    rangingFrame_.remote_address = remote_address;
    rangingFrame_.type = type;
    return sendFrameBlocking(dw_ptr, reinterpret_cast<uint8_t*>(&rangingFrame_), sizeof(rangingFrame_), timeout, timestamp_send);
}

bool UWBProtocol::sendReportFrameBlocking(DW1000* dw_ptr, uint8_t remote_address, int64_t timediff_slave, float timeout, uint64_t* timestamp_send)
{
    dw_ptr->clearSentFlag();
    reportFrame_.address = address_;
    reportFrame_.remote_address = remote_address;
    reportFrame_.type = SLAVE_REPORT;
    reportFrame_.timediff_slave = timediff_slave;
    return sendFrameBlocking(dw_ptr, reinterpret_cast<uint8_t*>(&reportFrame_), sizeof(reportFrame_), timeout, timestamp_send);
}

bool UWBProtocol::sendDelayedRangingFrameBlocking(DW1000* dw_ptr, uint8_t remote_address, uint8_t type, float timeout, uint64_t* timestamp_send)
{
    rangingFrame_.address = address_;
    rangingFrame_.remote_address = remote_address;
    rangingFrame_.type = type;
    return sendDelayedFrameBlocking(dw_ptr, reinterpret_cast<uint8_t*>(&rangingFrame_), sizeof(rangingFrame_), timeout, timestamp_send);
}

bool UWBProtocol::correctTimestamps(uint64_t* timestamp_master_request_1, uint64_t* timestamp_slave_reply, uint64_t* timestamp_master_request_2) const
{
    bool overflow;
    if (timestamp_master_request_1[0] > timestamp_slave_reply[0])
    {
        timestamp_slave_reply[0] += DW1000::CONST_2POWER40;
        timestamp_master_request_2[0] += DW1000::CONST_2POWER40;
        overflow = true;
    }
    else if (timestamp_slave_reply[0] > timestamp_master_request_2[0])
    {
        timestamp_master_request_2[0] += DW1000::CONST_2POWER40;
        overflow = true;
    }
    else
    {
        overflow = false;
    }
    return overflow;
}
