/*
 * UWBSwarmRing.cpp
 *
 *  Created on: 21 Apr 2016
 *      Author: Manuel
 */

#include "UWBSwarmRing.h"

#include "settings.h"



namespace ait {

UWBSwarmRing::UWBSwarmRing() {
	// TODO Auto-generated constructor stub

}

UWBSwarmRing::UWBSwarmRing(const UWB2WayMultiRange* tracker)
{
	registerTracker(tracker);
	UWBSwarmRing();
}

UWBSwarmRing::~UWBSwarmRing()
:onRangingCompleteCallback(0), tracker_(0), numberOfAgents_(0)
{
	// TODO Auto-generated destructor stub
}



void UWBSwarmRing::registerTracker(const UWB2WayMultiRange* tracker) {

	this->tracker_ = tracker;
}

bool UWBSwarmRing::getRingAddress() {

	DW1000* masterModule = tracker_->getModule(1);
}

bool UWBSwarmRing::startRingParticipation() {
}

void UWBSwarmRing::receiveFrameCallback(){

}

void UWBSwarmRing::sentFrameCallback(){

}
void UWBSwarmRing::startInterrupt() {

	DW1000* masterModule = tracker_->getModule(1);
	if (masterModule->isInterruptInit())
		masterModule->setCallbacks(this, &UWBSwarmRing::receiveFrameCallback, &UWBSwarmRing::sentFrameCallback);
	else
		ERROR_PRINTF("Cannot set interrupt for masterModule");
}

void UWBSwarmRing::stopInterrupt() {

	DW1000* masterModule = tracker_->getModule(1);
	masterModule->setCallbacks(NULL, NULL);
}

} /* namespace ait */

