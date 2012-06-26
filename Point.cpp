#include "Point.h"

Point::Point()
{
	x = y = 1;
}

Point::Point(int xx, int yy)
{
	setXY(xx, yy);
}

void Point::setX(int xx)
{
	if (xx < 1 || xx > 10){
		throw BadXInPointError();
	}
	x = xx;
}

void Point::setY(int yy)
{
	if (yy < 1 || yy > 9){
		throw BadYInPointError();
	}
	y = yy;
}

int Point::getX()const
{
	return x;
}

int Point::getY()const
{
	return y;
}

void Point::setXY(int xx, int yy)
{
	setX(xx);
	setY(yy);
}
bool Point::operator==(const Point &_pos)const
{
	return (x==_pos.getX() && y==_pos.getY());
}
