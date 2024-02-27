/*
 * Job.cpp
 *
 *  Created on: 22 Feb 2024
 *      Author: woutn
 */

#include "Job.h"

Job::Job() :
		jobId(0) {
}

Job::Job(unsigned short jobId, std::vector<unsigned short> config) :
		jobId(jobId) {
	for (unsigned short i = 0; i < config.size(); i += 2) {
		tasks.push_back(Task(i / 2, config[i], config[i + 1]));
	}
}

Job::Job(const Job &rhs) :
		jobId(rhs.jobId), tasks(rhs.tasks) {
}

Job::~Job() {
	// TODO Auto-generated destructor stub
}

std::ostream& operator <<(std::ostream &os, const Job &job) {
	os << "Job nr " << job.getJobId() << " with the following tasks: "
			<< std::endl;
	for (Task &t : job.getTasks()) {
		os << t;
	}
	return os;
}

unsigned short Job::getJobId() const {
	return this->jobId;
}

std::vector<Task> Job::getTasks() const {
	return this->tasks;
}
