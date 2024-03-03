/*
 * Job.h
 *
 *  Created on: 22 Feb 2024
 *      Author: woutn
 */

#ifndef JOB_H_
#define JOB_H_

#include <vector>
#include "Task.h"

class Job {
public:
	Job();
	Job(unsigned short jobId, std::vector<unsigned short> config);
	Job(const Job &rhs);

	void calculateEarliestStartTimes(unsigned short currentTime);
	void calculateDuration();
	void calculateSlack(unsigned short maxDuration);
	void sortTasksByTaskId();
	void printEndResult();

	bool jobDone(unsigned short currentTime);
	bool jobBusy(unsigned short currentTime);
	bool taskAvailable();

	bool usesMachine(unsigned short machineNr,
			unsigned short currentTime) const;

	unsigned short getDuration() const;
	unsigned short getJobId() const;
	const std::vector<Task>& getTasks() const;
	bool startNextTask(unsigned short startTime);
	unsigned short getNextMachine();

	unsigned short getSlack() const;

	virtual ~Job();

private:
	// can't be const, the next task will be started (starttime set)
	// because of this i made it private, so it will at least not be altered from outside
	Task* getNextTask();
	unsigned short calculateEarliestStartTime(Task &task);

	unsigned short jobId;
	std::vector<Task> tasks;
	std::vector<Task> finishedTasks;
	unsigned short duration;
	unsigned short slack;
};

std::ostream& operator<<(std::ostream &os, const Job &job);

#endif /* JOB_H_ */
