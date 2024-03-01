/*
 * Task.cpp
 *
 *  Created on: 22 Feb 2024
 *      Author: woutn
 */

#include "Task.h"

Task::Task() :
		taskId(0), machineNr(0), duration(0), earliestStartTime(0), startTime(
				0), endTime(0) {
}

Task::Task(unsigned short taskId, unsigned short machineNr,
		unsigned short duration) :
		taskId(taskId), machineNr(machineNr), duration(duration), earliestStartTime(
				0), startTime(0), endTime(0) {
}

Task::Task(const Task &rhs) :
		taskId(rhs.taskId), machineNr(rhs.machineNr), duration(rhs.duration), earliestStartTime(
				rhs.earliestStartTime), startTime(rhs.startTime), endTime(
				rhs.endTime) {
}

bool Task::taskStarted() const {
	return startTime != endTime;
}

bool Task::taskBusy(unsigned short currentTime) const {
	if (!this->taskStarted()) {
		return false;
	}
	return currentTime >= startTime && currentTime < endTime;
}

bool Task::taskDone(unsigned short currentTime) const {
	if (!this->taskStarted()) {
		return false;
	}
	return currentTime >= endTime;
}

void Task::startTask(unsigned short startTime) {
	this->startTime = startTime;
	this->endTime = startTime + this->duration;
}

unsigned short Task::getTaskId() const {
	return this->taskId;
}

unsigned short Task::getDuration() const {
	return this->duration;
}

unsigned short Task::getMachineNr() const {
	return this->machineNr;
}

unsigned short Task::getEarliestStartTime() const {
	return this->earliestStartTime;
}

unsigned short Task::getStartTime() const {
	return this->startTime;
}

unsigned short Task::getEndTime() const {
	return this->endTime;
}

void Task::setEarliestStartTime(unsigned short earliestStartTime) {
	this->earliestStartTime = earliestStartTime;
}

void Task::setStartTime(unsigned short startTime) {
	this->startTime = startTime;
}

void Task::setEndTime(unsigned short endTime) {
	this->endTime = endTime;
}

Task::~Task() {
}

std::ostream& operator <<(std::ostream &os, const Task &task) {
	os << "Task nr " << task.getTaskId();
	os << " on machine nr " << task.getMachineNr();
	os << " takes " << task.getDuration() << " sec";
	os << " begins at earliest on t=" << task.getEarliestStartTime() << "sec";
	os << " starts at " << task.getStartTime() << " sec and ends at "
			<< task.getEndTime() << " sec" << std::endl;
	return os;
}
