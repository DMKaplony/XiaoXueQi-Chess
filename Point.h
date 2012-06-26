// -*- c++ -*-
#ifndef POINT_H
#define POINT_H

class BadXInPointError{};
class BadYInPointError{};

class Point{
 public:
	Point();
	Point(int xx, int yy);
	void setX(int xx);
	void setY(int yy);
	int getX()const;
	int getY()const;
	void setXY(int xx, int yy);
	bool operator==(const Point &_pos)const;
 private:
	int x;
	int y;
};
#endif
