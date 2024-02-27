#include <iostream>
#include "Point2d.h"

int main(int argc, char **argv) {
	// default constructor
	Point2d p1;
	std::cout << "(" << p1.getX() << ", " << p1.getY() << ")" << std::endl;

	// constructor with 2 parameters
	Point2d p2(3, 4);
	std::cout << "(" << p2.getX() << ", " << p2.getY() << ")" << std::endl;

	// Making Copies
	Point2d p3 = p2; // Copy constructor, same as Point2d p3(p2);

	p3 = p2; // operator=

	// comparing instances
	if (p3 < p1) {
		std::cout << "(p3 < p1) := true" << std::endl;
	} else {
		std::cout << "(p3 < p1) := false" << std::endl;
	}

}
