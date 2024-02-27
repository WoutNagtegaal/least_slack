#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

#include "ConfigReader.h"
#include "Task.h"
#include "Job.h"
#include "JobFactory.h"

int main(int argc, char **argv) {
	std::vector<ConfigReader> configs;
	std::cout << argv[1] << std::endl;
	configs.push_back(ConfigReader(argv[1]));
//	configs.push_back(ConfigReader("config.txt"));
//	configs.push_back(ConfigReader("config1.txt"));
//	configs.push_back(ConfigReader("config2.txt"));
//	configs.push_back(ConfigReader("config3.txt"));
//	configs.push_back(ConfigReader("config4.txt"));
//	configs.push_back(ConfigReader("config5.txt"));
//	configs.push_back(ConfigReader("config6.txt"));

	std::vector<JobFactory> jobFactories;
	for (ConfigReader c : configs) {
		if (c.fileFound()) {
			std::cout << "gevonden" << std::endl;
			c.readConfig();
			c.printConfig();
			jobFactories.push_back(c);
		} else {
			std::cout << "niet gevonden" << std::endl;
		}
	}
	for (JobFactory j: jobFactories) {
		j.taskTests();
		std::cout << j;
	}

	return 0;
}
