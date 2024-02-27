#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

#include "ConfigReader.h"
#include "Task.h"
#include "Job.h"
#include "JobFactory.h"

int main(int argc, char **argv) {
	// check if there were any arguments filled in from the command line
	if (argc < 2) {
		std::cout << "Please enter a filename as the first argument"
				<< std::endl;
		return 1;
	}

	// this was made with the thought to make it possible to load multiple files, should edit it to only
	// create one config from the file in the arguments
	std::vector<ConfigReader> configs;
	std::cout << argv[1] << std::endl;
	configs.push_back(ConfigReader(argv[1]));

	// same for this one
	std::vector<JobFactory> jobFactories;
	for (ConfigReader c : configs) {
		// c will try to open the file, if it was found we can use it to read the config to the job factory
		if (c.fileFound()) {
			std::cout << "found" << std::endl;
			c.readConfig();
			std::cout << c;
			// created a copy constructor in the jobfactories class that accepts ConfigReader objects
			// this saves having to read all getter functions everytime a jobfactory is made
			jobFactories.push_back(c);
		} else {
			std::cout << "not found" << std::endl;
		}
	}
	for (JobFactory j : jobFactories) {
		// tasktests does temporary tests, this has to be replaced with the actual final logic
		j.taskTests();
		std::cout << j;
	}

	return 0;
}
