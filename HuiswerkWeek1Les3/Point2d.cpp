/*
 * Point2d.cpp
 *
 *  Created on: 2 Feb 2024
 *      Author: woutn
 */

#include <iostream>

#include "Point2d.h"

Point2d::Point2d(): x(0), y(0) {
	std::cout << __PRETTY_FUNCTION__ << std::endl;
}

Point2d::Point2d(short x, short y): x(x), y(y) {
	std::cout << __PRETTY_FUNCTION__ << std::endl;
}

Point2d::~Point2d() {
	std::cout << __PRETTY_FUNCTION__ << std::endl;
}

Point2d& Point2d::operator=(const Point2d & rhs) {
	std::cout << __PRETTY_FUNCTION__ << std::endl;
	if(this != &rhs) {
		this->x = rhs.x;
		this->y = rhs.y;
	}
	return *this;
}

bool Point2d::operator<(const Point2d & rhs) const {
	std::cout << __PRETTY_FUNCTION__ << std::endl;
	return this->x + this->y < rhs.x + rhs.y;
//	return !this->operator>(rhs);
}

bool Point2d::operator>(const Point2d & rhs) const {
	return !this->operator<(rhs);
}

short Point2d::getX() const{
	return this->x;
}

short Point2d::getY() const{
	return this->y;
}

