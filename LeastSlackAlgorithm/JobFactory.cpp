/*
 * JobFactory.cpp
 *
 *  Created on: 22 Feb 2024
 *      Author: woutn
 */

#include "JobFactory.h"
#include "Job.h"
#include "Task.h"

#include <algorithm>

JobFactory::JobFactory(unsigned short nMachines, unsigned short nJobs,
		std::vector<std::vector<unsigned short>> config) :
		nMachines(nMachines), nJobs(nJobs), currentTime(0) {
	// don't save the config vector directly
	// we want to save it into the correct classes
	this->initJobs(config);
	this->initMachines();
}

JobFactory::JobFactory(const JobFactory &rhs) :
		nMachines(rhs.nMachines), nJobs(rhs.nJobs), currentTime(0), jobs(
				rhs.jobs), machines(rhs.machines) {
}

JobFactory::JobFactory(const ConfigReader &rhs) {
	// made this copy constructor because the ConfigReader holds all required values
	// to create a JobFactory. this make it easier to create a JobFactory in the main
	this->nMachines = rhs.getNMachines();
	this->nJobs = rhs.getNJobs();
	this->initJobs(rhs.getConfigValues());
	this->initMachines();
}

void JobFactory::initJobs(std::vector<std::vector<unsigned short> > config) {
	// id is decided by location in the vector, so we have to keep track of it manually
	unsigned short id = 0;
	for (auto job : config) {
		this->jobs.push_back(Job(id, job));
		id++;
	}
}

void JobFactory::initMachines() {
	for (int i = 0; i < nMachines; i++) {
		machines.push_back(Machine());
	}
}

bool JobFactory::allJobsDone() {
	return jobs.size() == 0;
}

void JobFactory::sortJobsByJobId() {
	// sorts jobs by ID for easier visualisation
	auto jobIdSort = [](const Job &a, const Job &b) {
		return a.getJobId() < b.getJobId();
	};
	std::sort(jobs.begin(), jobs.end(), jobIdSort);
}

void JobFactory::calculateSlack() {
	// preparation for the slack calculation
	for (Job &j : this->jobs) {
		if (j.jobBusy(currentTime))
			continue;
		Task &current = j.getNextTask();
		if (current.taskDone(currentTime))
			continue;
		unsigned short machineNr = current.getMachineNr();
		if (machines[machineNr].machineBusy(currentTime)) {
			j.calculateEarliestStartTimes(machines[machineNr].getFreeFrom());
		} else {
			j.calculateEarliestStartTimes(currentTime);
		}
		j.calculateDuration();
	}
	// making seperate variable so it isn't calcuted for every job
	unsigned short longestJobDuration = this->getLongestJobDuration();
	for (Job &j : this->jobs) {
		j.calculateSlack(longestJobDuration);
//		std::cout << j;
	}
}

void JobFactory::sortJobsBySlack() {
	// sorts jobs by slack to decide the next task
	std::sort(jobs.begin(), jobs.end());
}

void JobFactory::printEndResults() {
	auto sort = [](const Job &a, const Job &b) {
		return a.getJobId() < b.getJobId();
	};
	std::sort(finishedJobs.begin(), finishedJobs.end(), sort);
	for (Job &j : finishedJobs) {
		std::cout << j.getJobId() << "\t";
		j.printEndResult();
	}
}

void JobFactory::removeFinishedJobs() {
	for (auto j = jobs.begin(); j < jobs.end();) {
		if (j->jobDone(currentTime)) {
			finishedJobs.push_back(*j);
			j = jobs.erase(j);
		} else {
			++j;
		}
	}
}

unsigned short JobFactory::getLongestJobDuration() {
	auto maxDuration = [](const Job &a, const Job &b) {
		return a.getDuration() < b.getDuration();
	};
	auto longestTask = std::max_element(jobs.begin(), jobs.end(), maxDuration);
	return longestTask->getDuration();
}

void JobFactory::schedule() {
	bool done = false;
	while (!done) {
		this->removeFinishedJobs();
		this->calculateSlack();
		this->sortJobsBySlack();

		for (Job &j : jobs) {
			if (j.jobBusy(currentTime)) {
				continue;
			}
			Task &current = j.getNextTask();
			unsigned short duration = current.getDuration();
			unsigned short machineNr = current.getMachineNr();
			if (!machines[machineNr].machineBusy(currentTime)) {
				j.startNextTask(currentTime);
				machines[machineNr].startMachine(currentTime, duration);
			}
		}

		++currentTime;
		if (allJobsDone()) {
			done = true;
		}
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
