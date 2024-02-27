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
	// don't save the config vector directly
	// we want to save it into the correct classes
	this->initJobs(config);
}

JobFactory::JobFactory(const JobFactory &rhs) :
		nMachines(rhs.nMachines), nJobs(rhs.nJobs), jobs(rhs.jobs) {
}

JobFactory::JobFactory(const ConfigReader &rhs) {
	// made this copy constructor because the ConfigReader holds all required values
	// to create a JobFactory. this make it easier to create a JobFactory in the main
	this->nMachines = rhs.getNMachines();
	this->nJobs = rhs.getNJobs();
	this->initJobs(rhs.getConfigValues());
}

void JobFactory::initJobs(std::vector<std::vector<unsigned short> > config) {
	// id is decided by location in the vector, so we have to keep track of it manually
	unsigned short id = 0;
	for (auto job : config) {
		this->jobs.push_back(Job(id, job));
		id++;
	}
}

// TODO this is a stupid test function
// replace with seperate functions
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

const std::vector<Job>& JobFactory::getJobs() const {
	return this->jobs;
}

JobFactory::~JobFactory() {
	// TODO Auto-generated destructor stub
}

std::ostream& operator <<(std::ostream &os, const JobFactory &jobFactory) {
	std::cout << "Jobfactory with " << jobFactory.getNJobs() << " jobs and "
			<< jobFactory.getNMachines() << " machines" << std::endl;

	for (const Job &j : jobFactory.getJobs()) {
		os << j;
	}
	return os;
}
