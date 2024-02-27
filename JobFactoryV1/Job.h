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
	virtual ~Job();

	unsigned short getJobId() const;
	std::vector<Task> getTasks() const;

private:
	unsigned short jobId;
	std::vector<Task> tasks;
};

std::ostream& operator<<(std::ostream &os, const Job &job);

#endif /* JOB_H_ */
