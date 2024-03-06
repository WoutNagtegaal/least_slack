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

	bool taskStarted() const;
	bool taskBusy(unsigned short currentTime) const;
	bool taskDone(unsigned short currentTime) const;
	void startTask(unsigned short startTime);

	unsigned short getTaskId() const;
	unsigned short getDuration() const;
	unsigned short getMachineNr() const;
	unsigned short getEarliestStartTime() const;
	unsigned short getStartTime() const;
	unsigned short getEndTime() const;

	// bool operator==(const Task &rhs);
	Task& operator=(const Task &rhs);
	bool operator<(const Task &rhs) const;

	void setEarliestStartTime(unsigned short earliestStartTime);

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
