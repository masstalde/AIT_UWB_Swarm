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
	virtual ~UWBSwarmRing();



private:
	uint8_t numberOfAgents;
};

} /* namespace ait */


#endif /* UWBSWARMRING_H_ */
