/*
 * UWBSwarmRing.cpp
 *
 *  Created on: 21 Apr 2016
 *      Author: Manuel
 */

#include "UWBSwarmRing.h"

#include "settings.h"



namespace ait {

UWBSwarmRing::UWBSwarmRing(UWB2WayMultiRange* tracker)
: UWBProtocol(ENTRY_ADDRESS),
  onRangingCompleteCallback(0),
  master_request_1_timestamp_(0),
  slave_reply_timestamp_(0),
  master_request_2_timestamp_(0),
  timediff_slave_(0),
  hasToken_(false),
  isTail_(true)
{
	registerTracker(tracker);
}

UWBSwarmRing::~UWBSwarmRing()
{
	// TODO Auto-generated destructor stub
}

void UWBSwarmRing::registerTracker(UWB2WayMultiRange* tracker) {

	this->tracker_ = tracker;
	masterModule_ = tracker_->getModule(0);
}

void UWBSwarmRing::setRangingCompleteCallback(void* (*pF)(UWB2WayMultiRange&, const UWB2WayMultiRange::RawRangingResult&))
{
	this->onRangingCompleteCallback = pF;
}

bool UWBSwarmRing::getRingAddress() {

	bool recStatus = receiveTrackerFrameBlocking(masterModule_, 1.2f); //receive any frame for ENTRY_ADDRESS

	if (recStatus && (receivedFrame_.type == RING_ENTRY_PING)) {
		address_ = receivedFrame_.address + 1;

		DEBUG_PRINTF("Got Ring address \r\n");

		return true;
	}
	else {											//No entry frame received, create new ring
		address_ = 1;
		DEBUG_PRINTF("New Ring initialized \r\n");
	}

	return false;
}

bool UWBSwarmRing::startRingParticipation() {



	if (address_ == 1){
		isTail_ = true;
		tracker_->setAddress(address_);											//set the correct address to the tracker

		ticker.attach(this, &UWBSwarmRing::sendRingEntryPing, 1.0f);			//Ping and wait for another agent
		attachInterruptCallbacks();

		DEBUG_PRINTF("\r\nStarted listening for 2nd agent \r\n");

		return true;
	}

	sendRangingFrameBlocking(masterModule_, address_ - 1, RING_NEW_MEMBER, 0.1f);//send Frame to previous tail of ring to be included in the ring
	bool recStatus = receiveTrackerFrameBlocking(masterModule_, 0.1f);
	if (recStatus && (receivedFrame_.type == RING_ENTRY_PING)) {
		isTail_ = true;
		tracker_->setAddress(address_);											//set the correct address to the tracker
		ticker.attach(this, &UWBSwarmRing::sendRingEntryPing, 1.0f);			//Fulfil duty as new tail
		attachInterruptCallbacks();												//Start receiving frames via interrupt

		DEBUG_PRINTF("\r\nAm now the new tail \r\n");
	}

	return recStatus;

}

//Routine executed after DW1000 triggered the Rx interrupt. No further Rx interrupts are generated during this routine! (b/c Flag clears after)
void UWBSwarmRing::receiveFrameCallback(){

	masterModule_->readRegister(DW1000_RX_BUFFER, 0, reinterpret_cast<uint8_t*>(&receivedFrame_), masterModule_->getFramelength());

	if (receivedFrame_.remote_address == address_){

        uint8_t sender_address = receivedFrame_.address;


		switch (receivedFrame_.type)
		{

		case RING_NEW_MEMBER:				//a new member wants to enter the ring
			joinNewAgent();
			break;

		case MASTER_REQUEST_1:				//Start blocking ranging procedure (slave role)
			master_request_1_timestamp_ = masterModule_->getRXTimestamp();
			sendDelayedRangingFrame(masterModule_, sender_address, SLAVE_REPLY, master_request_1_timestamp_ + ANSWER_DELAY_TIMEUNITS);

        	break;

		case MASTER_REQUEST_2:
			master_request_2_timestamp_ = masterModule_->getRXTimestamp();
        	correctTimestamps(&master_request_1_timestamp_, &slave_reply_timestamp_, &master_request_2_timestamp_);
        	timediff_slave_ = -2 * slave_reply_timestamp_ + master_request_1_timestamp_ + master_request_2_timestamp_;
            sendReportFrame(masterModule_, sender_address, timediff_slave_, master_request_1_timestamp_, slave_reply_timestamp_, master_request_2_timestamp_);

            break;

		case RING_TOKEN:

				hasToken_ = true;

			break;

		}
	}
}

void UWBSwarmRing::sentFrameCallback(){

	switch (rangingFrame_.type){

	case SLAVE_REPLY:
		slave_reply_timestamp_ = masterModule_->getTXTimestamp();
		break;
	}


}

void UWBSwarmRing::rangeNextAgent(){

	if (!hasToken_)
		return;

	DEBUG_PRINTF("Have TOKEN, start ranging!\r\n");

	if (isTail_)					//stop interrupting!
		ticker.detach();

	detachInterruptCallbacks();

	const UWB2WayMultiRange::RawRangingResult* raw_result;

	if (!isTail_)
		raw_result = &(tracker_->measureTimesOfFlight(address_ + 1));
	else
		raw_result = &(tracker_->measureTimesOfFlight(1));

	if (onRangingCompleteCallback)
		this->onRangingCompleteCallback(*tracker_, *raw_result);

	hasToken_ = false;

	if (!isTail_){

		bool recv = sendRangingFrameBlocking(masterModule_, address_ + 1, RING_TOKEN, 0.1f);
		if (!recv)
			ERROR_PRINTF("Could not send Token!\r\n");
		else
			DEBUG_PRINTF("Token sent\r\n");
	}
	else
	{

		//sendRingEntryPing();

		bool recv = sendRangingFrameBlocking(masterModule_, 1, RING_TOKEN, 0.1f);
		if (!recv)
			ERROR_PRINTF("Could not send Token!\r\n");
		else
			DEBUG_PRINTF("Token sent\r\n");

	}

	attachInterruptCallbacks();

}

void UWBSwarmRing::sendRingEntryPing(){
	bool transStatus = sendRangingFrameBlocking(masterModule_, ENTRY_ADDRESS, RING_ENTRY_PING, 0.1f);

	if (transStatus)
		DEBUG_PRINTF("Entry ping sent \r\n");
	else
		ERROR_PRINTF("Entry ping sending failed! \r\n");
}

void UWBSwarmRing::attachInterruptCallbacks() {

	if (masterModule_->isInterruptInit())
		masterModule_->setCallbacks(this, &UWBSwarmRing::receiveFrameCallback, &UWBSwarmRing::sentFrameCallback);
	else
		ERROR_PRINTF("Cannot set interrupt for masterModule \r\n");
}

void UWBSwarmRing::detachInterruptCallbacks() {

	masterModule_->setCallbacks(NULL, NULL);
}

void UWBSwarmRing::joinNewAgent()
{

	if (receivedFrame_.address == (address_ + 1))			//Am no longer the tail
	{
		ticker.detach();
		isTail_ = false;

		bool transStatus = sendRangingFrameBlocking(masterModule_, (address_ + 1), RING_ENTRY_PING, 0.1f);

		if (transStatus)
			DEBUG_PRINTF("New tail attached \r\n");
	}

	if (address_ == 1)
	{
		hasToken_ = true;
	}

}

} /* namespace ait */

