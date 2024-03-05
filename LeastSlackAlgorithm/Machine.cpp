/*
 * Machine.cpp
 *
 *  Created on: 3 Mar 2024
 *      Author: woutn
 */

#include "Machine.h"

Machine::Machine(): freeFrom(0) {

}

Machine::~Machine() {
}

void Machine::startMachine(unsigned short currentTime,
		unsigned short duration) {
	// machine will be unusable by other tasks while is busy
	this->freeFrom = currentTime + duration;
}

bool Machine::machineBusy(unsigned short currentTime) {
	return currentTime < freeFrom;
}

unsigned short Machine::getFreeFrom() {
	return this->freeFrom;
}
