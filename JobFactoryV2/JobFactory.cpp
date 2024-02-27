/*
 * JobFactory.cpp
 *
 *  Created on: 22 Feb 2024
 *      Author: woutn
 */

#include "JobFactory.h"
#include "Job.h"

#include <algorithm>

JobFactory::JobFactory(unsigned short nMachines, unsigned short nJobs,
		std::vector<std::vector<unsigned short>> config) :
		nMachines(nMachines), nJobs(nJobs) {
	this->initJobs(config);
}

JobFactory::JobFactory(const JobFactory &rhs) :
		nMachines(rhs.nMachines), nJobs(rhs.nJobs), jobs(rhs.jobs) {
}

JobFactory::~JobFactory() {
	// TODO Auto-generated destructor stub
}

JobFactory::JobFactory(const ConfigReader &rhs) {
	//
	this->nMachines = rhs.getNMachines();
	this->nJobs = rhs.getNJobs();
	this->initJobs(rhs.getConfigValues());
}

std::vector<Job> JobFactory::getJobs() const {
	return this->jobs;
}

std::ostream& operator <<(std::ostream &os, const JobFactory &jobFactory) {
	std::cout << "Jobfactory with " << jobFactory.getNJobs() << " jobs and "
			<< jobFactory.getNMachines() << " machines" << std::endl;

	for (Job &j : jobFactory.getJobs()) {
		os << j;
	}
	return os;
}

void JobFactory::initJobs(std::vector<std::vector<unsigned short> > config) {
	unsigned short id = 0;
	for (auto job : config) {
		this->jobs.push_back(Job(id, job));
		id++;
	}
}

void JobFactory::taskTests() {
	for (Job &j : this->jobs) {
		j.calculateEarliestStartTimes();
		j.calculateDuration();
	}
	auto maxDuration = [](const Job &a, const Job &b) {
		return a.getDuration() < b.getDuration();
	};
	auto longestTask = std::max_element(jobs.begin(), jobs.end(), maxDuration);
//	std::cout << *longestTask;
	for (Job &j : this->jobs) {
		j.calculateSlack(longestTask->getDuration());
		std::cout << j;
	}
}

unsigned short JobFactory::getNMachines() const {
	return this->nMachines;
}

unsigned short JobFactory::getNJobs() const {
	return this->nJobs;
}
