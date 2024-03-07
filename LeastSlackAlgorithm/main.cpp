#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

#include "ConfigReader.h"
#include "Task.h"
#include "Job.h"
#include "JobFactory.h"

#include <chrono>
unsigned long long millis();

int main(int argc, char **argv) {
	// check if there were any arguments filled in from the command line
	if (argc < 2) {
		std::cerr << "Please enter a filename as the first argument"
				<< std::endl;
		return 1;
	}

	ConfigReader config(argv[1]);
	if (!config.fileFound()) {
		std::cout << "File not found" << std::endl;
		return 1;
	}
	config.readConfig();
	// created a copy constructor in the jobfactories class that accepts ConfigReader objects
	// this saves having to read all getter functions everytime a jobfactory is made
	JobFactory jobFactory(config);

	unsigned long long start = millis();

	jobFactory.schedule();

	std::cout << millis() - start << std::endl;

	jobFactory.printEndResults();
	return 0;
}

unsigned long long millis() {
	auto now = std::chrono::system_clock::now();
	return std::chrono::duration_cast<std::chrono::milliseconds>(
			now.time_since_epoch()).count();
}
