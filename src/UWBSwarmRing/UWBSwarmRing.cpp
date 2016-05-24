/*
 * UWBSwarmRing.cpp
 *
 *  Created on: 21 Apr 2016
 *      Author: Manuel
 */

#include "UWBSwarmRing.h"

#include "settings.h"



namespace ait {

UWBSwarmRing::UWBSwarmRing(uint8_t numOfAgents, UWB2WayMultiRange* tracker)
: UWBProtocol(0),
  onRangingCompleteCallback(0),
  tracker_(NULL),
  masterModule_(NULL),
  numberOfAgents_(numOfAgents),
  hasToken_(false),
  master_request_1_timestamp_(0),
  slave_reply_timestamp_(0),
  master_request_2_timestamp_(0),
  timediff_slave_(0)
{

	if (tracker)
		registerTracker(tracker);

	timer.start();
	timeOfLastRanging = 0;
}

UWBSwarmRing::~UWBSwarmRing()
{
	// TODO Auto-generated destructor stub
}

void UWBSwarmRing::registerTracker(UWB2WayMultiRange* tracker) {

	this->tracker_ = tracker;
	masterModule_ = tracker_->getModule(0);
	address_ = tracker_->getAddress();
}

void UWBSwarmRing::setRangingCompleteCallback(void (*pF)(const UWB2WayMultiRange::RawRangingResult&))
{
	this->onRangingCompleteCallback = pF;
}

void UWBSwarmRing::startRingParticipation() {

	if (address_ == 1)
		hasToken_ = true;
	else
		attachInterruptCallbacks();
}

//Routine executed after DW1000 triggered the Rx interrupt. No further Rx interrupts are generated during this routine! (b/c Flag clears after)
void UWBSwarmRing::receiveFrameCallback(){
	masterModule_->readRegister(DW1000_RX_BUFFER, 0, reinterpret_cast<uint8_t*>(&receivedFrame_), masterModule_->getFramelength());

	if (receivedFrame_.remote_address == address_){
        uint8_t sender_address = receivedFrame_.address;

		switch (receivedFrame_.type)
		{
		case MASTER_REQUEST_1:
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
	else
	{
		wait_us(10);
		masterModule_->startRX();
	}
}

void UWBSwarmRing::sentFrameCallback(){

	switch (rangingFrame_.type){

	case SLAVE_REPLY:
		slave_reply_timestamp_ = masterModule_->getTXTimestamp();
		break;
	}
}

void UWBSwarmRing::rangeNextAgent() {
	uint8_t nextAddress = 0;
	const UWB2WayMultiRange::RawRangingResult* raw_result;

	if (!hasToken_)
		return;

	detachInterruptCallbacks();

	if ((uint8_t)address_ != (uint8_t)numberOfAgents_)
		nextAddress = address_ + 1;
	else
		nextAddress = 1;

	raw_result = &(tracker_->measureTimesOfFlight(nextAddress, 0.02));

	if(raw_result->status != 0)
		wait_ms(3000);
	else
	{
		DEBUG_PRINTF("\r\nRanging OK\r\n");
	}

	hasToken_ = false;

	timeMessageBefore = timer.read_us();
	bool recv = sendRangingFrameBlocking(masterModule_, nextAddress, RING_TOKEN,
			0.1f);
	if (!recv)
		ERROR_PRINTF("Could not send Token!\r\n");


	timeMessageAfter = timer.read_us();

	if (onRangingCompleteCallback)
		this->onRangingCompleteCallback(*raw_result);

	attachInterruptCallbacks();

	uint32_t timeElapsedMs = timer.read_ms() - timeOfLastRanging;

	//DEBUG_PRINTF_VA("Time elapsed for entire Loop: %i\r\n", timeElapsedMs);
	//DEBUG_PRINTF_VA("Time elapsed for single short frame: %i\r\n", timeMessageAfter - timeMessageBefore);

	timeOfLastRanging = timer.read_ms();

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

} /* namespace ait */

