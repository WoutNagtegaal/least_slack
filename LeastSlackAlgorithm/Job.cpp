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

void Job::calculateEarliestStartTimes() {
	// sorting all task by taskId to loop in the right order
	// otherwise the earliest starttime of the previous task will not have been set
	auto taskIdSort = [](const Task &a, const Task &b) {
		return a.getTaskId() < b.getTaskId();
	};
	std::sort(this->tasks.begin(), this->tasks.end(), taskIdSort);

	for (Task &t : tasks) {
		// first task does not have a previous task so it is set directly
		if (t.getTaskId() == 0) {
			t.setEarliestStartTime(0); // TODO make this set the current time
			continue;
		}
		t.setEarliestStartTime(calculateEarliestStartTime(t));
	}
}

unsigned short Job::calculateEarliestStartTime(Task &task) {
	// we want the task before the current task to read the duration and earliest start time
	// these can be added together to get the earliest start time of the current task
	auto getPreviousTask = [task](const Task &a) {
		return a.getTaskId() == ((task.getTaskId()) - 1);
	};
	auto prev = std::find_if(tasks.begin(), tasks.end(), getPreviousTask);
	// TODO validation if a task is found
	return (prev->getEarliestStartTime() + prev->getDuration());
}

void Job::calculateDuration() {
	// the last task to be executed can be used to calculate the total duration
	// this task is the last, so when this task is done the complete job is done
	auto taskLastId = [](const Task &a, const Task &b) {
		return a.getTaskId() < b.getTaskId();
	};
	auto lastTask = std::max_element(tasks.begin(), tasks.end(), taskLastId);
	this->duration = lastTask->getDuration() + lastTask->getEarliestStartTime();
}

void Job::calculateSlack(unsigned short maxDuration) {
	// slack is calculated by taking the duration of the longest task an subtracting
	// the duration of this task
	this->slack = maxDuration - this->duration;
}

// TODO remove this one, this is calculated within calculate slack
void Job::setSlack(unsigned short slack) {
	this->slack = slack;
}

unsigned short Job::getSlack() const {
	return this->slack;
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

Job::~Job() {
}

std::ostream& operator <<(std::ostream &os, const Job &job) {
	os << "Job nr " << job.getJobId() << " takes " << job.getDuration()
			<< " sec with " << job.getSlack()
			<< " sec slack with the following tasks: " << std::endl;
	for (Task &t : job.getTasks()) {
		os << t;
	}
	return os;
}
