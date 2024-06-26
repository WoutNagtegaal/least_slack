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
	explicit ConfigReader(const std::string &filename);
	ConfigReader(const ConfigReader &rhs);

	bool readConfig();
	bool fileFound();

	const std::vector<std::vector<unsigned short>>& getConfigValues() const;
	unsigned short getNJobs() const;
	unsigned short getNMachines() const;

	virtual ~ConfigReader();

private:
	void readFirstLine();

	std::string filename;
	std::ifstream configFile;

	unsigned short nJobs;
	unsigned short nMachines;
	std::vector<std::vector<unsigned short>> configValues;
};

std::ostream& operator<<(std::ostream &os, const ConfigReader &configReader);

#endif /* CONFIGREADER_H_ */
