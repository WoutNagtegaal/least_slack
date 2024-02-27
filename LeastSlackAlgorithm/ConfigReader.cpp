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

ConfigReader::ConfigReader(const ConfigReader &rhs) :
		filename(rhs.filename), nJobs(rhs.nJobs), nMachines(rhs.nMachines), configValues(
				rhs.configValues) {
	this->configFile.open(filename, std::ios::binary);
}

bool ConfigReader::readConfig() {
	// if the file is found the config can be read
	if (!this->fileFound()) {
		return false;
	}
	// first line contains specific values, so read these seperately
	this->readFirstLine();

	// create a string that all lines will be read into
	std::string jobLine;
	while (std::getline(this->configFile, jobLine)) {
		std::istringstream jobStream(jobLine);
		unsigned short value;
		std::vector<unsigned short> currentJob;
		while (jobStream >> value) {
			currentJob.push_back(value);
		}
		// it still reads the first line even though it was already read before
		// this results in an empty line, so we filter it out here
		if (!currentJob.empty()) {
			configValues.push_back(currentJob);
		}
	}
	return true;
}

void ConfigReader::readFirstLine() {
	if (!this->fileFound()) {
		return;
	}
	this->configFile >> this->nJobs >> this->nMachines;
}

bool ConfigReader::fileFound() {
	return configFile.is_open();
}

const std::vector<std::vector<unsigned short>>& ConfigReader::getConfigValues() const {
	return this->configValues;
}

unsigned short ConfigReader::getNJobs() const {
	return this->nJobs;
}

unsigned short ConfigReader::getNMachines() const {
	return this->nMachines;
}

ConfigReader::~ConfigReader() {
}

std::ostream& operator <<(std::ostream &os, const ConfigReader &configReader) {
	os << "Jobs: " << configReader.getNJobs() << " Machines: " << configReader.getNMachines()
			<< std::endl;
	for (std::vector<unsigned short> jobs : configReader.getConfigValues()) {
		for (unsigned short task : jobs) {
			std::cout << task << ' ';
		}
		std::cout << std::endl;
	}
	return os;
}
