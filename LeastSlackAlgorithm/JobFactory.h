/*
 * JobFactory.h
 *
 *  Created on: 22 Feb 2024
 *      Author: woutn
 */

#ifndef JOBFACTORY_H_
#define JOBFACTORY_H_

#include <vector>
#include <set>

#include "Job.h"
#include "ConfigReader.h"
#include "Machine.h"

typedef std::vector<unsigned short> growyBoy;

class JobFactory {
public:
	JobFactory() = delete;
	JobFactory(unsigned short nMachines, unsigned short nJobs,
			const std::vector<std::vector<unsigned short>> &config);
	JobFactory(const JobFactory &rhs);
	explicit JobFactory(const ConfigReader &rhs);

	void initJobs(const std::vector<std::vector<unsigned short>> &config);
	void initMachines();
	void calculateSlack();
	void sortJobsByJobId();
	void sortJobsBySlack();

	bool allJobsDone();

	void printEndResults();

	void schedule();

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
	std::vector<Machine> machines;
	std::set<unsigned short> globalTimer;

};

std::ostream& operator<<(std::ostream &os, const JobFactory &jobFactory);

#endif /* JOBFACTORY_H_ */
