#include <iostream>
#include <fstream>
#include <vector>

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

	std::vector<std::vector<unsigned short>> v;

	for (int i = 0; i < nJobs; i++) {
		v.push_back( { });
	}

	unsigned short value;
	for (std::vector<unsigned short> vInner : v) {
		while (istrm >> value) {
			vInner.push_back(value);
			if (istrm.peek() == '\n' || istrm.peek() == '\r') { // detect '\n'
				std::cout << "regel" << std::endl;
				break;
			}
		}
		for (unsigned short val : vInner) {
			std::cout << val << ' ';
		}
	}

	for (std::vector<unsigned short> vInner : v) {
		for (unsigned short val : vInner) {
			std::cout << val << ' ';
		}
		std::cout << std::endl;
	}

	return 0;
}
