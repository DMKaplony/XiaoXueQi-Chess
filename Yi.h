// -*- c++ -*-
#ifndef YI_H
#define YI_H

#include <QtGui>

#include <string>
using namespace std;

#include "def.h"
#include "Chessman.h"
#include "Image.h"
#include "Point.h"

class QWidget;
class QGridLayout;
class QVBoxLayout;
class QHBoxLayout;
class Chessman;
class Image;
class Point;

class Yi:public QWidget{
	Q_OBJECT
public:
	Yi(QWidget *parent=0);
	~Yi();
    void clickConnect(Image *img);
private slots:
	void chessmanClicked(Chessman *chessman);

private:
	Chessman *lastClicked;
	Chessman *maps[BOARD_X][BOARD_Y];
	STATUS_TYPE status;
	Image *boardImg;
	STATUS_TYPE checkStatus();
	void updateMaps(Chessman *c1, Chessman *c2);
	//init for the game
	void init();
	//finit for the game
	void finit();
	QHBoxLayout *mainLayout;
	QVBoxLayout *leftLayout;
	QVBoxLayout *rightLayout;
	QGridLayout *chessLayout;
	QGridLayout *revChessLayout;
};

#endif
