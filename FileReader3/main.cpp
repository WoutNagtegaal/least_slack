#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

#include "ConfigReader.h"

int main(int argc, char **argv) {
	std::string filename = "config.txt";

	std::ifstream istrm(filename, std::ios::binary);
	if (!istrm.is_open()) {
		std::cout << "failed to open " << filename << '\n';
		return 1;
	}

	int nJobs = 0;
	int nMachines = 0;
	std::string s;
	istrm >> nJobs >> nMachines;
	std::cout << "Jobs: " << nJobs << " Machines: " << nMachines << std::endl;

	std::vector<std::vector<unsigned short>> configValues;

	std::string jobLine;
	while (std::getline(istrm, jobLine)) {
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

	for (std::vector<unsigned short> jobs : configValues) {
		for (unsigned short task : jobs) {
			std::cout << task << ' ';
		}
		std::cout << std::endl;
	}

	ConfigReader c(filename);
	if (c.fileFound()) {
		std::cout << "gevonden" << std::endl;
		c.readConfig();
		std::cout << "Jobs: " << c.getNJobs() << " Machines: "
				<< c.getNMachines() << std::endl;
		std::vector<std::vector<unsigned short>> v = c.getConfigValues();
		for (std::vector<unsigned short> jobs : v) {
			for (unsigned short task : jobs) {
				std::cout << task << ' ';
			}
			std::cout << std::endl;
		}
	}

	ConfigReader c2("config1.txt");
	if (c2.fileFound()) {
		std::cout << "gevonden" << std::endl;
		c2.readConfig();
		c2.printConfig();
	}
	return 0;
}
