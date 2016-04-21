#pragma once
#include "UWB2WayMultiRange.h"

using ait::UWB2WayMultiRange;

const char* const UWB2WayMultiRange::RANGING_STATUS_MESSAGES[] = {
    "SUCCESS",
    "NO_MASTER_REQUEST_1",
    "NO_SLAVE_REPLY",
    "NO_MASTER_REQUEST_2",
    "NO_SLAVE_REPORT",
    "OTHER",
};

UWB2WayMultiRange::UWB2WayMultiRange(uint8_t address)
: UWBProtocol(address), moduleCounter_(0)
{
    timer_.start();

};

UWB2WayMultiRange::~UWB2WayMultiRange() {
	raw_result_.timestamp_master_request_1.clear();
	raw_result_.timestamp_master_request_2.clear();
	raw_result_.timestamp_slave_reply.clear();

	dw_vector_.clear();
}

void UWB2WayMultiRange::addModule(DW1000* dw_ptr)
{
 
    dw_vector_.push_back(dw_ptr);

    //result_.stats.push_back(ReceptionStats());
    raw_result_.timestamp_master_request_1.push_back(0);
    raw_result_.timestamp_slave_reply.push_back(0);
    raw_result_.timestamp_master_request_2.push_back(0);
    //raw_result_.stats.push_back(ReceptionStats());

    moduleCounter_++;
}

int UWB2WayMultiRange::getNumOfModules() const
{
	return moduleCounter_;
}

const DW1000* UWB2WayMultiRange::getModule(int module_index) const
{
    return dw_vector_.at(module_index);
}

DW1000* UWB2WayMultiRange::getModule(int module_index)
{
    return dw_vector_.at(module_index);
}

bool UWB2WayMultiRange::receiveFramesBlocking(std::vector<DW1000*>& dw_array, float timeout, uint64_t* timestamp_recv, ReceptionStats* stats)
{
    return true;
}

bool UWB2WayMultiRange::receiveFramesBlocking(std::vector<DW1000*>& dw_array, uint8_t type, float timeout, uint64_t* timestamp_recv, ReceptionStats* stats)
{
    return true;
}

const UWB2WayMultiRange::RawRangingResult& UWB2WayMultiRange::measureTimesOfFlight(uint8_t remote_address, float timeout, ReceptionStats* stats)
{
    raw_result_.status = OTHER;
    strcpy(raw_result_.status_description, "");

    raw_result_.remote_address = remote_address;
    raw_result_.tracker_address = this->getAddress();

    DW1000* primary_dw = dw_vector_.front();
    

    ReceptionStats* stats1;
    ReceptionStats* stats2;
    if (stats == NULL)
    {
        stats1 = NULL;
        stats2 = NULL;
    }
    else
    {
        stats1 = &stats[0];
        stats2 = &stats[1];
    }

    
    // Reset transmitter on all modules, start receiver
    //WAIT AFTER!!! (No idea why)
    for (int i = 0; i < moduleCounter_; ++i)
    {
        dw_vector_.at(i)->stopTRX();
        dw_vector_.at(i)->startRX();
    }
    wait_us(100);

    float timeout_time = timer_.read() + timeout;

    // Sending Master Request 1, RX is re-enabled!
    //DEBUG_PRINTF_VA("Sending master request 1 to address %d...\r\n", remote_address);
    bool send_status = sendRangingFrameBlocking(primary_dw, remote_address, MASTER_REQUEST_1, timeout_time - timer_.read(), &raw_result_.timestamp_master_request_1.at(0));
    if (!send_status)
    {
        ERROR_PRINTF("Unable to send master request 1 within timeout\r\n");
        raw_result_.status = NO_MASTER_REQUEST_1;
        return raw_result_;
    }
    
    //Receive Master Request 1 on secondary Modules
    //DEBUG_PRINTF("Waiting for master request 1 on secondaries ...\r\n");
    for (int i = 1; i < moduleCounter_; ++i)
    {
        bool recv_status = receiveMasterFrameBlocking(dw_vector_.at(i), remote_address, MASTER_REQUEST_1, timeout_time - timer_.read(), &raw_result_.timestamp_master_request_1.at(i), NULL);
        if (!recv_status)
        {
            ERROR_PRINTF_VA("Unable to receive master request 1 on secondary module %d reply within timeout\r\n", i);
            raw_result_.status = OTHER;
            strcpy(raw_result_.status_description, "Unable to receive master request 1 on secondary module");
            return raw_result_;
        }
        //DEBUG_PRINTF_VA("timestamp_master_request_1[%d]: %lu\r\n", i, raw_result_.timestamp_master_request_1[i]);
    }

    // Waiting for slave reply on Master - RX is re-enabled after every received frame!
    //DEBUG_PRINTF("Waiting for slave reply ...\r\n");
    bool recv_status = receiveSlaveFrameBlocking(primary_dw, SLAVE_REPLY, timeout_time - timer_.read(), &raw_result_.timestamp_slave_reply.at(0), stats1);
    if (!recv_status)
    {
        ERROR_PRINTF("Unable to receive slave reply on Master within timeout\r\n");
        raw_result_.status = NO_SLAVE_REPLY;
        return raw_result_;
    }

    //Receive slave reply on secondary modules
    for (int i = 1; i < moduleCounter_; i++)
    {
        bool recv_status = receiveSlaveFrameBlocking(dw_vector_.at(i), SLAVE_REPLY, timeout_time - timer_.read(), &raw_result_.timestamp_slave_reply.at(i), NULL);
        if (!recv_status)
        {
            ERROR_PRINTF_VA("Unable to receive slave reply on secondary module %d reply within timeout\r\n", i);
            raw_result_.status = OTHER;
            strcpy(raw_result_.status_description, "Unable to receive slave reply for secondary module");
            return raw_result_;
        }
        //DEBUG_PRINTF_VA("timestamp_slave_reply[%d]: %lu\r\n", i, raw_result_.timestamp_slave_reply[i]);
    }

    // Sending master request 2
    //Calculate the timestamp for the transmission based on the reception timestamp.
    raw_result_.timestamp_master_request_2.at(0) = raw_result_.timestamp_slave_reply[0] + ANSWER_DELAY_TIMEUNITS;
    send_status = sendDelayedRangingFrameBlocking(primary_dw, remote_address, MASTER_REQUEST_2, timeout_time - timer_.read(), &raw_result_.timestamp_master_request_2.at(0));
    if (!send_status)
    {
        ERROR_PRINTF("Unable to send master request 2 within timeout\r\n");
        raw_result_.status = NO_MASTER_REQUEST_2;
        return raw_result_;
    }

    //Receiving master request 2 on secondary modules
    for (int i = 1; i < moduleCounter_; ++i)
    {
        bool recv_status = receiveMasterFrameBlocking(dw_vector_.at(i), remote_address, MASTER_REQUEST_2, timeout_time - timer_.read(), &raw_result_.timestamp_master_request_2.at(i), NULL);
        if (!recv_status)
        {
            ERROR_PRINTF_VA("Unable to receive master request 2 on secondary module %d reply within timeout\r\n", i);
            raw_result_.status = OTHER;
            strcpy(raw_result_.status_description, "Unable to receive master request 2 for secondary module");
            return raw_result_;
        }
        //DEBUG_PRINTF_VA("timestamp_master_request_2[%d]: %lu\r\n", i, raw_result_.timestamp_master_request_2[i]);
    }

    for (int i = 0; i < moduleCounter_; ++i)
    {
        correctTimestamps(&raw_result_.timestamp_master_request_1.at(i), &raw_result_.timestamp_slave_reply.at(i), &raw_result_.timestamp_master_request_2.at(i));
    }

    // Waiting for slave report
    recv_status = receiveSlaveFrameBlocking(primary_dw, SLAVE_REPORT, timeout_time - timer_.read(), NULL, stats2);
    if (!recv_status)
    {
        ERROR_PRINTF("Unable to receive slave report within timeout\r\n");
        raw_result_.status = NO_SLAVE_REPORT;
        return raw_result_;
    }

    raw_result_.timeDiffSlave = receivedFrame_.timediff_slave;
    raw_result_.timestamp_master_request_1_recv = receivedFrame_.timestamp_master_request_1_recv;
    raw_result_.timestamp_slave_reply_send = receivedFrame_.timestamp_slave_reply_send;
    raw_result_.timestamp_master_request_2_recv = receivedFrame_.timestamp_master_request_2_recv;

#if _DEBUG
//    For debugging ranging only
//    DEBUG_PRINTF_VA("timestamp_master_request_1_recv: %lu\r\n", receivedFrame_.timestamp_master_request_1_recv);
//    DEBUG_PRINTF_VA("timestamp_slave_reply_send: %lu\r\n", receivedFrame_.timestamp_slave_reply_send);
//    DEBUG_PRINTF_VA("timestamp_master_request_2_recv: %lu\r\n", receivedFrame_.timestamp_master_request_2_recv);
//    for (int i = 0; i < dw_array_.size(); ++i)
//    {
//        DEBUG_PRINTF_VA("timestamp_master_request_1[%d]: %lu\r\n", i, raw_result_.timestamp_master_request_1[i]);
//        DEBUG_PRINTF_VA("timestamp_slave_reply[%d]: %lu\r\n", i, raw_result_.timestamp_slave_reply[i]);
//        DEBUG_PRINTF_VA("timestamp_master_request_2[%d]: %lu\r\n", i, raw_result_.timestamp_master_request_2[i]);
//    }
//    DEBUG_PRINTF("\r\n\r\n");
//    wait_ms(1000);
#endif

#if _DEBUG
//    For debugging ranging only
//    DEBUG_PRINTF_VA("report.timestamp_master_request_1: %lu\r\n", receivedFrame_.timestamp_master_request_1_recv);
//    DEBUG_PRINTF_VA("report.timestamp_slave_reply: %lu\r\n", receivedFrame_.timestamp_slave_reply_send);
//    DEBUG_PRINTF_VA("report.timestamp_master_request_2: %lu\r\n", receivedFrame_.timestamp_master_request_2_recv);
//    DEBUG_PRINTF_VA("timestamp_master_request_1: %lu\r\n", timestamp_master_request_1);
//    DEBUG_PRINTF_VA("timestamp_slave_reply: %lu\r\n", timestamp_slave_reply);
//    DEBUG_PRINTF_VA("timestamp_master_request_2: %lu\r\n", timestamp_master_request_2);
//    DEBUG_PRINTF_VA("timediff_master: %ld\r\n", timediff_master);
//    DEBUG_PRINTF_VA("timediff_slave: %ld\r\n", timediff_slave);
//    DEBUG_PRINTF_VA("tof: %ld\r\n", tof);
//    DEBUG_PRINTF_VA("range: %f\r\n", range);
//    DEBUG_PRINTF("\r\n");
//    DEBUG_PRINTF("\r\n\r\n");
//    wait_ms(1000);
#endif

#if _DEBUG
//    For debugging timing of individual steps only
//    int time_end_us = timer_.read_us();
//    int time_elapsed_us = time_end_us - time_begin_us;
//    int time_elapsed_ms = time_elapsed_us / 1000;
//    DEBUG_PRINTF_VA("Time elapsed for ranging: %d ms (%d microseconds)\r\n", time_elapsed_ms, time_elapsed_us);
//    DEBUG_PRINTF_VA("t1 - t0: %d us\r\n", t1_us - time_begin_us);
//    DEBUG_PRINTF_VA("t2 - t1: %d us\r\n", t2_us - t1_us);
//    DEBUG_PRINTF_VA("t3 - t2: %d us\r\n", t3_us - t2_us);
//    DEBUG_PRINTF_VA("t4 - t3: %d us\r\n", t4_us - t3_us);
//    DEBUG_PRINTF_VA("t5 - t4: %d us\r\n", t5_us - t4_us);
//    DEBUG_PRINTF_VA("t6 - t5: %d us\r\n", t6_us - t5_us);
//    DEBUG_PRINTF_VA("t7 - t6: %d us\r\n", t7_us - t6_us);
//    DEBUG_PRINTF_VA("t8 - t7: %d us\r\n", t8_us - t7_us);
//    DEBUG_PRINTF_VA("t9 - t8: %d us\r\n", t9_us - t8_us);
//    DEBUG_PRINTF_VA("t10 - t9: %d us\r\n", time_end_us - t9_us);
//    DEBUG_PRINTF("\r\n\r\n");
//    wait_ms(1000);
#endif

    raw_result_.status = SUCCESS;
    return raw_result_;
}

//const UWB2WayMultiRange<N>::RangingResult& UWB2WayMultiRange<N>::measureTimeOfFlight(uint8_t remote_address, float timeout, ReceptionStats* stats)
//{
//#if _DEBUG
//    int time_begin_us = timer_.read_us();
//#endif
//
//    float timeout_time = timer_.read() + timeout;
//
//    result_.status = OTHER;
//
//    DW1000* primary_dw = dw_array_.front();
//
//    ReceptionStats* stats1;
//    ReceptionStats* stats2;
//    if (stats == NULL)
//    {
//        stats1 = NULL;
//        stats2 = NULL;
//    }
//    else
//    {
//        stats1 = &stats[0];
//        stats2 = &stats[1];
//    }
//
//    // Sending Master Request 1
////    DEBUG_PRINTF_VA("Sending master request 1 to address %d...\r\n", remote_address);
//    uint64_t timestamp_master_request_1;
//    bool send_status = sendRangingFrameBlocking(primary_dw, remote_address, MASTER_REQUEST_1, timeout_time - timer_.read(), &timestamp_master_request_1);
//    if (!send_status)
//    {
//        ERROR_PRINTF("Unable to send master request 1 within timeout\r\n");
//        result_.status = NO_MASTER_REQUEST_1;
//        return result_;
//    }
//
//#if _DEBUG
//    int t1_us = timer_.read_us();
//#endif
//
//    // Waiting for slave reply
//    //DEBUG_PRINTF("Waiting for slave reply ...\r\n");
//    uint64_t timestamp_slave_reply;
//    bool recv_status = receiveFrameBlocking(primary_dw, SLAVE_REPLY, timeout_time - timer_.read(), &timestamp_slave_reply, stats1);
//    if (!recv_status)
//    {
//        ERROR_PRINTF("Unable to receive slave reply within timeout\r\n");
//        result_.status = NO_SLAVE_REPLY;
//        return result_;
//    }
//
//#if _DEBUG
//    int t2_us = timer_.read_us();
//#endif
//
//    // Sending master request 2
////    DEBUG_PRINTF_VA("Sending master request 2 to address %d...\r\n", remote_address);
//    uint64_t timestamp_master_request_2 = timestamp_slave_reply + ANSWER_DELAY_TIMEUNITS;
//    send_status = sendDelayedRangingFrameBlocking(primary_dw, remote_address, MASTER_REQUEST_2, timeout_time - timer_.read(), &timestamp_master_request_2);
//    //    send_status = sendFrameBlocking(destination, BEACON_RESPONSE, timeout);
//    if (!send_status)
//    {
//        ERROR_PRINTF("Unable to send master request 2 within timeout\r\n");
//        result_.status = NO_MASTER_REQUEST_2;
//        return result_;
//    }
//
//    correctTimestamps(&timestamp_master_request_1, &timestamp_slave_reply, &timestamp_master_request_2);
//
//#if _DEBUG
//    int t3_us = timer_.read_us();
//#endif
//
//    // Waiting for slave report
//    // printf("Waiting for slave report ...\r\n");
//    recv_status = receiveFrameBlocking(primary_dw, SLAVE_REPORT, timeout_time - timer_.read(), NULL, stats2);
//    if (!recv_status)
//    {
//        ERROR_PRINTF("Unable to receive slave report within timeout\r\n");
//        result_.status = NO_SLAVE_REPORT;
//        return result_;
//    }
//
//#if _DEBUG
//    int t4_us = timer_.read_us();
//#endif
//
//    // Calculation of the summand on the sending node/beacon
//    int64_t timediff_master = 2 * timestamp_slave_reply - timestamp_master_request_1 - timestamp_master_request_2;
//    // Calculation of the resulting sum of all four ToFs.
////    int64_t timediff_slave = receivedFrame_.timediff_slave;
//    int64_t timediff_slave = - 2 * receivedFrame_.timestamp_slave_reply_send + receivedFrame_.timestamp_master_request_1_recv + receivedFrame_.timestamp_master_request_2_recv;
//    int64_t timediff = timediff_master + timediff_slave;
//
//#if _DEBUG
//    int t5_us = timer_.read_us();
//#endif
//
//    float primary_tof = convertDWTimeunitsToMicroseconds(timediff) / 4.0f;
//    float primary_range = convertTimeOfFlightToDistance(primary_tof);
//
//    result_.primary_tof = primary_tof;
//    result_.primary_range = primary_range;
//
//#if _DEBUG
////    For debugging ranging only
////    DEBUG_PRINTF_VA("report.timestamp_master_request_1: %lu\r\n", receivedFrame_.timestamp_master_request_1_recv);
////    DEBUG_PRINTF_VA("report.timestamp_slave_reply: %lu\r\n", receivedFrame_.timestamp_slave_reply_send);
////    DEBUG_PRINTF_VA("report.timestamp_master_request_2: %lu\r\n", receivedFrame_.timestamp_master_request_2_recv);
////    DEBUG_PRINTF_VA("timestamp_master_request_1: %lu\r\n", timestamp_master_request_1);
////    DEBUG_PRINTF_VA("timestamp_slave_reply: %lu\r\n", timestamp_slave_reply);
////    DEBUG_PRINTF_VA("timestamp_master_request_2: %lu\r\n", timestamp_master_request_2);
////    DEBUG_PRINTF_VA("timediff_master: %ld\r\n", timediff_master);
////    DEBUG_PRINTF_VA("timediff_slave: %ld\r\n", timediff_slave);
////    DEBUG_PRINTF("\r\n");
////    DEBUG_PRINTF("\r\n\r\n");
////    wait_ms(1000);
//#endif
//
//#if _DEBUG
////    For debugging timing of individual steps only
////    int time_end_us = timer_.read_us();
////    int time_elapsed_us = time_end_us - time_begin_us;
////    int time_elapsed_ms = time_elapsed_us / 1000;
////    DEBUG_PRINTF_VA("Time elapsed for ranging: %d ms (%d microseconds)\r\n", time_elapsed_ms, time_elapsed_us);
////    DEBUG_PRINTF_VA("t1 - t0: %d us\r\n", t1_us - time_begin_us);
////    DEBUG_PRINTF_VA("t2 - t1: %d us\r\n", t2_us - t1_us);
////    DEBUG_PRINTF_VA("t3 - t2: %d us\r\n", t3_us - t2_us);
////    DEBUG_PRINTF_VA("t4 - t3: %d us\r\n", t4_us - t3_us);
////    DEBUG_PRINTF_VA("t5 - t4: %d us\r\n", t5_us - t4_us);
////    DEBUG_PRINTF_VA("t6 - t5: %d us\r\n", time_end_us - t5_us);
////    DEBUG_PRINTF("\r\n\r\n");
////    wait_ms(1000);
//#endif
//
//    result_.status = SUCCESS;
//    return result_;
//}

float UWB2WayMultiRange::convertDWTimeunitsToMicroseconds(int64_t dw_timeunits) const
{
    float time_us = dw_timeunits * DW1000::TIMEUNITS_TO_US;
    return time_us;
}

float UWB2WayMultiRange::convertTimeOfFlightToDistance(float tof) const
{
    float distance = SPEED_OF_LIGHT_IN_M_PER_US * tof;
    return distance;
}
