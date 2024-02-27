/*
 * Task.h
 *
 *  Created on: 22 Feb 2024
 *      Author: woutn
 */

#ifndef TASK_H_
#define TASK_H_

#include <iostream>

class Task {
public:
	Task();
	Task(unsigned short taskId, unsigned short machineNr,
			unsigned short duration);
	Task(const Task &rhs);
	virtual ~Task();

	unsigned short getTaskId() const;
	unsigned short getDuration() const;
	unsigned short getMachineNr() const;

private:
	unsigned short taskId;
	unsigned short machineNr;
	unsigned short duration;
};

std::ostream& operator<<(std::ostream &os, const Task &task);

#endif /* TASK_H_ */
