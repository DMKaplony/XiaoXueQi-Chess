// -*- C++ -*-
#ifndef LeftFrame_H
#define LeftFrame_H

#include <QObject>
#include <QLabel>

#include "def.h"
#include "Chess.h"
#include "Image.h"
#include "Button.h"

class QObject;
class QLabel;
class Chess;
class Image;
class Button;

class LeftFrame:public QObject{
    Q_OBJECT
public:
    LeftFrame(Chess *chess);
    ~LeftFrame();
private:
    Image *headerB;
    Image *headerR;
    QLabel *infoB;
    QLabel *infoR;
    Button *revButton;
};


#endif // LeftFrame_H
