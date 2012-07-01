#include "Chess.h"

//consts for the class
const QSize Chess::CHESSMAN_SIZE = QSize(55, 50);
const QSize Chess::BOARD_SIZE = QSize(600, 600);
const QSize Chess::WIN_SIZE = QSize(1100, 670);
const QPoint Chess::BOARD_POS = QPoint(150, 10);

//constructor
Chess::Chess(QWidget *parent)
    :QWidget(parent)
{
    INFO("info Chess::Chess entered.\n");

    //set title for the window
    setWindowTitle(tr(WIN_TITLE.c_str()));

    //set size for the window
    setFixedSize(WIN_SIZE);

    //set background for the app
    QPalette palette = QPalette();
    QPixmap background = QPixmap((SOURCE_PATH + BACKGROUND_IMG).c_str());
    palette.setBrush(backgroundRole(),QBrush(background));
    setPalette(palette);

    //create main parts for the app
    leftFrame = new LeftFrame(this);
    rightFrame = new RightFrame(this);
    rightFrame->connectMenuButtons();
    chessLayout = new QGridLayout();

    //set chess-board image
    QFrame *boardFrame = new QFrame(this);
    boardImg = new QLabel();
    boardImg->setPixmap(QPixmap::fromImage(
                            QImage((SOURCE_PATH + BOARD_IMG).c_str()).scaled(BOARD_SIZE)));
    chessLayout->addWidget(boardImg, 0, 0, BOARD_X+1, BOARD_Y+1);
    boardFrame->setLayout(chessLayout);
    boardFrame->move(BOARD_POS);

    //create indicators
    for (int i=0; i<3; ++i){
        indicators[i] = new QLabel(boardImg);
        indicators[i]->setPixmap(QPixmap::fromImage(
                                     QImage((SOURCE_PATH + INDICATOR_IMG).c_str()).scaled(CHESSMAN_SIZE)));
        indicators[i]->hide();
    }

    //init maps
    INFO("info Chess::Chess initing maps...\n");
    for (int i=0; i<BOARD_X; ++i){
        for (int j=0; j<BOARD_Y; ++j){
            originMaps[i][j] = maps[i][j] = NULL;
        }
    }
    INFO("info Chess::Chess maps inited.\n");

    //create chessman on maps
    INFO("info Chess::Chess creating chessman on maps...\n");
    Image *chessmanImg;
    Image *blankImg;
    int cnt = 0;
    for (int i=0; i<KIND_OF_CHESSMAN; ++i){
        for (int j=0; j<CHESS_NUM[i]; ++j){
            //create images for the chessman
            chessmanImg = new Image(
                            QString((SOURCE_PATH + CHESSMAN_IMG[i]).c_str()),
                            CHESSMAN_SIZE);

            blankImg = new Image(
                            QString((SOURCE_PATH + BLANK_IMG).c_str()),
                            CHESSMAN_SIZE);

            //create the chessman
            int x = CHESS_POS[cnt][0];
            int y = CHESS_POS[cnt][1];
            maps[x][y] = new Chessman(QPoint(x,y), CHESSMAN_TYPE(i), chessmanImg, NON, blankImg);

            //add father
            chessmanImg->addFather(maps[x][y]);
            blankImg->addFather(maps[x][y]);

            //connect click event
            clickConnect(blankImg);
            clickConnect(chessmanImg);
            ++cnt;
        }
    }
    INFO("info Chess::Chess chessman created.\n");

    //create non-chessman(i.e. the board) on maps
    INFO("info Chess::Chess creating non-chessman(i.e. the board) on maps...\n");
    for (int i=1; i<BOARD_X; ++i){
        for (int j=1; j<BOARD_Y; ++j){
            if (maps[i][j] == NULL){
                blankImg = new Image(
                                QString((SOURCE_PATH + BLANK_IMG).c_str()),
                                CHESSMAN_SIZE);
                maps[i][j] = new Chessman(QPoint(i, j), NON, blankImg);
                blankImg->addFather(maps[i][j]);
                clickConnect(blankImg);
            }
        }
    }
    INFO("info Chess::Chess non-chessman created.\n");

    //bak maps to originMaps
    memcpy(originMaps, maps, sizeof(maps));

    //add chessmans to chessLayout
    INFO("info Chess::Chess adding chessmans to chessLayout...\n");
    for (int i=1; i<BOARD_X; ++i){
        for (int j=1; j<BOARD_Y; ++j){
            chessLayout->addWidget(maps[i][j]->getImg(), i, j);
        }
    }
    INFO("info Chess::Chess all chessmans added to the chessLayout.\n");
    //hide all chessmans
    for (int i=1; i<BOARD_X; ++i){
        for (int j=1; j<BOARD_Y; ++j){
            maps[i][j]->getImg()->hide();
        }
    }

    //disable leftFrame revButton
    leftFrame->revButton->setEnabled(false);
    //init reverse animation group
    revAnimGroup = new QParallelAnimationGroup();
    //connect: re-enable revButton when animation finished
    connect(revAnimGroup, SIGNAL(finished()), leftFrame->revButton, SLOT(enable()));

    //animation test
    /*
    QPropertyAnimation *anim1=new QPropertyAnimation(boardImg, "pos");
    anim1->setDuration(2000);
    anim1->setStartValue(QPoint(0, 0));
    anim1->setEndValue(QPoint(135, 11));
    anim1->setEasingCurve(QEasingCurve::OutBounce);
    anim1->start();
    connect(anim1, SIGNAL(finished()), this, SLOT(repaint()));
    */

    lastChessman = NULL;
    status = STATUS_NON;
    currTurn = ROLE_NON;
    currScene = ROLE_NON;
    currR = NO_PLAYER;
    currB = NO_PLAYER;
    checkStatus();

    INFO("info Chess::Chess exited.\n");
}

Chess::~Chess()
{
	delete boardImg;
    delete chessLayout;
    for (int i=0; i<3; ++i){
        //delete indicators[i];
    }
    delete boardFrame;
    delete leftFrame;
    delete rightFrame;
    delete revAnimGroup;
}

//connecters
void Chess::clickConnect(Image *img)
{
    connect(img, SIGNAL(clicked(Chessman *)), this, SLOT(chessmanClicked(Chessman *)));
}

void Chess::connectRevButton(Button *btn)
{
    connect(btn, SIGNAL(clicked()), this, SLOT(reverseBoard()));
}

void Chess::connectPlayerVsPlayerGame(Button *btn)
{
    connect(btn, SIGNAL(clicked()), this, SLOT(startPlayerVsPlayerGame()));
}

void Chess::connectPlayerVsAiGame(Button *btn)
{
    connect(btn, SIGNAL(clicked()), this, SLOT(startPlayerVsAiGame()));
}

void Chess::connectAiVsAiGame(Button *btn)
{
    connect(btn, SIGNAL(clicked()), this, SLOT(startAiVsAiGame()));
}

void Chess::connectRecorder(Button *btn)
{
    connect(btn, SIGNAL(clicked()), this, SLOT(startRecorder()));
}

void Chess::connectOptions(Button *btn)
{
    connect(btn, SIGNAL(clicked()), this, SLOT(showOptions()));
}


void Chess::checkStatus()
{
    switch(status){
    case STATUS_PLAY:
        if (currTurn == ROLE_R){
            rightFrame->setStatus(tr(R_TURN_STR.c_str()));
        }else if (currTurn == ROLE_B){
            rightFrame->setStatus(tr(B_TURN_STR.c_str()));
        }else{
            rightFrame->setStatus(tr(NO_PLAYER_STR.c_str()));
        }
        break;
    case STATUS_R_WIN:
        rightFrame->setStatus(tr(R_WIN_STR.c_str()));
        rightFrame->setSlaveMenuEndState();
        QMessageBox::information(NULL, tr("WIN!"), tr(R_WIN_STR.c_str()));
        break;
    case STATUS_B_WIN:
        rightFrame->setStatus(tr(B_WIN_STR.c_str()));
        rightFrame->setSlaveMenuEndState();
        QMessageBox::information(NULL, tr("WIN!"), tr(B_WIN_STR.c_str()));
        break;
    case STATUS_TIE:
        rightFrame->setStatus(tr(TIE_STR.c_str()));
        rightFrame->setSlaveMenuEndState();
        QMessageBox::information(NULL, tr("TIE!"), tr(TIE_STR.c_str()));
        break;
    case STATUS_END:
        rightFrame->setStatus(tr(GAME_ENDED_STR.c_str()));
        rightFrame->setSlaveMenuEndState();
        break;
    default:
        rightFrame->setStatus(tr(NO_GAME_STR.c_str()));
        break;
    }
}

void Chess::updatePos(Chessman *c1, Chessman *c2)
{
    QPoint tmp1 = c1->getPos();
    int x1 = tmp1.x();
    int y1 = tmp1.y();
    QPoint tmp2 = c2->getPos();
    int x2 = tmp2.x();
    int y2 = tmp2.y();

    /* not need to remove
    chessLayout->removeWidget(c2->getImg());
    chessLayout->removeWidget(c1->getImg());
    */
    maps[x1][y1] = c2;
    maps[x2][y2] = c1;
    if (currScene == ROLE_B){
        x1 = BOARD_X - x1;
        x2 = BOARD_X - x2;
        y1 = BOARD_Y - y1;
        y2 = BOARD_Y - y2;
    }
    chessLayout->addWidget(c2->getImg(), x1, y1);
    chessLayout->addWidget(c1->getImg(), x2, y2);

    QPoint tmpPos = c1->getPos();
    c1->moveTo(c2->getPos());
    c2->moveTo(tmpPos);

    printf("Chess::Position Updated");
}

void Chess::init(PLAYER_ROLE _R, PLAYER_ROLE _B, const QString &_RAi, const QString &_BAi)
{
    INFO("info Chess::init entered.\n");
    //stop flicker
    if (lastChessman != NULL){
        lastChessman->getImg()->stopFlicker();
    }

	//init player info
    currTurn = ROLE_R;
    currScene = ROLE_R;
	currR = _R;
	currB = _B;
	RAi = _RAi;
	BAi = _BAi;

	//compile AI if needed
	if (currR == ROLE_AI){
		system(("g++ -shared -fPIC -o " + RAI_NAME + " " + RAi.toStdString()).c_str());
	}
	if (currB == ROLE_AI){
		system(("g++ -shared -fPIC -o " + BAI_NAME + " " + BAi.toStdString()).c_str());
	}

    //init recorder & stepCnt
    recorder.clear();
    eater.clear();
    stepCnt = 0;
    noEatingStepCnt = 0;

    //hide indicators
    for (int i=0; i<3; ++i){
        indicators[i]->hide();
    }

    //restore to originMaps
    memcpy(maps, originMaps, sizeof(originMaps));

    //reset pos
    for (int i=1; i<BOARD_X; ++i){
        for (int j=1; j<BOARD_Y; ++j){
            maps[i][j]->revive();
            maps[i][j]->moveTo(QPoint(i, j));
            maps[i][j]->getImg()->show();
            chessLayout->addWidget(maps[i][j]->getImg(), i, j);
        }
    }

	//game start
	lastChessman = NULL;
	status = STATUS_PLAY;
    checkStatus();

    //enable revButton
    leftFrame->revButton->setEnabled(true);

    INFO("info Chess::init exited.\n");
}

void Chess::finit()
{
    for (int i=0; i<3; ++i){
        indicators[i]->hide();
    }
    for (int i=1; i<BOARD_X; ++i){
        for (int j=1; j<BOARD_Y; ++j){
            maps[i][j]->getImg()->hide();
        }
    }
}




void Chess::startGame(GAME_TYPE gameType)
{
    switch (gameType){
    case GAME_PVP:
        init(ROLE_PLAYER, ROLE_PLAYER);
        break;
    case GAME_PVA:
        break;
    case GAME_AVA:
        init(ROLE_AI, ROLE_AI, RAi, BAi);
        break;
    case GAME_REC:
        break;
    }
}

void Chess::saveGame()
{
    QString savePath = QFileDialog::getSaveFileName(this, tr("Save Chess Game"), ".", tr("Chess Save Files(*.csf)"));
    if(savePath.length() == 0) {
        QMessageBox::information(NULL, tr("Path"), tr("You didn't select any files."));
    }else{
        ofstream ofs;
        ofs.open(savePath.toStdString(), ios::out);
        for (int i=0; i<stepCnt; ++i){
            pair<QPoint, QPoint> tmp = recorder[i];
            ofs << stepCnt << ": ";
            QPoint pnt = tmp.first();
            ofs << pnt.x() << " " << pnt.y() << " ";
            pnt = tmp.second();
            ofs << pnt.x() << " " << pnt.y() << " ";
            ofs << (eater[i] ? 1 : 0) << endl;
        }
        ofs.close();
    }
}

void Chess::loadGame()
{

}



void Chess::regret()
{
    if (stepCnt < 2){
        //QMessageBox::about(0, tr("ERROR"), tr("cannot regret!"));
        QMessageBox::information(NULL, tr("Error"), tr("You cannot regret anymore!"));

    }else{
        for (int i=0; i<2; ++i){
            --stepCnt;
            pair<QPoint, QPoint> tmpPair = recorder[stepCnt];
            QPoint tmpPoint = tmpPair.first;
            Chessman *from = maps[tmpPoint.x()][tmpPoint.y()];
            tmpPoint = tmpPair.second;
            Chessman *to = maps[tmpPoint.x()][tmpPoint.y()];
            if (eater[stepCnt]){
                from->revive();
            }
            recorder.pop_back();
            eater.pop_back();
            updatePos(to, from);
        }
        //unset flicker
        if (lastChessman != NULL){
            lastChessman->getImg()->stopFlicker();
            lastChessman = NULL;
        }
        //reset indicator
        for (int i=0; i<3; ++i){
            indicators[i]->hide();
        }
        updateIndicators();
        indicators[1]->show();
        indicators[2]->show();
        /*
        if (stepCnt > 0){
            pair<QPoint, QPoint> tmpPair = recorder[stepCnt-1];
            QPoint tmpPoint = tmpPair.first;
            Chessman *from = maps[tmpPoint.x()][tmpPoint.y()];
            tmpPoint = tmpPair.second;
            Chessman *to = maps[tmpPoint.x()][tmpPoint.y()];
            //reset indicators
            if (currScene == ROLE_B){
                int x = BOARD_X - from->getPos().x();
                int y = BOARD_Y - from->getPos().y();
                indicators[1]->move(maps[x][y]->getImg()->pos() - boardImg->pos());
                indicators[1]->show();
                x = BOARD_X - to->getPos().x();
                y = BOARD_Y - to->getPos().y();
                indicators[2]->move(maps[x][y]->getImg()->pos() - boardImg->pos());
                indicators[2]->show();
            }else if (currScene == ROLE_R){
                indicators[1]->move(from->getImg()->pos() - boardImg->pos());
                indicators[1]->show();
                indicators[2]->move(to->getImg()->pos() - boardImg->pos());
                indicators[2]->show();
            }else{
                throw InvalidSceneError();
            }
        }*/
    }
}

void Chess::loadSingleAI()
{

}

void Chess::loadDoubleAI()
{
    QString aiPathR = QFileDialog::getOpenFileName(this, tr("Open Chess AI File"), ".", tr("Chess AI Files(*.cai)"));
    if(aiPathR.length() == 0) {
        QMessageBox::information(NULL, tr("Path"), tr("You didn't select any files."));
    }else{
        QMessageBox::information(NULL, tr("Path"), tr("You selected ") + aiPathR);
    }

    QString aiPathB = QFileDialog::getOpenFileName(this, tr("Open Chess AI File"), ".", tr("Chess AI Files(*.cai)"));
    if(aiPathB.length() == 0) {
        QMessageBox::information(NULL, tr("Path"), tr("You didn't select any files."));
    }else{
        QMessageBox::information(NULL, tr("Path"), tr("You selected ") + aiPathB);
    }

    init(ROLE_AI, ROLE_AI, aiPathR, aiPathB);
}

void Chess::prevStep()
{

}

void Chess::nextStep()
{

}

void Chess::autoStep()
{

}

void Chess::endGame()
{
    if (status == STATUS_PLAY){
        status = STATUS_END;
        checkStatus();
    }
}

//exit the game
void Chess::exitGame()
{
    finit();
}
//exit the app
void Chess::exitApp()
{
    this->close();
}

void Chess::showOptions()
{

}


void Chess::chessmanClicked(Chessman *chessman)
{
    INFO("info Chess::chessmanClicked entered.\n");

    //game over or not begin
    if (status != STATUS_PLAY){
        return;
    }

    //no chessman selected
    if (lastChessman == NULL || lastChessman->getType() == NON){
        if (currTurn == chessman->getRole()){
            lastChessman = chessman;
            //set flicker
            lastChessman->getImg()->startFlicker();
            updateIndicators();
            indicators[0]->show();
            /*
            //set indicator
            if (currScene == ROLE_B){
                int x = BOARD_X - lastChessman->getPos().x();
                int y = BOARD_Y - lastChessman->getPos().y();
                indicators[0]->move(maps[x][y]->getImg()->pos() - boardImg->pos());
                indicators[0]->show();
            }else if (currScene == ROLE_R){
                indicators[0]->move(lastChessman->getImg()->pos() - boardImg->pos());
                indicators[0]->show();
            }else{
                throw InvalidSceneError();
            }
            */

        }
        return;
    }

    //some chessman selected
    if (currTurn != chessman->getRole() && lastChessman->canGo(maps, chessman->getPos())){
        printf("debug can go\n");
        //can go
        ++stepCnt;
        recorder.push_back(pair<QPoint, QPoint>(lastChessman->getPos(), chessman->getPos()));

        if (chessman->getType() != NON){
            eater.push_back(true);
            noEatingStepCnt = 0;
        }else{
            eater.push_back(false);
            if (++noEatingStepCnt == TIE_STEP){
                status = STATUS_TIE;
            }
        }
        if (chessman->getType() != NON){
            //die
            if (chessman->getType() == R_JIANG){
                status = STATUS_B_WIN;
            }else if (chessman->getType() == B_JIANG){
                status = STATUS_R_WIN;
            }
            //set die
            chessman->die();
        }

        //update position
        updatePos(chessman, lastChessman);

        /*
        //reset indicators
        if (currScene == ROLE_B){
            int x = BOARD_X - chessman->getPos().x();
            int y = BOARD_Y - chessman->getPos().y();
            indicators[1]->move(maps[x][y]->getImg()->pos() - boardImg->pos());
            indicators[1]->show();
            x = BOARD_X - lastChessman->getPos().x();
            y = BOARD_Y - lastChessman->getPos().y();
            indicators[2]->move(maps[x][y]->getImg()->pos() - boardImg->pos());
            indicators[2]->show();
        }else if (currScene == ROLE_R){
            indicators[1]->move(chessman->getImg()->pos() - boardImg->pos());
            indicators[1]->show();
            indicators[2]->move(lastChessman->getImg()->pos() - boardImg->pos());
            indicators[2]->show();
        }else{
            throw InvalidSceneError();
        }
        */
        updateIndicators();
        indicators[1]->show();
        indicators[2]->show();
        indicators[0]->hide();

        //unset flicker
        lastChessman->getImg()->stopFlicker();
        lastChessman = NULL;
        //toggle turn
        currTurn = (currTurn==ROLE_R)?ROLE_B:ROLE_R;
        checkStatus();
    }else{
        //cannot go
        printf("debug cannot go\n");
        lastChessman->getImg()->stopFlicker();
        lastChessman = chessman;
        lastChessman->getImg()->startFlicker();


        if (chessman->getType() != NON){
            updateIndicators();
            indicators[0]->show();
        }
    }

    INFO("info Chess::chessmanClicked exited\n");
}

void Chess::reverseBoard()
{
    INFO("info Chess::reverseBoard entered.\n");

    //disable revButton
    leftFrame->revButton->setEnabled(false);

    //animation
    QPropertyAnimation *anim;
    revAnimGroup->clear();

    for (int i=1; i<(BOARD_X+1)/2; ++i){
        for(int j=1; j<BOARD_Y; ++j){
            QPoint pos1 = maps[i][j]->getImg()->geometry().topLeft();
            QPoint pos2 = maps[BOARD_X-i][BOARD_Y-j]->getImg()->geometry().topLeft();

            anim = new QPropertyAnimation(maps[i][j]->getImg(), "pos");
            anim->setDuration(REV_ANIM_TIME);
            anim->setStartValue(pos1);
            anim->setEndValue(pos2);
            anim->setEasingCurve(QEasingCurve::InOutElastic);
            revAnimGroup->addAnimation(anim);

            anim = new QPropertyAnimation(maps[BOARD_X-i][BOARD_Y-j]->getImg(), "pos");
            anim->setDuration(REV_ANIM_TIME);
            anim->setStartValue(pos2);
            anim->setEndValue(pos1);
            anim->setEasingCurve(QEasingCurve::InOutElastic);
            revAnimGroup->addAnimation(anim);
        }
    }
    revAnimGroup->start();
    //update indicators when animation finished
    connect(revAnimGroup, SIGNAL(finished()), this, SLOT(updateIndicators()));

    //toggle Scene
    currScene = (currScene==ROLE_R)?ROLE_B:ROLE_R;

    //remove & re-add chessmans to chessLayout
    /* not need to remove
    for (int i=1; i<BOARD_X; ++i){
        for (int j=1; j<BOARD_Y; ++j){
            chessLayout->removeWidget(maps[i][j]->getImg());
        }
    }*/
    for (int i=1; i<BOARD_X; ++i){
        for (int j=1; j<BOARD_Y; ++j){
            if (currScene == ROLE_B){
                chessLayout->addWidget(maps[i][j]->getImg(), BOARD_X-i, BOARD_Y-j);
                maps[i][j]->getImg()->update();
            }else if (currScene == ROLE_R){
                chessLayout->addWidget(maps[i][j]->getImg(), i, j);
                maps[i][j]->getImg()->update();
            }else{
                throw InvalidSceneError();
            }
        }
    }

    INFO("info Chess::reverseBoard exited.\n");
}


void Chess::updateIndicators()
{
    //update indicator[0]
    if (lastChessman != NULL && lastChessman->getType() != NON){
        indicators[0]->move(lastChessman->getImg()->pos() - boardImg->pos());
        printf("%d\n", indicators[0]->pos().x());
    }
    //update indicator[1]&incidcator[2]
    if (stepCnt > 0){
        pair<QPoint, QPoint> tmpPair = recorder[stepCnt-1];
        QPoint tmpPoint = tmpPair.first;
        Chessman *from = maps[tmpPoint.x()][tmpPoint.y()];
        tmpPoint = tmpPair.second;
        Chessman *to = maps[tmpPoint.x()][tmpPoint.y()];
        indicators[1]->move(from->getImg()->pos() - boardImg->pos());
        indicators[2]->move(to->getImg()->pos() - boardImg->pos());
    }
}
