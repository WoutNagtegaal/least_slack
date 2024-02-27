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

	void calculateEarliestStartTimes();
	void calculateDuration();
	void calculateSlack(unsigned short maxDuration);

	unsigned short getDuration() const;
	unsigned short getJobId() const;
	std::vector<Task> getTasks() const;

	void setSlack(unsigned short slack);
	unsigned short getSlack() const;

	virtual ~Job();

private:
	unsigned short calculateEarliestStartTime(Task &task);

	unsigned short jobId;
	std::vector<Task> tasks;
	unsigned short duration;
	unsigned short slack;
};

std::ostream& operator<<(std::ostream &os, const Job &job);

#endif /* JOB_H_ */
