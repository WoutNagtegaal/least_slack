/*
 * Point2d.h
 *
 *  Created on: 2 Feb 2024
 *      Author: woutn
 */

#ifndef POINT2D_H_
#define POINT2D_H_

class Point2d {
public:
	Point2d();
	Point2d(short x, short y);
	virtual ~Point2d();

	bool operator<(const Point2d & rhs) const;
	bool operator>(const Point2d & rhs) const;
	Point2d& operator=(const Point2d & rhs);


	void setX(short x);
	short getX() const;

	void setY(short y);
	short getY() const;

private:
	short x;
	short y;
};

#endif /* POINT2D_H_ */
