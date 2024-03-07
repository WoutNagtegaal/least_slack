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

Job::Job(unsigned short jobId, const std::vector<unsigned short> &config) :
		jobId(jobId), duration(0), slack(0) {
	// Tasks accept at first the ID, then the machine nr and last the duration
	// in the config no ID is stored, so this is the iterator
	// afterwards each task is stored in a pair of machine nr - duration
	// this is why i is increased by 2 each time and the ID is divided by 2
	for (unsigned short i = 0; i < config.size(); i += 2) {
		tasks.push_back(Task(i / 2, config[i], config[i + 1]));
	}
}

Job::Job(const Job &rhs) :
		jobId(rhs.jobId), tasks(rhs.tasks), duration(rhs.duration), slack(
				rhs.slack) {
}

bool Job::startNextTask(unsigned short currentTime) {
	// some checks if the job is already done
	// a finished job can of course not be started
	if (!this->taskAvailable()) {
		return false;
	}
	if (this->jobDone(currentTime)) {
		return false;
	}
	// getNextTask() returns the last task if no next task is found because a task must!!! be returned
	// this is why I check if this task is already started
	Task &nextTask = this->getNextTask();
	if (nextTask.taskStarted()) {
		return false;
	}
	nextTask.startTask(currentTime);
	return true;
}

Task& Job::getNextTask() {
	// sort the tasks so I will get the actual first task
	this->sortTasksByTaskId();
	auto taskDone = [](const Task &t) {
		return !t.taskStarted();
	};
	auto next = std::find_if(tasks.begin(), tasks.end(), taskDone);
	// if there is a task found that task can be returned
	if (next != tasks.end()) {
		return *next;
	}
	// if no task is found however the last task is returned.
	// using references it isn't possible to return NULL like with c pointers
	// so I had to return something, and this seemed the most logical
	// using this task it can be checked if the job has started, so at least the calling function can validate
	// didn't want to just return next directly as that may lead do undefined behaviour
	return tasks[tasks.size() - 1];
}

void Job::calculateDuration() {
	// the last task to be executed can be used to calculate the total duration
	// this task is the last, so when this task is done the complete job is done
	// first I sort them. again....
	this->sortTasksByTaskId();
	auto lastTask = tasks.end() - 1; // the task before end() is always the last
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
	// I want the task before the current task to read the duration and earliest start time
	// these can be added together to get the earliest start time of the current task
	auto getPreviousTask = [task](const Task &a) {
		return a.getTaskId() == ((task.getTaskId()) - 1);
	};
	auto prev = std::find_if(tasks.begin(), tasks.end(), getPreviousTask);
	if (prev == tasks.end()) // if no task is found I rather stupidly assume it is the first
		return 0;
	return (prev->getEarliestStartTime() + prev->getDuration());
}

bool Job::jobDone(unsigned short currentTime) {
	for (const Task &t : tasks) {
		if (!t.taskDone(currentTime)) {
			return false;
		}
	}
	// if all tasks are done the job is also done
	return true;
}

bool Job::taskAvailable() {
	for (const Task &t : tasks) {
		if (!t.taskStarted()) {
			return true;
		}
	}
	// if all tasks have started already there is no task left to execute
	return false;
}

bool Job::jobBusy(unsigned short currentTime) {
	for (const Task &t : tasks) {
		if (t.taskBusy(currentTime)) {
			return true;
		}
	}
	// if no task is busy the job is also not busy
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

bool Job::operator <(const Job &rhs) const {
	// at first I want to sort by slack, if both slacks are the same I sort by job ID instead
	// otherwise I won't get the exact same order as the teacher
	if (this->slack != rhs.slack) {
		return this->slack < rhs.slack;
	}
	return this->jobId < rhs.jobId;
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
