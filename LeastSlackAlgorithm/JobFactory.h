/*
 * JobFactory.h
 *
 *  Created on: 22 Feb 2024
 *      Author: woutn
 */

#ifndef JOBFACTORY_H_
#define JOBFACTORY_H_

#include <vector>

#include "Job.h"
#include "ConfigReader.h"
#include "Machine.h"

typedef std::vector<unsigned short> growyBoy;

class JobFactory {
public:
	JobFactory() = delete;
	JobFactory(unsigned short nMachines, unsigned short nJobs,
			std::vector<std::vector<unsigned short>> config);
	JobFactory(const JobFactory &rhs);
	JobFactory(const ConfigReader &rhs);

	void initJobs(std::vector<std::vector<unsigned short>> config);
	void calculateSlack();
	void sortJobsByJobId();
	void sortJobsBySlack();

	void printEndResults();

	void taskTests(); // replace with the proper devided functions!!!!!!!!!

	unsigned short getNMachines() const;
	unsigned short getNJobs() const;
	const std::vector<Job>& getJobs() const;

	virtual ~JobFactory();

private:
	unsigned short getLongestJobDuration();

	unsigned short nMachines;
	unsigned short nJobs;
	unsigned short currentTime;
	std::vector<Job> jobs;

};

std::ostream& operator<<(std::ostream &os, const JobFactory &jobFactory);

#endif /* JOBFACTORY_H_ */
