// -*- c++ -*-
#ifndef CHESSMAN_H
#define CHESSMAN_H

#include <QGridLayout>

#include "def.h"
#include "Yi.h"
#include "Image.h"
#include "Point.h"

class QGridLayout;
class Yi;
class Image;
class Point;

class InvalidMoveError{};
class UnreachableError{};

class Chessman{
 public:
    Chessman(Point _pos, CHESS_TYPE _type, Image *_img);
    ~Chessman();

	Point getPos()const;
	CHESS_TYPE getType()const;
	Image *getImg()const;

	bool checkPos(const Point &_pos)const;
	bool canGo(Chessman *maps[BOARD_X][BOARD_Y], const Point &_pos)const;

	void moveTo(Chessman *maps[BOARD_X][BOARD_Y], const Point &_pos);
    void die(Yi *yi, QGridLayout *chessLayout);
    void revive();

 private:
	Point pos;
	Image *img;
	CHESS_TYPE type;
};

inline int max(int a, int b){return a>b?a:b;}
inline int min(int a, int b){return a<b?a:b;}

#endif
