/*
 * Machine.h
 *
 *  Created on: 3 Mar 2024
 *      Author: woutn
 */

#ifndef MACHINE_H_
#define MACHINE_H_

class Machine {
public:
	Machine();
	virtual ~Machine();

	void startMachine(unsigned short currentTime, unsigned short duration);
	bool machineBusy(unsigned short currentTime);

private:
	unsigned short freeFrom;
};

#endif /* MACHINE_H_ */
