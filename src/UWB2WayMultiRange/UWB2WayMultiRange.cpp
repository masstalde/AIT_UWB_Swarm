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
: UWBProtocol(address)
{
    timer_.start();
}

void UWB2WayMultiRange::addModule(DW1000* dw_ptr)
{
 
    dw_array_.push_back(dw_ptr); 
    //result_.stats.push_back(ReceptionStats());
    raw_result_.timestamp_master_request_1.push_back(0);
    raw_result_.timestamp_slave_reply.push_back(0);
    raw_result_.timestamp_master_request_2.push_back(0);
    //raw_result_.stats.push_back(ReceptionStats());
}

int UWB2WayMultiRange::getNumOfModules() const
{
    return dw_array_.size();
}

const DW1000* UWB2WayMultiRange::getModule(int module_index) const
{
    return dw_array_[module_index];
}

DW1000* UWB2WayMultiRange::getModule(int module_index)
{
    return dw_array_[module_index];
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
#if _DEBUG
    int time_begin_us = timer_.read_us();
#endif

    raw_result_.status = OTHER;
    strcpy(raw_result_.status_description, "");

    DW1000* primary_dw = dw_array_.front();
    

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

    
    // Start receiving on secondary modules
    for (int i = 1; i < dw_array_.size(); ++i)
    {
        DW1000* dw_ptr = dw_array_[i];
        dw_ptr->clearReceivedFlag();
        dw_ptr->stopTRX();
        wait_us(10);
        dw_ptr->startRX();
    }

    float timeout_time = timer_.read() + timeout;


    // Sending Master Request 1
//    DEBUG_PRINTF_VA("Sending master request 1 to address %d...\r\n", remote_address);
    bool send_status = sendRangingFrameBlocking(primary_dw, remote_address, MASTER_REQUEST_1, timeout_time - timer_.read(), &raw_result_.timestamp_master_request_1[0]);
    if (!send_status)
    {
        ERROR_PRINTF("Unable to send master request 1 within timeout\r\n");
        raw_result_.status = NO_MASTER_REQUEST_1;
        return raw_result_;
    }
    

#if _DEBUG
    int t1_us = timer_.read_us();
#endif

    //DEBUG_PRINTF("Waiting for master request 1 on secondaries ...\r\n");
    for (int i = 1; i < dw_array_.size(); ++i)
    {
        DW1000* dw_ptr = dw_array_[i];
        bool recv_status = receiveFrameBlocking(dw_ptr, remote_address, MASTER_REQUEST_1, timeout_time - timer_.read(), &raw_result_.timestamp_master_request_1[i], NULL, false);
        if (!recv_status)
        {
            ERROR_PRINTF_VA("Unable to receive master request 1 on secondary module %d reply within timeout\r\n", i);
            raw_result_.status = OTHER;
            strcpy(raw_result_.status_description, "Unable to receive master request 1 on secondary module");
            return raw_result_;
        }
        //DEBUG_PRINTF_VA("timestamp_master_request_1[%d]: %lu\r\n", i, raw_result_.timestamp_master_request_1[i]);
    }
    
#if _DEBUG
    int t2_us = timer_.read_us();
#endif
    
    // Start receiving on all modules
    for (int i = 0; i < dw_array_.size(); ++i)
    {
        DW1000* dw_ptr = dw_array_[i];
        dw_ptr->clearReceivedFlag();
        dw_ptr->stopTRX();
        wait_us(1);
        dw_ptr->startRX();
        
    }


    // Waiting for slave reply
    //DEBUG_PRINTF("Waiting for slave reply ...\r\n");
    bool recv_status = receiveFrameBlocking(primary_dw, SLAVE_REPLY, timeout_time - timer_.read(), &raw_result_.timestamp_slave_reply[0], stats1);
    if (!recv_status)
    {
        ERROR_PRINTF("Unable to receive slave reply within timeout\r\n");
        raw_result_.status = NO_SLAVE_REPLY;
        return raw_result_;
    }

#if _DEBUG
    int t3_us = timer_.read_us();
#endif

    // Receive slave reply on secondary modules
    for (int i = 1; i < dw_array_.size(); ++i)
    {
        DW1000* dw_ptr = dw_array_[i];
        bool recv_status = receiveFrameBlocking(dw_ptr, SLAVE_REPLY, timeout_time - timer_.read(), &raw_result_.timestamp_slave_reply[i], NULL, false);
        if (!recv_status)
        {
            ERROR_PRINTF_VA("Unable to receive slave reply on secondary module %d reply within timeout\r\n", i);
            raw_result_.status = OTHER;
            strcpy(raw_result_.status_description, "Unable to receive slave reply for secondary module");
            return raw_result_;
        }
//        DEBUG_PRINTF_VA("timestamp_slave_reply[%d]: %lu\r\n", i, raw_result_.timestamp_slave_reply[i]);
    }

#if _DEBUG
    int t4_us = timer_.read_us();
#endif

    // Start receiving on secondary modules
    for (int i = 1; i < dw_array_.size(); ++i)
    {
        DW1000* dw_ptr = dw_array_[i];
        dw_ptr->clearReceivedFlag();
        dw_ptr->stopTRX();
        dw_ptr->startRX();
    }

    // Sending master request 2
//    DEBUG_PRINTF_VA("Sending master request 2 to address %d...\r\n", remote_address);
    raw_result_.timestamp_master_request_2[0] = raw_result_.timestamp_slave_reply[0] + ANSWER_DELAY_TIMEUNITS;
    send_status = sendDelayedRangingFrameBlocking(primary_dw, remote_address, MASTER_REQUEST_2, timeout_time - timer_.read(), &raw_result_.timestamp_master_request_2[0]);
    //    send_status = sendFrameBlocking(destination, BEACON_RESPONSE, timeout);
    if (!send_status)
    {
        ERROR_PRINTF("Unable to send master request 2 within timeout\r\n");
        raw_result_.status = NO_MASTER_REQUEST_2;
        return raw_result_;
    }

#if _DEBUG
    int t5_us = timer_.read_us();
#endif

    //DEBUG_PRINTF("Waiting for master request 2 on secondaries ...\r\n");
    for (int i = 1; i < dw_array_.size(); ++i)
    {
        DW1000* dw_ptr = dw_array_[i];
        bool recv_status = receiveFrameBlocking(dw_ptr, remote_address, MASTER_REQUEST_2, timeout_time - timer_.read(), &raw_result_.timestamp_master_request_2[i], NULL, false);
        if (!recv_status)
        {
            ERROR_PRINTF_VA("Unable to receive master request 2 on secondary module %d reply within timeout\r\n", i);
            raw_result_.status = OTHER;
            strcpy(raw_result_.status_description, "Unable to receive master request 2 for secondary module");
            return raw_result_;
        }
//        DEBUG_PRINTF_VA("timestamp_master_request_2[%d]: %lu\r\n", i, raw_result_.timestamp_master_request_2[i]);
    }

    for (int i = 0; i < dw_array_.size(); ++i)
    {
        correctTimestamps(&raw_result_.timestamp_master_request_1[i], &raw_result_.timestamp_slave_reply[i], &raw_result_.timestamp_master_request_2[i]);
    }

#if _DEBUG
    int t6_us = timer_.read_us();
#endif

    // Waiting for slave report
    // printf("Waiting for slave report ...\r\n");
    recv_status = receiveFrameBlocking(primary_dw, SLAVE_REPORT, timeout_time - timer_.read(), NULL, stats2);
    if (!recv_status)
    {
        ERROR_PRINTF("Unable to receive slave report within timeout\r\n");
        raw_result_.status = NO_SLAVE_REPORT;
        return raw_result_;
    }

#if _DEBUG
    int t7_us = timer_.read_us();
#endif

    raw_result_.timestamp_master_request_1_recv = receivedFrame_.timestamp_master_request_1_recv;
    raw_result_.timestamp_slave_reply_send = receivedFrame_.timestamp_slave_reply_send;
    raw_result_.timestamp_master_request_2_recv = receivedFrame_.timestamp_master_request_2_recv;

#if _DEBUG
    int t8_us = timer_.read_us();

    // Calculation of the summand on the sending node/beacon
    int64_t timediff_master = 2 * raw_result_.timestamp_slave_reply[0] - raw_result_.timestamp_master_request_1[0] - raw_result_.timestamp_master_request_2[0];
    // Calculation of the resulting sum of all four ToFs.
//    int64_t timediff_slave = receivedFrame_.timediff_slave;
    int64_t timediff_slave = receivedFrame_.timestamp_master_request_1_recv + receivedFrame_.timestamp_master_request_2_recv - 2 * receivedFrame_.timestamp_slave_reply_send;
    int64_t timediff = timediff_master + timediff_slave;

    int t9_us = timer_.read_us();
#endif

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

//const UWB2WayMultiRange::RangingResult& UWB2WayMultiRange::measureTimeOfFlight(uint8_t remote_address, float timeout, ReceptionStats* stats)
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
