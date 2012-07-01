// -*- C++ -*-
#ifndef LeftFrame_H
#define LeftFrame_H

#include <QObject>
#include <QLabel>

#include "def.h"
#include "Chess.h"
#include "Image.h"
#include "Button.h"

//forward declarations
class Chess;
class Image;

//LeftFrame class
class LeftFrame:public QObject{
    Q_OBJECT
public:
	//constructors & destructors
    LeftFrame(Chess *chess);
    ~LeftFrame();
    //friend class
    friend class Chess;

private:
	//widgets in frame
    Image *headerB;
    Image *headerR;
    QLabel *infoB;
    QLabel *infoR;
    Button *revButton;
    //consts
    static const QPoint HEADER_B_POS;
    static const QPoint HEADER_R_POS;
    static const QPoint INFO_B_POS;
    static const QPoint INFO_R_POS;
    static const QPoint REV_BUTTON_POS;
    static const QSize HEADER_SIZE;
};


#endif // LeftFrame_H
