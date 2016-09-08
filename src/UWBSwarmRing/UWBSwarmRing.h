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

class UWBSwarmRing: public UWBProtocol {

public:
	UWBSwarmRing(uint8_t numOfAgents = 3, UWB2WayMultiRange* tracker = NULL);
	virtual ~UWBSwarmRing();

	void registerTracker(UWB2WayMultiRange* tracker);
	UWB2WayMultiRange* getTracker(){ return tracker_;}
	void startRingParticipation();
	void rangeNextAgent();
	void rangeAllAgents();

	void setRangingCompleteCallback(void (*pF)(const UWB2WayMultiRange::RawRangingResult&));

	bool getResetFlag(void){return resetFlag_;}


private:

	enum FrameType
	    {
	        MASTER_REQUEST_1 = 1,
	        SLAVE_REPLY,
	        MASTER_REQUEST_2,
	        SLAVE_REPORT,
	        RING_TOKEN
	    };

	const uint32_t RESET_DELAY_MS = 120;

	void rangeAgent(uint8_t destAddress, const UWB2WayMultiRange::RawRangingResult* raw_result);
	bool sendTokenTo(uint8_t destAddress);

	void attachInterruptCallbacks();		//start listening for frames
	void detachInterruptCallbacks() volatile;		//stop listening for frames, go into blocking mode

	void resetModules() volatile;
	void receiveFrameCallback();
	void sentFrameCallback();

	void (*onRangingCompleteCallback)(const UWB2WayMultiRange::RawRangingResult&);		//what to do with the resulted measurements

	UWB2WayMultiRange* tracker_;
	DW1000*	masterModule_;
	uint8_t numberOfAgents_;
	bool hasToken_;
	bool isRingStarter_;
	bool resetFlag_;

	Timer timer;
	uint32_t timeOfLastRanging;

	uint64_t master_request_1_timestamp_;
	uint64_t slave_reply_timestamp_;
	uint64_t master_request_2_timestamp_;
	uint64_t timediff_slave_;
};

} /* namespace ait */


#endif /* UWBSWARMRING_H_ */
