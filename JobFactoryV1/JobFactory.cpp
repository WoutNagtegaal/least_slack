/*
 * JobFactory.cpp
 *
 *  Created on: 22 Feb 2024
 *      Author: woutn
 */

#include "JobFactory.h"
#include "Job.h"

JobFactory::JobFactory() {

}

JobFactory::JobFactory(std::vector<std::vector<unsigned short>> config) {
	unsigned short id = 0;
	for (auto job : config) {
		this->jobs.push_back(Job(id, job));
		id++;
	}
}

JobFactory::JobFactory(const JobFactory &rhs) :
		jobs(rhs.jobs) {
}

JobFactory::~JobFactory() {
	// TODO Auto-generated destructor stub
}

JobFactory::JobFactory(const ConfigReader &rhs) :
		JobFactory(rhs.getConfigValues()) {

}

std::vector<Job> JobFactory::getJobs() const {
	return this->jobs;
}

std::ostream& operator <<(std::ostream &os, const JobFactory &jobFactory) {
	for (Job j : jobFactory.getJobs()) {
		os << j;
	}
	return os;
}
