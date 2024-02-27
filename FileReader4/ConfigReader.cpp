/*
 * ConfigReader.cpp
 *
 *  Created on: 22 Feb 2024
 *      Author: woutn
 */

#include "ConfigReader.h"

#include <sstream>
#include <iostream>

ConfigReader::ConfigReader() :
		nJobs(0), nMachines(0) {
}

ConfigReader::ConfigReader(const std::string &filename) :
		filename(filename), nJobs(0), nMachines(0) {
	this->configFile.open(filename, std::ios::binary);
}

ConfigReader::~ConfigReader() {
}

bool ConfigReader::fileFound() {
	return configFile.is_open();
}

bool ConfigReader::readConfig() {
	if (!this->fileFound()) {
		return false;
	}
	this->readFirstLine();
	std::string jobLine;
	while (std::getline(this->configFile, jobLine)) {
		std::istringstream jobStream(jobLine);
		unsigned short value;
		std::vector<unsigned short> currentJob;
		while (jobStream >> value) {
			currentJob.push_back(value);
		}
		if (!currentJob.empty()) {
			configValues.push_back(currentJob);
		}
	}
	return true;
}

const std::vector<std::vector<unsigned short>>& ConfigReader::getConfigValues() {
	return this->configValues;
}

unsigned short ConfigReader::getNJobs() {
	return this->nJobs;
}

unsigned short ConfigReader::getNMachines() {
	return this->nMachines;
}

ConfigReader::ConfigReader(const ConfigReader &rhs) :
		filename(rhs.filename), nJobs(rhs.nJobs), nMachines(rhs.nMachines), configValues(
				rhs.configValues) {
	this->configFile.open(filename, std::ios::binary);
}

void ConfigReader::readFirstLine() {
	if (!this->fileFound()) {
		return;
	}
	this->configFile >> this->nJobs >> this->nMachines;
}

void ConfigReader::printConfig() {
	std::cout << "Jobs: " << this->nJobs << " Machines: " << this->nMachines
			<< std::endl;
	for (std::vector<unsigned short> jobs : this->configValues) {
		for (unsigned short task : jobs) {
			std::cout << task << ' ';
		}
		std::cout << std::endl;
	}
}
