/*
 * UWBSwarmRing.h
 *
 *  Created on: 21 Apr 2016
 *      Author: Manuel
 */

#ifndef UWBSWARMRING_H_
#define UWBSWARMRING_H_

#include "UWB2WayMultiRange.h"

namespace ait{

const uint8_t TAIL_ADDRESS = 3;

class UWBSwarmRing: public UWBProtocol {

public:
	UWBSwarmRing(UWB2WayMultiRange* tracker);
	virtual ~UWBSwarmRing();



	void registerTracker(UWB2WayMultiRange* tracker);
	void startRingParticipation();
	void rangeNextAgent();


	void setRangingCompleteCallback(void* (*pF)(UWB2WayMultiRange&, const UWB2WayMultiRange::RawRangingResult&));

private:

	enum FrameType
	    {
	        MASTER_REQUEST_1 = 1,
	        SLAVE_REPLY,
	        MASTER_REQUEST_2,
	        SLAVE_REPORT,
	        RING_TOKEN
	    };

	void attachInterruptCallbacks();		//start listening for frames
	void detachInterruptCallbacks();		//stop listening for frames, go into blocking mode

	void receiveFrameCallback();
	void sentFrameCallback();


	void* (*onRangingCompleteCallback)(UWB2WayMultiRange&, const UWB2WayMultiRange::RawRangingResult&);		//what to do with the resulted measurements


	UWB2WayMultiRange* tracker_;
	DW1000*	masterModule_;
	bool hasToken_;

	uint64_t master_request_1_timestamp_;
	uint64_t slave_reply_timestamp_;
	uint64_t master_request_2_timestamp_;
	uint64_t timediff_slave_;


};

} /* namespace ait */


#endif /* UWBSWARMRING_H_ */
