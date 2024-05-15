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
		const std::vector<std::vector<unsigned short>> &config) :
		nMachines(nMachines), nJobs(nJobs), currentTime(0) {
	// don't save the config vector directly
	// we want to save it into the correct classes
	this->initJobs(config);
	this->initMachines();
}

// this one exists mostly because i first wanted to make a vector with jobfactories
// so i could execute multiple files at once
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

void JobFactory::initJobs(
		const std::vector<std::vector<unsigned short>> &config) {
	// id is decided by location in the vector, so we have to keep track of it manually
	unsigned short id = 0;
	for (const std::vector<unsigned short> &job : config) {
		// each row of the vector contains a job
		this->jobs.emplace_back(Job(id, job));
		++id;
	}
}

void JobFactory::initMachines() {
	// the machine ID is just the location in the vector
	// no need to make it more complicated than necessary
	for (int i = 0; i < nMachines; i++) {
		machines.push_back(Machine());
	}
}

bool JobFactory::allJobsDone() {
	for(Job&j:jobs) {
		if (!j.jobDone(currentTime)) {
			return false;
		}
	}
	return true;
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
	// is also not const, the earliest start times and slack will be written
	for (Job &j : this->jobs) {
		// busy jobs already have the correct values saved, so they don't have
		// to be updated every time
		if (j.jobBusy(currentTime) || j.jobDone(currentTime))
			continue;
		Task &current = j.getNextTask();

		unsigned short machineNr = current.getMachineNr();
		// tasks that use an already busy machine cannot be executed until it is free
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
	}
}

void JobFactory::sortJobsBySlack() {
	// sorts jobs by slack to decide the next task
	std::sort(jobs.begin(), jobs.end());
}

void JobFactory::printEndResults() {
	// print the finished job in order of job id, else checks will fail
	this->sortJobsByJobId();
	for (Job &j : jobs) {
		std::cout << j.getJobId() << "\t";
		j.printEndResult();
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
	while (!allJobsDone()) {
		this->calculateSlack();
		this->sortJobsBySlack();

		// update every job, not const because a new task will possibly start
		for (Job &j : jobs) {
			if (j.jobBusy(currentTime) || j.jobDone(currentTime)) {
				continue;
			}
			Task &current = j.getNextTask();
			unsigned short duration = current.getDuration();
			unsigned short machineNr = current.getMachineNr();
			// if a machine is already busy another task cannot be started
			if (!machines[machineNr].machineBusy(currentTime)) {
				j.startNextTask(currentTime);
				globalTimer.insert(current.getEndTime());
				machines[machineNr].startMachine(currentTime, duration);
			}
		}
//		std::sort(earliestTimes.begin(), earliestTimes.end());
		if (!globalTimer.empty()) {
			currentTime = *globalTimer.begin();
			globalTimer.erase(globalTimer.begin());
		} else {
			++currentTime;
		}
//		std::cout << currentTime << std::endl;
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
