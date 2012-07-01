// -*- c++ -*-
#ifndef CHESS_H
#define CHESS_H

#include <QtGui>

#include <fstream>
#include <string>
#include <vector>
using namespace std;


#include "def.h"
#include "LeftFrame.h"
#include "RightFrame.h"
#include "Chessman.h"
#include "Image.h"
#include "Button.h"

//forward declarations
class QApplication;
class QWidget;
class QGridLayout;
class QFrame;
class QLabel;
class QPoint;
class QParallelAnimationGroup;

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
    //connecters between signals and slots
    void clickConnect(Image *img);
    void connectRevButton(Button *btn);
    void connectPlayerVsPlayerGame(Button *btn);
    void connectPlayerVsAiGame(Button *btn);
    void connectAiVsAiGame(Button *btn);
    void connectRecorder(Button *btn);
    void connectOptions(Button *btn);

    void startGame(GAME_TYPE gameType);
    void saveGame();
    void loadGame();
    void regret();
    void loadSingleAI();
    void loadDoubleAI();
    void prevStep();
    void nextStep();
    void autoStep();
    void endGame();
    void exitGame();
    void exitApp();
    void showOptions();

private:
    //variables for the scene
    QFrame *boardFrame;
    QLabel *boardImg;
    QGridLayout *chessLayout;
    LeftFrame *leftFrame;
    RightFrame *rightFrame;
    //images for indicators
    QLabel *indicators[3];

    //variable saving reverse-animation
    QParallelAnimationGroup *revAnimGroup;

    //variables for the game
	Chessman *lastChessman;
    Chessman *maps[BOARD_X][BOARD_Y];       //this is also for the scene.
    Chessman *originMaps[BOARD_X][BOARD_Y]; //to store the init state.
	STATUS_TYPE status;
    CHESS_ROLE currTurn;
    CHESS_ROLE currScene;
    PLAYER_ROLE currR;
    PLAYER_ROLE currB;

    //variables saving AI file paths
    QString RAi;
    QString BAi;

    //vector saving records
    vector<pair<QPoint, QPoint> > recorder;
    vector<bool> eater;
    //step counter
    int stepCnt;
    //no-eating counter(>60 => HE)
    int noEatingStepCnt;

    //consts for the scene
    static const QSize CHESSMAN_SIZE;
    static const QSize BOARD_SIZE;
    static const QSize WIN_SIZE;
    static const QPoint BOARD_POS;

    //init & finit for the game
    void init(PLAYER_ROLE _R, PLAYER_ROLE _B, const QString &_RAi=QString(), const QString &_BAi=QString());
    void finit();

	//other functions
    void checkStatus();
    void updatePos(Chessman *c1, Chessman *c2);

private slots:
    //slots
    void chessmanClicked(Chessman *chessman);
    void reverseBoard();
    void updateIndicators();
};

#endif // CHESS_H
