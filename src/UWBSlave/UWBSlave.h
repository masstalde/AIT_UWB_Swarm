#pragma once

#include "settings.h"

#include <vector>
#include <mbed.h>
#include <DW1000.h>

#include "UWBProtocol.h"

namespace ait
{

class UWBSlave : public UWBProtocol
{
public:
    UWBSlave(DW1000* dw_ptr, uint8_t address);

    const DW1000* getModule() const;
    DW1000* getModule();

    void startReceiving();
    void stopReceiving();

    void checkForFrame(float timeout = 1.0f);

protected:
    DW1000* dw_ptr_;

    uint64_t master_request_1_timestamps_[NUM_OF_UWB_ADDRESSES];
    uint64_t slave_reply_timestamps_[NUM_OF_UWB_ADDRESSES];
    uint64_t master_request_2_timestamps_[NUM_OF_UWB_ADDRESSES];

#if SLAVE_REPLY_WITH_STATS
    ReceptionStats reception_stats_[NUM_OF_UWB_ADDRESSES][2];
#endif

    ReportRangingFrame frame_;

    void receiveFrameCallback();
    void sentFrameCallback();

    void handleMasterRequest1(uint64_t timestamp_recv, RangingFrame* frame, float timeout);
    void handleMasterRequest2(uint64_t timestamp_recv, RangingFrame* frame, float timeout);
};

}
