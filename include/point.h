#pragma once
#ifndef POINT_H
#define POINT_H

#include <iostream>
#include <ostream>

struct Point {
	int64_t x;
	int64_t y;

	Point(int64_t a = 0, int64_t b = 0);

	bool operator==(const Point& p);
	Point& operator=(const Point& p);
	friend std::ostream& operator<<(std::ostream& os, const Point& p);
};

#endif // !POINT_H
