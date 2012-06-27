// -*- c++ -*-
#ifndef CHESSMAN_H
#define CHESSMAN_H

#include <QGridLayout>
#include <QPoint>

#include "def.h"
#include "Chess.h"
#include "Image.h"


class QGridLayout;
class QPoint;
class Chess;
class Image;


class InvalidMoveError{};
class UnreachableError{};

class Chessman{
 public:
    Chessman(const QPoint &_pos, CHESS_TYPE _type, Image *_img);
    ~Chessman();

    QPoint getPos()const;
	CHESS_TYPE getType()const;
	CHESS_ROLE getRole()const;
	Image *getImg()const;

    bool checkPos(const QPoint &_pos)const;
    bool canGo(Chessman *maps[BOARD_X][BOARD_Y], const QPoint &_pos)const;

    void moveTo(Chessman *maps[BOARD_X][BOARD_Y], const QPoint &_pos);
    void die(Chess *chess, QGridLayout *chessLayout);
    void revive();

 private:
    QPoint pos;
	Image *img;
	CHESS_TYPE type;
};

inline int max(int a, int b){return a>b?a:b;}
inline int min(int a, int b){return a<b?a:b;}

#endif
