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

const uint8_t ENTRY_ADDRESS = 0;

class UWBSwarmRing: public UWBProtocol {

public:
	UWBSwarmRing();
	UWBSwarmRing(UWB2WayMultiRange* tracker);
	virtual ~UWBSwarmRing();



	void registerTracker(UWB2WayMultiRange* tracker);
	bool getRingAddress();
	bool startRingParticipation();

private:

	enum FrameType
	    {
			RING_ENTRY_PING = 0,
	        MASTER_REQUEST_1,
	        SLAVE_REPLY,
	        MASTER_REQUEST_2,
	        SLAVE_REPORT,
	        RING_NEW_MEMBER
	    };

	void startListeningInterrupt();			//start listening for frames
	void stopInterrupt();			//stop listening for frames, go into blocking mode
	void sendRingEntryPing();		//send the ping for new ring members

	void receiveFrameCallback();
	void sentFrameCallback();


	void* (*onRangingCompleteCallback)(const UWB2WayMultiRange::RawRangingResult*);		//what to do with the resulted measurements


	UWB2WayMultiRange* tracker_;
	Ticker ticker;

};

} /* namespace ait */


#endif /* UWBSWARMRING_H_ */
