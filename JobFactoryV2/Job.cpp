/*
 * Job.cpp
 *
 *  Created on: 22 Feb 2024
 *      Author: woutn
 */

#include "Job.h"

#include <algorithm>

Job::Job() :
		jobId(0), duration(0), slack(0) {
}

Job::Job(unsigned short jobId, std::vector<unsigned short> config) :
		jobId(jobId), duration(0), slack(0) {
	for (unsigned short i = 0; i < config.size(); i += 2) {
		tasks.push_back(Task(i / 2, config[i], config[i + 1]));
	}
}

Job::Job(const Job &rhs) :
		jobId(rhs.jobId), tasks(rhs.tasks), duration(rhs.duration), slack(
				rhs.slack) {
}

Job::~Job() {
	// TODO Auto-generated destructor stub
}

std::ostream& operator <<(std::ostream &os, const Job &job) {
	os << "Job nr " << job.getJobId() << " takes " << job.getDuration()
			<< " sec with " << job.getSlack() <<" sec slack with the following tasks: " << std::endl;
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

unsigned short Job::getDuration() const {
	return this->duration;
}

void Job::calculateEarliestStartTimes() {
	auto taskIdSort = [](const Task &a, const Task &b) {
		return a.getTaskId() < b.getTaskId();
	};
	std::sort(this->tasks.begin(), this->tasks.end(), taskIdSort);

	for (Task &t : tasks) {
		if (t.getTaskId() == 0) {
			t.setEarliestStartTime(0);
			continue;
		}
		t.setEarliestStartTime(calculateEarliestStartTime(t));
	}
}

void Job::calculateDuration() {
	auto taskLastId = [](const Task &a, const Task &b) {
		return a.getTaskId() < b.getTaskId();
	};
	auto lastTask = std::max_element(tasks.begin(), tasks.end(), taskLastId);
//	std::cout << *lastTask;
//	std::cout << lastTask->getDuration() + lastTask->getEarliestStartTime()
//			<< std::endl;
	this->duration = lastTask->getDuration() + lastTask->getEarliestStartTime();
}

void Job::calculateSlack(unsigned short maxDuration) {
	this->slack = maxDuration - this->duration;
}

void Job::setSlack(unsigned short slack) {
	this->slack = slack;
}

unsigned short Job::getSlack() const {
	return this->slack;
}

unsigned short Job::calculateEarliestStartTime(Task &task) {
	auto getPreviousTask = [task](const Task &a) {
		return a.getTaskId() == ((task.getTaskId()) - 1);
	};
	auto prev = std::find_if(tasks.begin(), tasks.end(), getPreviousTask);
	return (prev->getEarliestStartTime() + prev->getDuration());
}
