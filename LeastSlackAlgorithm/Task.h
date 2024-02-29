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

	bool taskDone() const;
	void startTask(unsigned short startTime);

	unsigned short getTaskId() const;
	unsigned short getDuration() const;
	unsigned short getMachineNr() const;
	unsigned short getEarliestStartTime() const;
	unsigned short getStartTime() const;
	unsigned short getEndTime() const;

	// bool operator==(const Task &rhs);

	void setEarliestStartTime(unsigned short earliestStartTime);
	void setStartTime(unsigned short startTime);
	void setEndTime(unsigned short endTime);

	Task& operator=(const Task &rhs);

	virtual ~Task();

private:
	unsigned short taskId;
	unsigned short machineNr;
	unsigned short duration;
	unsigned short earliestStartTime;
	unsigned short startTime;
	unsigned short endTime;
};

std::ostream& operator<<(std::ostream &os, const Task &task);

#endif /* TASK_H_ */
