#include "UWBSlave.h"

using ait::UWBSlave;

UWBSlave::UWBSlave(DW1000* dw_ptr, uint8_t address)
: UWBProtocol(address), dw_ptr_(dw_ptr)
{
    timer_.start();

    dw_ptr_->setCallbacks(this, &UWBSlave::receiveFrameCallback, &UWBSlave::sentFrameCallback);
}

const DW1000* UWBSlave::getModule() const
{
    return dw_ptr_;
}

DW1000* UWBSlave::getModule()
{
    return dw_ptr_;
}

void UWBSlave::startReceiving()
{
    dw_ptr_->startRX();
}

void UWBSlave::stopReceiving()
{
    dw_ptr_->startRX();
}

void UWBSlave::receiveFrameCallback()
{
	dw_ptr_->readRegister(DW1000_RX_BUFFER, 0, reinterpret_cast<uint8_t*>(&frame_), dw_ptr_->getFramelength());

    //DEBUG_PRINTF_VA("Received frame: address=%d, remote_address=%d, type=%d\r\n", frame_.address, frame_.remote_address, frame_.type);


    if (frame_.remote_address == address_)
    {
        uint8_t sender_address = frame_.address;
        uint64_t timestamp_recv = dw_ptr_->getRXTimestamp();

#if SLAVE_REPLY_WITH_STATS
        uint16_t std_noise = dw_ptr_->getStdNoise();
        uint16_t preamble_acc_count = dw_ptr_->getPACC();
        uint16_t first_path_index = dw_ptr_->getFPINDEX();
        uint16_t first_path_amp_1 = dw_ptr_->getFPAMPL1();
        uint16_t first_path_amp_2 = dw_ptr_->getFPAMPL2();
        uint16_t first_path_amp_3 = dw_ptr_->getFPAMPL3();
        uint16_t channel_impulse_response_power = dw_ptr_->getCIRPWR();
        uint8_t prf = dw_ptr_->getPRF();
#endif

        int64_t timediff_slave;

        switch (frame_.type)
        {
            case MASTER_REQUEST_1:
            	//sendRangingFrame(dw_ptr_, sender_address, SLAVE_REPLY);
            	DEBUG_PRINTF("\r\nReceived Master Request 1\r\n");
                sendDelayedRangingFrame(dw_ptr_, sender_address, SLAVE_REPLY, timestamp_recv + ANSWER_DELAY_TIMEUNITS);
            	//sendRangingFrame(dw_ptr_, sender_address, SLAVE_REPLY);
                master_request_1_timestamps_[sender_address] = timestamp_recv;
#if SLAVE_REPLY_WITH_STATS
                reception_stats_[sender_address][0].std_noise = std_noise;
                reception_stats_[sender_address][0].preamble_acc_count = preamble_acc_count;
                reception_stats_[sender_address][0].first_path_index = first_path_index;
                reception_stats_[sender_address][0].first_path_amp_1 = first_path_amp_1;
                reception_stats_[sender_address][0].first_path_amp_2 = first_path_amp_2;
                reception_stats_[sender_address][0].first_path_amp_3 = first_path_amp_3;
                reception_stats_[sender_address][0].channel_impulse_response_power = channel_impulse_response_power;
                reception_stats_[sender_address][0].prf = prf;
#endif
                break;
            case MASTER_REQUEST_2:
            	DEBUG_PRINTF("\r\nReceived Master Request 2\r\n");
                master_request_2_timestamps_[sender_address] = timestamp_recv;
                correctTimestamps(&master_request_1_timestamps_[sender_address], &slave_reply_timestamps_[sender_address], &master_request_2_timestamps_[sender_address]);

                timediff_slave = - 2 * static_cast<int64_t>(slave_reply_timestamps_[sender_address])
                    + master_request_1_timestamps_[sender_address] + master_request_2_timestamps_[sender_address];

#if SLAVE_REPLY_WITH_STATS
                reception_stats_[sender_address][1].std_noise = std_noise;
                reception_stats_[sender_address][1].preamble_acc_count = preamble_acc_count;
                reception_stats_[sender_address][1].first_path_index = first_path_index;
                reception_stats_[sender_address][1].first_path_amp_1 = first_path_amp_1;
                reception_stats_[sender_address][1].first_path_amp_2 = first_path_amp_2;
                reception_stats_[sender_address][1].first_path_amp_3 = first_path_amp_3;
                reception_stats_[sender_address][1].channel_impulse_response_power = channel_impulse_response_power;
                reception_stats_[sender_address][1].prf = prf;
#endif
                //TODO: Find better solution
                rangingFrame_.type = SLAVE_REPORT;
                sendReportFrame(dw_ptr_, sender_address, timediff_slave);
//                DEBUG_PRINTF_VA("timediff_slave %ld\r\n", timediff_slave);
                break;
        }
    }

    dw_ptr_->startRX();
}

void UWBSlave::sentFrameCallback()
{

    uint8_t remote_address = rangingFrame_.remote_address;
    uint8_t frame_type = rangingFrame_.type;
    DEBUG_PRINTF_VA("Sent slave reply type %i\r\n", frame_type);
    switch (frame_type)
    {
    case SLAVE_REPLY:
        slave_reply_timestamps_[remote_address] = dw_ptr_->getTXTimestamp();
//        DEBUG_PRINTF("Sent slave reply\r\n");
        break;
    }
}

void UWBSlave::checkForFrame(float timeout) {
    // Waiting for frame
//    DEBUG_PRINTF("Waiting for frame ...\r\n")
    uint64_t timestamp_recv;
    bool recv_status = receiveTrackerFrameBlocking(dw_ptr_, timeout, &timestamp_recv, NULL);
    if (!recv_status)
    {
        ERROR_PRINTF("Unable to receive frame within timeout\r\n");
        return;
    }

    switch (receivedFrame_.type) {
        case MASTER_REQUEST_1:
            handleMasterRequest1(timestamp_recv, reinterpret_cast<RangingFrame*>(&receivedFrame_), timeout);
            break;
        case MASTER_REQUEST_2:
            handleMasterRequest2(timestamp_recv, reinterpret_cast<RangingFrame*>(&receivedFrame_), timeout);
            break;
    }
}

void UWBSlave::handleMasterRequest1(uint64_t timestamp_recv, RangingFrame* frame, float timeout)
{
//    DEBUG_PRINTF_VA("Handling master request 1 from %d\r\n", frame->address);
    uint8_t remote_address = frame->address;
    master_request_1_timestamps_[remote_address] = timestamp_recv;
    // TODO
//    uint64_t sys_timestamp = dw_ptr_->getSYSTimestamp();
    uint64_t timestamp_slave_reply_send = timestamp_recv + ANSWER_DELAY_TIMEUNITS;
    bool send_status = sendDelayedRangingFrameBlocking(dw_ptr_, remote_address, SLAVE_REPLY, timeout, &timestamp_slave_reply_send);
    if (!send_status)
    {
        ERROR_PRINTF("Unable to send slave reply within timeout\r\n");
        return;
    }
    slave_reply_timestamps_[remote_address] = timestamp_slave_reply_send;
//    DEBUG_PRINTF_VA("sys_time: %f\r\n", sys_timestamp * DW1000::TIMEUNITS_TO_US);
//    DEBUG_PRINTF_VA("timestamp_recv: %f\r\n", timestamp_recv * DW1000::TIMEUNITS_TO_US);
//    DEBUG_PRINTF_VA("timestamp_slave_reply_send: %f\r\n", timestamp_slave_reply_send * DW1000::TIMEUNITS_TO_US);
//    DEBUG_PRINTF_VA("Slave sent delayed frame: address=%d, remote_address=%d, type=%d\r\n", rangingFrame_.address, rangingFrame_.remote_address, rangingFrame_.type);
}

void UWBSlave::handleMasterRequest2(uint64_t timestamp_recv, RangingFrame* frame, float timeout)
{
//    DEBUG_PRINTF_VA("Handling master request 2 from %d\r\n", frame->address);
    uint8_t remote_address = frame->address;
    master_request_2_timestamps_[remote_address] = timestamp_recv;
    
    correctTimestamps(&master_request_1_timestamps_[remote_address], &slave_reply_timestamps_[remote_address], &master_request_2_timestamps_[remote_address]);
    int64_t timediff_slave = - 2 * static_cast<int64_t>(slave_reply_timestamps_[receivedFrame_.address])
        + master_request_1_timestamps_[receivedFrame_.address] + master_request_2_timestamps_[receivedFrame_.address];

    reportFrame_.address = address_;
    reportFrame_.remote_address = remote_address;
    reportFrame_.type = SLAVE_REPORT;
    reportFrame_.timediff_slave =  timediff_slave;
    bool send_status = sendReportFrameBlocking(dw_ptr_, remote_address, timediff_slave, timeout);
    if (!send_status)
    {
        ERROR_PRINTF("Unable to send slave report within timeout\r\n");
        return;
    }
//    DEBUG_PRINTF_VA("Slave sent delayed frame: address=%d, remote_address=%d, type=%d\r\n", rangingFrame_.address, rangingFrame_.remote_address, rangingFrame_.type);
}
