/*
 * UWBSwarmRing.h
 *
 *  Created on: 21 Apr 2016
 *      Author: Manuel
 */

#ifndef UWBSWARMRING_H_
#define UWBSWARMRING_H_

namespace ait{

class UWBSwarmRing: public UWBProtocol {

public:
	UWBSwarmRing();
	UWBSwarmRing(const UWB2WayMultiRange* tracker);
	virtual ~UWBSwarmRing();



	void registerTracker(const UWB2WayMultiRange* tracker);
	bool getRingAddress();
	bool startRingParticipation();

private:

	void startInterrupt();			//start listening frames
	void stopInterrupt();			//stop listening for frames, go into blocking mode

	void receiveFrameCallback();
	void sentFrameCallback();

	void* (*onRangingCompleteCallback)();		//what to do with the resulted measurements

	UWB2WayMultiRange* tracker_;
	uint8_t numberOfAgents_;
};

} /* namespace ait */


#endif /* UWBSWARMRING_H_ */
