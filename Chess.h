// -*- c++ -*-
#ifndef CHESS_H
#define CHESS_H

#include <QtGui>

#include <string>
using namespace std;

#include "def.h"
#include "LeftFrame.h"
#include "RightFrame.h"
#include "Chessman.h"
#include "Image.h"
#include "Button.h"

//forward declaration
class QApplication;
class QWidget;
class QGridLayout;
class QLabel;
class QPoint;

class LeftFrame;
class RightFrame;
class Chessman;
class Image;
class Button;

//class for ERROR
class InvalidSceneError{};

//main class of the game
class Chess:public QWidget{
	Q_OBJECT
public:
    //constructor & destructor
    Chess(QWidget *parent=0);
    ~Chess();
    //connect signals and slots
    void clickConnect(Image *img);
    void connectRevButton(Button *btn);
    void connectPlayerVsPlayerGame(Button *btn);
    void connectPlayerVsAiGame(Button *btn);
    void connectAiVsAiGame(Button *btn);
    void connectRecorder(Button *btn);
    void connectOptions(Button *btn);

private:
	STATUS_TYPE checkStatus();
    void updatePos(Chessman *c1, Chessman *c2);

    //init & finit for the game
	void init(PLAYER_ROLE _R, PLAYER_ROLE _B, const QString &_RAi=QString(), const QString &_BAi=QString());
	void finit();


    //variables for the scene
    QLabel *boardImg;
    QGridLayout *chessLayout;

    //variables for the game
	Chessman *lastChessman;
    Chessman *maps[BOARD_X][BOARD_Y];   //this is also for the scene
	STATUS_TYPE status;
    CHESS_ROLE currTurn;
    CHESS_ROLE currScene;
    PLAYER_ROLE currR;
    PLAYER_ROLE currB;

    //variables saving AI file paths
    QString RAi;
    QString BAi;

    //consts for the scene
    static const QSize CHESSMAN_SIZE;
    static const QSize BOARD_SIZE;

private slots:
    //slots
    void chessmanClicked(Chessman *chessman);
    void reverseBoard();
    void startPlayerVsPlayerGame();
    void startPlayerVsAiGame();
    void startAiVsAiGame();
    void startRecorder();
    void showOptions();
};

#endif
