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
	Job(unsigned short jobId, const std::vector<unsigned short> &config);
	Job(const Job &rhs);

	void calculateEarliestStartTimes(unsigned short currentTime);
	void calculateDuration();
	void calculateSlack(unsigned short maxDuration);
	void sortTasksByTaskId();
	void printEndResult();

	bool jobDone(unsigned short currentTime);
	bool jobBusy(unsigned short currentTime);
	bool taskAvailable();

	unsigned short getDuration() const;
	unsigned short getJobId() const;
	const std::vector<Task>& getTasks() const;
	bool startNextTask(unsigned short startTime);

	// can't be const, the next task will be started (starttime set)
	Task& getNextTask();

	unsigned short getSlack() const;

	Job& operator=(const Job &rhs);
	bool operator<(const Job &rhs) const;

	virtual ~Job();

private:
	unsigned short calculateEarliestStartTime(const Task &task);

	unsigned short jobId;
	std::vector<Task> tasks;
	unsigned short duration;
	unsigned short slack;
};

std::ostream& operator<<(std::ostream &os, const Job &job);

#endif /* JOB_H_ */
