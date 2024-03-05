/*
 * Job.cpp
 *
 *  Created on: 22 Feb 2024
 *      Author: woutn
 */

#include "Job.h"

#include <algorithm>
#include <limits>

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

bool Job::startNextTask(unsigned short currentTime) {
	if (!this->taskAvailable()) {
		return false;
	}
//	std::cout << "start next task...." << std::endl;
	if (this->jobDone(currentTime)) {
		return false;
	}
	Task &nextTask = this->getNextTask();
	if (nextTask.taskStarted()) {
		return false;
	}
	nextTask.startTask(currentTime);
//	std::cout << nextTask;
	return true;
}

Task& Job::getNextTask() {
	this->sortTasksByTaskId();
	auto taskDone = [](const Task &t) {
		return !t.taskStarted();
	};
	auto next = std::find_if(tasks.begin(), tasks.end(), taskDone);
	if (next != tasks.end()) {
		return *next;
	}
	return tasks[tasks.size() - 1];
}

const Task& Job::getCurrentTask(unsigned short currentTime) {
	for (const Task &t : tasks) {
		if(t.taskBusy(currentTime)) return t;
	}
	return this->getNextTask();
}

void Job::calculateDuration() {
// the last task to be executed can be used to calculate the total duration
// this task is the last, so when this task is done the complete job is done
//	auto taskLastId = [](const Task &a, const Task &b) {
//		return a.getTaskId() < b.getTaskId();
//	};
//	auto lastTask = std::max_element(tasks.begin(), tasks.end(), taskLastId);
	this->sortTasksByTaskId();
	auto lastTask = tasks.end() - 1;
	this->duration = lastTask->getDuration() + lastTask->getEarliestStartTime();
}

void Job::calculateSlack(unsigned short maxDuration) {
// slack is calculated by taking the duration of the longest task an subtracting
// the duration of this task
	this->slack = maxDuration - this->duration;
}

void Job::printEndResult() {
	std::cout << tasks[0].getStartTime() << "\t"
			<< tasks[tasks.size() - 1].getEndTime() << std::endl;
}

void Job::calculateEarliestStartTimes(unsigned short currentTime) {
// sorting all task by taskId to loop in the right order
// otherwise the earliest starttime of the previous task will not have been set
	if (!this->taskAvailable())
		return;
	this->sortTasksByTaskId();
	auto taskDone = [](const Task &t) {
		return !t.taskStarted();
	};
	auto next = std::find_if(tasks.begin(), tasks.end(), taskDone);
	if (next == tasks.end())
		return;
	for (auto t = next; t != tasks.end(); t++) {
		// first task does not have a previous task so it is set directly
		if (t->getTaskId() == 0 || next == t) {
			t->setEarliestStartTime(currentTime);
			continue;
		}
		t->setEarliestStartTime(calculateEarliestStartTime(*t));
	}
}

unsigned short Job::calculateEarliestStartTime(Task &task) {
// we want the task before the current task to read the duration and earliest start time
// these can be added together to get the earliest start time of the current task
	auto getPreviousTask = [task](const Task &a) {
		return a.getTaskId() == ((task.getTaskId()) - 1);
	};
	auto prev = std::find_if(tasks.begin(), tasks.end(), getPreviousTask);
	if (prev == tasks.end())
		return 0;
	return (prev->getEarliestStartTime() + prev->getDuration());
}

bool Job::jobDone(unsigned short currentTime) {
	for (const Task &t : tasks) {
		if (!t.taskDone(currentTime)) {
			return false;
		}
	}
	return true;
}

bool Job::taskAvailable() {
	for (const Task &t : tasks) {
		if (!t.taskStarted()) {
			return true;
		}
	}
	return false;
}

bool Job::jobBusy(unsigned short currentTime) {
	for (const Task &t : tasks) {
		if (t.taskBusy(currentTime)) {
			return true;
		}
	}
	return false;
}

Job& Job::operator =(const Job &rhs) {
	if (this != &rhs) {
		this->duration = rhs.duration;
		this->jobId = rhs.jobId;
		this->slack = rhs.slack;
		this->tasks = rhs.tasks;
	}
	return *this;
}

void Job::sortTasksByTaskId() {
	std::sort(this->tasks.begin(), this->tasks.end());
}

unsigned short Job::getSlack() const {
	return this->slack;
}

unsigned short Job::getJobId() const {
	return this->jobId;
}

const std::vector<Task>& Job::getTasks() const {
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
	for (const Task &t : job.getTasks()) {
		os << t;
	}
	return os;
}
