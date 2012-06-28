// -*- c++ -*-
#ifndef CHESSMAN_H
#define CHESSMAN_H

#include <QGridLayout>
#include <QPoint>

#include "def.h"
#include "Chess.h"
#include "Image.h"

//forward declaration
class QGridLayout;
class QPoint;
class Chess;
class Image;

//classes for ERROR
class InvalidMoveError{};
class UnreachableError{};

//chessman class
class Chessman{
public:
	//constructor & destructor
    Chessman(const QPoint &_pos, CHESSMAN_TYPE _type, Image *_img,
             CHESSMAN_TYPE _bakType=NON, Image *_bakImg=NULL);
    ~Chessman();

	//get-functions
    QPoint getPos()const;
	CHESSMAN_TYPE getType()const;
	CHESS_ROLE getRole()const;
	Image *getImg()const;

	//check-functions
    bool checkPos(const QPoint &_pos)const;
    bool canGo(Chessman *maps[BOARD_X][BOARD_Y], const QPoint &_pos)const;

	//set-functions
    void moveTo(const QPoint &_pos);
    void toggleDeadAndAlive();

 private:
	//variables
    QPoint pos;
    Image *bakImg;
	Image *img;
    CHESSMAN_TYPE bakType;
	CHESSMAN_TYPE type;
};

//useful small functions
inline int max(int a, int b){return a>b?a:b;}
inline int min(int a, int b){return a<b?a:b;}
//why cannot i move these two inline functions into class

#endif // CHESSMAN_H
