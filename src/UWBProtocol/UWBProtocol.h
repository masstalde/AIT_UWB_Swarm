#pragma once

#include "settings.h"

#include <mbed.h>
#include <DW1000.h>

namespace ait
{
    
class UWBProtocol
{
public:
    UWBProtocol(uint8_t address);

    uint8_t getAddress() const;

    // Attributes packed and aligned(1) ensure that the structure is not padded and not aligned in memory.
    struct __attribute__((packed, aligned(1))) ReceptionStats
    {
        uint16_t std_noise;
        uint16_t preamble_acc_count;
        uint16_t first_path_index;
        uint16_t first_path_amp_1;
        uint16_t first_path_amp_2;
        uint16_t first_path_amp_3;
        uint16_t channel_impulse_response_power;
        uint8_t prf;
    };

protected:
    uint8_t address_;
    Timer timer_;

    // Response delay of the ranging. This should be equal on both sides and has to be bigger than the processing time of the frame on each node.
    // For 110kbps, 2500 is OK. For 6.8Mbps, 900 is OK.
#ifdef ANSWER_DELAY_US_MASTER
    const static int ANSWER_DELAY_US = ANSWER_DELAY_US_MASTER;
#elif defined ANSWER_DELAY_US_SLAVE
    const static int ANSWER_DELAY_US = ANSWER_DELAY_US_SLAVE;
#else
    const int ANSWER_DELAY_US = 2500;
#endif
    const float ANSWER_DELAY_TIMEUNITS = ANSWER_DELAY_US * DW1000::US_TO_TIMEUNITS;

    const static int NUM_OF_UWB_ADDRESSES = 256;

    enum FrameType
    {
        MASTER_REQUEST_1 = 1,
        SLAVE_REPLY,
        MASTER_REQUEST_2,
        SLAVE_REPORT,
    };

    // Attributes packed and aligned(1) ensure that the structure is not padded and not aligned in memory.
    struct __attribute__((packed, aligned(1))) RangingFrame
    {
        uint8_t address;
        uint8_t remote_address;
        uint8_t type;
    };

    // Attributes packed and aligned(1) ensure that the structure is not padded and not aligned in memory.
    struct __attribute__((packed, aligned(1))) ReportRangingFrame : RangingFrame
    {
        int64_t timediff_slave;
        int64_t timestamp_master_request_1_recv;
        int64_t timestamp_slave_reply_send;
        int64_t timestamp_master_request_2_recv;
#if SLAVE_REPLY_WITH_STATS
        ReceptionStats stats1;
        ReceptionStats stats2;
#endif
    };

    RangingFrame rangingFrame_;
    ReportRangingFrame receivedFrame_;
    ReportRangingFrame reportFrame_;

    void sendRangingFrame(DW1000* dw_ptr, uint8_t remote_address, uint8_t type);
    void sendDelayedRangingFrame(DW1000* dw_ptr, uint8_t remote_address, uint8_t type, uint64_t timestamp_send);

    void sendReportFrame(DW1000* dw_ptr, uint8_t remote_address, int64_t timediff_slave,
    	    uint64_t timestamp_master_request_1_recv,
    	    uint64_t timestamp_slave_reply_send,
    	    uint64_t timestamp_master_request_2_recv);

    bool receiveAnyFrameBlocking(DW1000* dw_ptr, float timeout, uint64_t* timestamp_recv = NULL, ReceptionStats* stats = NULL);

    bool receiveTrackerFrameBlocking(DW1000* dw_ptr, float timeout, uint64_t* timestamp_recv = NULL, ReceptionStats* stats = NULL);
    bool receiveSlaveFrameBlocking(DW1000* dw_ptr, uint8_t type, float timeout, uint64_t* timestamp_recv = NULL, ReceptionStats* stats = NULL);
    bool receiveMasterFrameBlocking(DW1000* dw_ptr, uint8_t remote_address, uint8_t type, float timeout, uint64_t* timestamp_recv = NULL, ReceptionStats* stats = NULL);

    bool sendFrameBlocking(DW1000* dw_ptr, uint8_t* frame, int frame_size, float timeout, uint64_t* timestamp_send = NULL);
    bool sendDelayedFrameBlocking(DW1000* dw_ptr, uint8_t* frame, int frame_size, float timeout, uint64_t* timestamp_send);

    bool sendRangingFrameBlocking(DW1000* dw_ptr, uint8_t remote_address, uint8_t type, float timeout, uint64_t* timestamp_send = NULL);
    bool sendReportFrameBlocking(DW1000* dw_ptr, uint8_t remote_address, int64_t timediff_slave, float timeout, uint64_t* timestamp_send = NULL);
    bool sendDelayedRangingFrameBlocking(DW1000* dw_ptr, uint8_t remote_address, uint8_t type, float timeout, uint64_t* timestamp_send = NULL);

    // This function corrects the timestamps if the counter had an overflow between measurements
    bool correctTimestamps(uint64_t* timestamp_master_request_1, uint64_t* timestamp_slave_reply, uint64_t* timestamp_master_request_2) const;
};

}
