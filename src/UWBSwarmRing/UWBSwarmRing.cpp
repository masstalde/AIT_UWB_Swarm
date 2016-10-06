/*
 * UWBSwarmRing.cpp
 *
 *  Created on: 21 Apr 2016
 *      Author: Manuel
 */

#include "UWBSwarmRing.h"

#include "settings.h"



namespace ait {

UWBSwarmRing::UWBSwarmRing(uint8_t numOfAgents, UWB2WayMultiRange* tracker, BufferedSerial* serial)
: UWBProtocol(0),
  onRangingCompleteCallback(0),
  tracker_(NULL),
  masterModule_(NULL),
  numberOfAgents_(numOfAgents),
  hasToken_(false),
  isRingStarter_(true),
  resetFlag_(false),
  master_request_1_timestamp_(0),
  slave_reply_timestamp_(0),
  master_request_2_timestamp_(0),
  timediff_slave_(0),
  serial_(serial)
{

	if (tracker)
		registerTracker(tracker);

	timer.start();
	timeOfLastMessage = 0;
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

	isRingStarter_ = true;
	resetFlag_ = false;
	masterModule_->stopTRX();
	attachInterruptCallbacks();
	masterModule_->startRX();

	if (address_ != 1)
		isRingStarter_ = false;
	else
		wait_ms(8);

	if (isRingStarter_)
	{
		hasToken_ = true;
		wait_ms(60);
	}

	timeOfLastMessage = timer.read_ms();

}

//Routine executed after DW1000 triggered the Rx interrupt. No further Rx interrupts are generated during this routine! (b/c Flag clears after)
void UWBSwarmRing::receiveFrameCallback(){
	masterModule_->readRegister(DW1000_RX_BUFFER, 0, reinterpret_cast<uint8_t*>(&receivedFrame_), masterModule_->getFramelength());
	timeOfLastMessage = timer.read_ms();
	hasToken_ = false;
	isRingStarter_ = false;

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
				isRingStarter_ = false;
			break;
		}
	}
	else
	{
		masterModule_->stopTRX();
		masterModule_->startRX();
	}
}

void UWBSwarmRing::sentFrameCallback() {

	switch (rangingFrame_.type){

	case SLAVE_REPLY:
		slave_reply_timestamp_ = masterModule_->getTXTimestamp();
		break;
	}
}

void UWBSwarmRing::rangeNextAgent() {
	const UWB2WayMultiRange::RawRangingResult* raw_result;

	if ((timer.read_ms()-timeOfLastMessage) > RESET_DELAY_MS && timeOfLastMessage > 0)
		resetFlag_ = true;

	if (!hasToken_)
		return;

	detachInterruptCallbacks();

	uint8_t	nextAddress = address_  % numberOfAgents_ + 1;

	raw_result = &(tracker_->measureTimesOfFlight(nextAddress, 0.02));

	if (onRangingCompleteCallback)
		this->onRangingCompleteCallback(*raw_result);

	//wait_ms(10);

	if(raw_result->status != UWB2WayMultiRange::SUCCESS)
	{
		//DEBUG_PRINTF("\r\nSOFT RESET\r\n");
		resetModules();
		wait_us(10);
	} else {
		//DEBUG_PRINTF("\r\nRanging OK\r\n");

		sendTokenTo(nextAddress);
		attachInterruptCallbacks();
	}



//	uint32_t timeElapsedMs = timer.read_ms() - timeOfLastRanging;
	//DEBUG_PRINTF_VA("Time elapsed for entire Loop: %i\r\n", timeElapsedMs);
	//DEBUG_PRINTF_VA("Time elapsed for single short frame: %i\r\n", timeMessageAfter - timeMessageBefore);

	if(raw_result->status == UWB2WayMultiRange::SUCCESS)
		timeOfLastMessage = timer.read_ms();

}

void UWBSwarmRing::rangeAllAgents() {
	const UWB2WayMultiRange::RawRangingResult* raw_result;
	uint8_t nextAddress = 0;

	if (timeOfLastMessage > 0 && (timer.read_ms() - (int) timeOfLastMessage) > RESET_DELAY_MS) {
		resetModules();
		timeOfLastMessage = timer.read_ms();
		resetFlag_ = true;
		return;
	}


	if (!hasToken_)
	{
		return;
	}

	masterModule_->stopTRX();
	detachInterruptCallbacks();
	serial_->disableTx();

	nextAddress = address_  % numberOfAgents_ + 1;
	/////////////////////////////////////////////////////////////////

	raw_result = &(tracker_->measureTimesOfFlight(nextAddress, 0.02));

	if (onRangingCompleteCallback)
		this->onRangingCompleteCallback(*raw_result);

	if (raw_result->status != UWB2WayMultiRange::SUCCESS) {
		//DEBUG_PRINTF("\r\nSOFT RESET\r\n");

		resetModules();

		return;
	}
	/////////////////////////////////////////////////////////
	nextAddress = nextAddress % numberOfAgents_ + 1;
	raw_result = &(tracker_->measureTimesOfFlight(nextAddress, 0.02));

	if (onRangingCompleteCallback)
			this->onRangingCompleteCallback(*raw_result);

	if (raw_result->status != UWB2WayMultiRange::SUCCESS) {

		resetModules();

		return;
	}
	/////////////////////////////////////////////////////////
	nextAddress = address_  % numberOfAgents_ + 1;
	sendTokenTo(nextAddress);

	masterModule_->stopTRX();
	attachInterruptCallbacks();
	masterModule_->startRX();

	serial_->resumeTx();

//	uint32_t timeElapsedMs = timer.read_ms() - timeOfLastRanging;
	//DEBUG_PRINTF_VA("Time elapsed for entire Loop: %i\r\n", timeElapsedMs);
	//DEBUG_PRINTF_VA("Time elapsed for single short frame: %i\r\n", timeMessageAfter - timeMessageBefore);

//	if(raw_result->status == UWB2WayMultiRange::SUCCESS)
		timeOfLastMessage = timer.read_ms();

}


bool UWBSwarmRing::sendTokenTo(uint8_t destAddress) {
	bool recv = sendRangingFrameBlocking(masterModule_, destAddress, RING_TOKEN,
			0.1f);
	//Test for successfully sent TOKEN, should fail VERY RARELY
	if (!recv) {
		resetModules();
		return false;
	} else
		hasToken_ = false;

	return true;
}

void UWBSwarmRing::resetModules() volatile{
	for (uint8_t i = 0; i < tracker_->getNumOfModules(); i++){
		DW1000* dw_ptr = tracker_->getModule(i);

		if (USE_NLOS_SETTINGS)
			DW1000Utils::setNLOSSettings(dw_ptr, DATA_RATE_SETTING, PRF_SETTING, PREAMBLE_SETTING, SFD_SETTING);
		else
			DW1000Utils::setLOSSettings(dw_ptr, DATA_RATE_SETTING, PRF_SETTING, PREAMBLE_SETTING, SFD_SETTING);
	}
}

void UWBSwarmRing::attachInterruptCallbacks(){

	if (masterModule_->isInterruptInit())
		masterModule_->setCallbacks(this, &UWBSwarmRing::receiveFrameCallback, &UWBSwarmRing::sentFrameCallback);
	else
		ERROR_PRINTF("Cannot set interrupt for masterModule \r\n");
}

void UWBSwarmRing::detachInterruptCallbacks() volatile{

	masterModule_->setCallbacks(NULL, NULL);
}

} /* namespace ait */

