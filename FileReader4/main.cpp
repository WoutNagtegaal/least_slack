#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

#include "ConfigReader.h"
#include "Task.h"
#include "Job.h"

int main(int argc, char **argv) {
	std::vector<ConfigReader> configs;
	configs.push_back(ConfigReader("testing.txt"));
//	configs.push_back(ConfigReader("config.txt"));
//	configs.push_back(ConfigReader("config1.txt"));
//	configs.push_back(ConfigReader("config2.txt"));
//	configs.push_back(ConfigReader("config3.txt"));
//	configs.push_back(ConfigReader("config4.txt"));
//	configs.push_back(ConfigReader("config5.txt"));
//	configs.push_back(ConfigReader("config6.txt"));

	for (ConfigReader c : configs) {
		if (c.fileFound()) {
			std::cout << "gevonden" << std::endl;
			c.readConfig();
			c.printConfig();
			for (auto job : c.getConfigValues()) {
				std::vector<Task> tasks;
				for (unsigned short i = 0; i < job.size(); i += 2) {
					tasks.push_back(Task(i / 2, job[i], job[i + 1]));
				}
				for (Task t : tasks) {
					std::cout << t;
				}
			}
		} else {
			std::cout << "niet gevonden" << std::endl;
		}
	}

	std::vector<Job> jobs;
	for (ConfigReader c : configs) {
		if (c.fileFound()) {
			std::cout << "gevonden" << std::endl;
			c.readConfig();
			c.printConfig();
			unsigned short id = 0;
			for (auto job : c.getConfigValues()) {
				jobs.push_back(Job(id, job));
				id++;

			}
		} else {
			std::cout << "niet gevonden" << std::endl;
		}
	}
	for (Job j: jobs) {
		std::cout << j;
	}

	return 0;
}
