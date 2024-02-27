/*
 * ConfigReader.h
 *
 *  Created on: 22 Feb 2024
 *      Author: woutn
 */

#ifndef CONFIGREADER_H_
#define CONFIGREADER_H_

#include <string>
#include <fstream>
#include <vector>

class ConfigReader {
public:
	ConfigReader();
	ConfigReader(const std::string &filename);
	virtual ~ConfigReader();

	bool fileFound();
	bool readConfig();

	std::vector<std::vector<unsigned short>> getConfigValues();

	unsigned short getNJobs();
	unsigned short getNMachines();

	void printConfig();

private:
	void readFirstLine();

	std::string filename;
	std::ifstream configFile;

	unsigned short nJobs;
	unsigned short nMachines;
	std::vector<std::vector<unsigned short>> configValues;
};

#endif /* CONFIGREADER_H_ */
