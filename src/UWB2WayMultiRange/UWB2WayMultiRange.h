#pragma once

#include "settings.h"

#include <vector>
#include <mbed.h>
#include <DW1000.h>

#include "UWBProtocol.h"

namespace ait
{

class UWB2WayMultiRange : public UWBProtocol
{
public:
    static const float SPEED_OF_LIGHT_IN_M_PER_US = 299.792458f;

    enum RangingStatus
    {
        SUCCESS = 0,
        NO_MASTER_REQUEST_1,
        NO_SLAVE_REPLY,
        NO_MASTER_REQUEST_2,
        NO_SLAVE_REPORT,
        OTHER,
    };

    static const char* const RANGING_STATUS_MESSAGES[];

    struct RawRangingResult
    {
    	  RawRangingResult()
    	        : tracker_address(0), remote_address(0),timestamp_master_request_1_recv(0), timestamp_slave_reply_send(0), timestamp_master_request_2_recv(0),  timeDiffSlave(0), status(OTHER)
    	        {
    	        }

        uint8_t tracker_address;
        uint8_t remote_address;

        std::vector<uint64_t> timestamp_master_request_1;
        std::vector<uint64_t> timestamp_slave_reply;
        std::vector<uint64_t> timestamp_master_request_2;

        uint64_t timestamp_master_request_1_recv;
        uint64_t timestamp_slave_reply_send;
        uint64_t timestamp_master_request_2_recv;

        uint64_t timeDiffSlave;

        std::vector<ReceptionStats> stats;
        RangingStatus status;
        char status_description[64];
    };

    UWB2WayMultiRange(uint8_t address);
    ~UWB2WayMultiRange();

    void addModule(DW1000* dw_ptr);

    int getNumOfModules() const;

    void setAddress(uint8_t newAddress);

    const DW1000* getModule(int module_index) const;
    DW1000* getModule(int module_index);

//    const RangingResult& measureTimeOfFlight(uint8_t remote_address, float timeout = 1.0f, ReceptionStats* stats = NULL);
    const RawRangingResult& measureTimesOfFlight(uint8_t remote_address, float timeout = 1.0f, ReceptionStats* stats = NULL);

    float convertDWTimeunitsToMicroseconds(int64_t dw_timeunits) const;
    float convertTimeOfFlightToDistance(float tof) const;

protected:
    std::vector<DW1000*> dw_vector_;
    uint8_t moduleCounter_;
    RawRangingResult raw_result_;			//    RangingResult result_;

    bool receiveFramesBlocking(std::vector<DW1000*>& dw_array, float timeout, uint64_t* timestamp_recv = NULL, ReceptionStats* stats = NULL);
    bool receiveFramesBlocking(std::vector<DW1000*>& dw_array, uint8_t type, float timeout, uint64_t* timestamp_recv = NULL, ReceptionStats* stats = NULL);
};

}
