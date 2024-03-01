#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

#include "ConfigReader.h"
#include "Task.h"
#include "Job.h"
#include "JobFactory.h"

int main(int argc, char **argv) {
	std::cout << "Starting program.........." << std::endl;
	// check if there were any arguments filled in from the command line
	if (argc < 2) {
		std::cerr << "Please enter a filename as the first argument"
				<< std::endl;
		return 1;
	}

	ConfigReader config(argv[1]);
	std::cout << argv[1] << std::endl;

	if (!config.fileFound()) {
		std::cout << "not found" << std::endl;
		return 1;
	}

	std::cout << "found" << std::endl;
	config.readConfig();
	std::cout << config;
	std::cout
			<< "------------------------------initial------------------------------"
			<< std::endl;
	// created a copy constructor in the jobfactories class that accepts ConfigReader objects
	// this saves having to read all getter functions everytime a jobfactory is made
	JobFactory jobFactory(config);

	std::cout << jobFactory;
	std::cout
			<< "------------------------------after sort------------------------------"
			<< std::endl;
	jobFactory.taskTests();
	jobFactory.sortJobsByJobId();
	std::cout
			<< "------------------------------end results------------------------------"
			<< std::endl;
	std::cout << jobFactory;

	return 0;
}
