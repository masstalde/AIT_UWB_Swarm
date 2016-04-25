/*
 * UWBSwarmRing.cpp
 *
 *  Created on: 21 Apr 2016
 *      Author: Manuel
 */

#include "UWBSwarmRing.h"

#include "settings.h"



namespace ait {

UWBSwarmRing::UWBSwarmRing()
: UWBProtocol(ENTRY_ADDRESS)
{
	// TODO Auto-generated constructor stub
	(void) tracker_;
	numberOfAgents_ = 0;
}

UWBSwarmRing::UWBSwarmRing(UWB2WayMultiRange* tracker)
: UWBProtocol(ENTRY_ADDRESS), numberOfAgents_(0)
{
	registerTracker(tracker);
}

UWBSwarmRing::~UWBSwarmRing()
{
	// TODO Auto-generated destructor stub
}



void UWBSwarmRing::registerTracker(UWB2WayMultiRange* tracker) {

	this->tracker_ = tracker;
}

bool UWBSwarmRing::getRingAddress() {

	DW1000* masterModule = tracker_->getModule(0);

	bool recStatus = receiveTrackerFrameBlocking(masterModule, 1.2f); //receive any frame for ENTRY_ADDRESS

	if (recStatus && (receivedFrame_.type == RING_ENTRY_PING)) {

		//tracker_->setAddress(receivedFrame_.address + 1);	//if successful, change address for the tracker to the acquired ring address
		numberOfAgents_ = receivedFrame_.address + 1;		//including oneself, set number of Agents in Ring

		DEBUG_PRINTF("Got Ring address \r\n");

		return true;
	}
	else {		//No entry frame received, create new ring
		//tracker_->setAddress(1);
		address_ = 1;
		numberOfAgents_ = 1;

		DEBUG_PRINTF("New Ring initialized \r\n");
	}

	return false;
}

bool UWBSwarmRing::startRingParticipation() {
	DW1000* masterModule = tracker_->getModule(0);

	if (numberOfAgents_ == 1){
		ticker.attach(this, &UWBSwarmRing::sendRingEntryPing, 1.0f);			//Ping and wait for another agent
		startListeningInterrupt();

		DEBUG_PRINTF("Started listening for 2nd agent \r\n");

		return true;
	}

	sendRangingFrameBlocking(masterModule, numberOfAgents_ - 1, RING_NEW_MEMBER, 0.1f); //send Frame to previous tail of ring to be included in the ring
	this->address_ = numberOfAgents_;	//Listen on and send from new address from now on

	bool recStatus = receiveTrackerFrameBlocking(masterModule, 0.1f);
	if (recStatus && (receivedFrame_.type == RING_ENTRY_PING)) {
		startListeningInterrupt();											//Start receiving frames via interrupt
		ticker.attach(this, &UWBSwarmRing::sendRingEntryPing, 1.0f);		//Fulfil duty as new tail

		DEBUG_PRINTF("Am now the new tail \r\n");
	}

	return recStatus;

}

void UWBSwarmRing::sendRingEntryPing(){
	DW1000* masterModule = tracker_->getModule(0);
	bool transStatus = sendRangingFrameBlocking(masterModule, ENTRY_ADDRESS, RING_ENTRY_PING, 0.1f);

	if (transStatus)
		DEBUG_PRINTF("Entry ping sent \r\n");
	else
		ERROR_PRINTF("Entry ping sending failed \r\n");
}

void UWBSwarmRing::receiveFrameCallback(){
	DW1000* masterModule = tracker_->getModule(0);
	masterModule->readRegister(DW1000_RX_BUFFER, 0, reinterpret_cast<uint8_t*>(&receivedFrame_), masterModule->getFramelength());

	if (receivedFrame_.remote_address == address_){

		switch (receivedFrame_.type)
		{

		case RING_NEW_MEMBER:				//a new member wants to enter the ring
			if (receivedFrame_.address == ENTRY_ADDRESS)			//Am no longer the tail
			{
				numberOfAgents_++;
				ticker.detach();

				bool transStatus = sendRangingFrameBlocking(masterModule, numberOfAgents_, RING_ENTRY_PING, 0.1f);

				if (transStatus)
					DEBUG_PRINTF("New tail attached \r\n");


			}
			else
				numberOfAgents_++;



		}


	}


}

void UWBSwarmRing::sentFrameCallback(){

}
void UWBSwarmRing::startListeningInterrupt() {

	DW1000* masterModule = tracker_->getModule(0);
	if (masterModule->isInterruptInit())
		masterModule->setCallbacks(this, &UWBSwarmRing::receiveFrameCallback, &UWBSwarmRing::sentFrameCallback);
	else
		ERROR_PRINTF("Cannot set interrupt for masterModule \r\n");
}

void UWBSwarmRing::stopInterrupt() {

	DW1000* masterModule = tracker_->getModule(0);
	masterModule->setCallbacks(NULL, NULL);
}

} /* namespace ait */

