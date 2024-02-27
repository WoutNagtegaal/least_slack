/*
 * Task.cpp
 *
 *  Created on: 22 Feb 2024
 *      Author: woutn
 */

#include "Task.h"

Task::Task() :
		taskId(0), machineNr(0), duration(0) {
}

Task::Task(unsigned short taskId, unsigned short machineNr,
		unsigned short duration) :
		taskId(taskId), machineNr(machineNr), duration(duration) {
}

Task::Task(const Task &rhs) :
		Task(rhs.getTaskId(), rhs.getMachineNr(), rhs.getDuration()) {
}

Task::~Task() {
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

std::ostream& operator <<(std::ostream &os, const Task &task) {
	os << "Task nr " << task.getTaskId();
	os << " on machine nr " << task.getMachineNr();
	os << " takes " << task.getDuration() << " sec" << std::endl;
	return os;
}
