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

class JobFactory {
public:
	JobFactory();
	JobFactory(std::vector<std::vector<unsigned short>> config);
	JobFactory(const JobFactory &rhs);
	JobFactory(const ConfigReader &rhs);
	virtual ~JobFactory();

	std::vector<Job> getJobs() const;

private:
	std::vector<Job> jobs;

};

std::ostream& operator<<(std::ostream &os, const JobFactory &jobFactory);

#endif /* JOBFACTORY_H_ */
