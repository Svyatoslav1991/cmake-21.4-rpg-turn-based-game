#include "point.h"

Point::Point(int64_t a, int64_t b) : x (a), y (b)
{

}

/////////////////////////////////////////////////

bool Point::operator==(const Point& p)
{
	return (x == p.x && y == p.y);
}

/////////////////////////////////////////////////

Point& Point::operator=(const Point& p)
{
	x = p.x;
	y = p.y;

	return *this;
}

std::ostream& operator<<(std::ostream& os, const Point& p)
{
	os << "x = " << p.x << "; y = " << p.y;
	return os;
}
