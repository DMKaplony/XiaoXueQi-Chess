#include "Chess.h"

//consts for the class
const QSize Chess::CHESSMAN_SIZE = QSize(55, 50);
const QSize Chess::BOARD_SIZE = QSize(600, 600);

//constructor
Chess::Chess(QWidget *parent)
	:QWidget(parent)
{
    INFO("info Chess::Chess entered.\n");

    //set title for the window
    setWindowTitle(tr(WIN_TITLE));

    //set size for the window
    setFixedSize(WIN_SIZE);

    //set background for the app
    QPalette palette();
    QPixmap background = QPixmap((SOURCE_PATH + BACKGROUND_IMG).c_str());
    palette.setBrush(backgroundRole(),QBrush(background));
    setPalette(palette);

    //create main parts for the app
    leftFrame = new LeftFrame(this);
    rightFrame = new RightFrame(this);
    chessLayout = new QGridLayout();

    //chessLayout->addWidget(boardImg, 0, 0, BOARD_X+1, BOARD_Y+1);

    //set chess-board image
    boardImg = new QLabel(this);
    QImage img((SOURCE_PATH + BOARD_IMG).c_str());
    boardImg->setPixmap(QPixmap::fromImage(img.scaled(BOARD_SIZE, QT::IgnoreAspectRatio)));
    boardImg->setLayout(chessLayout);
    boardImg->move(BOARD_POS);

    rightFrame->showButtons();

    /*
    QPropertyAnimation *anim1=new QPropertyAnimation(boardImg, "pos");
    anim1->setDuration(2000);
    anim1->setStartValue(QPoint(0, 0));
    anim1->setEndValue(QPoint(135, 11));
    anim1->setEasingCurve(QEasingCurve::OutBounce);
    anim1->start();
    connect(anim1, SIGNAL(finished()), this, SLOT(repaint()));
    */
    INFO("info Chess::Chess exited.\n");
}

Chess::~Chess()
{
	//need to be modified
	delete boardImg;
	delete mainLayout;
    delete leftFrame;
    delete rightFrame;
}

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



STATUS_TYPE Chess::checkStatus()
{
	//need to be modified

	//tie here to be added
	return STATUS_PLAY;
}

void Chess::updatePos(Chessman *c1, Chessman *c2)
{
    QPoint tmp1 = c1->getPos();
    int x1 = tmp1.x();
    int y1 = tmp1.y();
    QPoint tmp2 = c2->getPos();
    int x2 = tmp2.x();
    int y2 = tmp2.y();

    chessLayout->removeWidget(c1->getImg());
    chessLayout->removeWidget(c2->getImg());
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
    c1->moveTo(maps, c2->getPos());
    c2->moveTo(maps, tmpPos);

    printf("Chess::mapsupdated");
}

void Chess::init(PLAYER_ROLE _R, PLAYER_ROLE _B, const QString &_RAi, const QString &_BAi)
{
    INFO("info Chess::init entered.\n");

	//init player info
    INFO("info Chess::init initing player info...\n");
    currTurn = ROLE_R;
    currScene = ROLE_R;
	currR = _R;
	currB = _B;
	RAi = _RAi;
	BAi = _BAi;
    INFO("info Chess::init player info inited.\n");

	//compile AI if needed
    INFO("info Chess::init compiling AI files needed...\n");
	if (currR == ROLE_AI){
		system(("g++ -shared -fPIC -o " + RAI_NAME + " " + RAi.toStdString()).c_str());
	}
	if (currB == ROLE_AI){
		system(("g++ -shared -fPIC -o " + BAI_NAME + " " + BAi.toStdString()).c_str());
	}
    INFO("info Chess::init AI files compiled.\n");

	//init maps
    printf("info Chess::init initing maps...\n");
	for (int i=0; i<BOARD_X; ++i){
		for (int j=0; j<BOARD_Y; ++j){
			maps[i][j] = NULL;
		}
	}
    INFO("info Chess::init maps inited.\n");

	//create chessman on maps
    INFO("info Chess::init creating chessman on maps...\n");
	Image *chessmanImg;
	int cnt = 0;
	for (int i=0; i<KIND_OF_CHESSMAN; ++i){
		for (int j=0; j<CHESS_NUM[i]; ++j){
			chessmanImg = new Image(
							QString((SOURCE_PATH + CHESS_NAME[i] + IMG_TYPE).c_str()),
                            CHESSMAN_SIZE);
			int x = CHESS_POS[cnt][0];
			int y = CHESS_POS[cnt][1];
            maps[x][y] = new Chessman(QPoint(x,y), CHESS_TYPE(i), chessmanImg);
			chessmanImg->addFather(maps[x][y]);
			clickConnect(chessmanImg);
			++cnt;
		}
	}
    INFO("info Chess::init chessman created.\n");

	//create non-chessman(i.e. the board) on maps
    INFO("info Chess::init creating non-chessman(i.e. the board) on maps...\n");
	for (int i=1; i<BOARD_X; ++i){
		for (int j=1; j<BOARD_Y; ++j){
			if (maps[i][j] == NULL){
				chessmanImg = new Image(
									QString((SOURCE_PATH + BLANK + IMG_TYPE).c_str()),
                                    CHESSMAN_SIZE);
                maps[i][j] = new Chessman(QPoint(i, j), NON, chessmanImg);
				chessmanImg->addFather(maps[i][j]);
				clickConnect(chessmanImg);
			}
		}
	}
    INFO("info Chess::init non-chessman created.\n");

    //add chessmans to chessLayout
    INFO("info Chess::init adding chessmans to chessLayout...\n");
	for (int i=1; i<BOARD_X; ++i){
		for (int j=1; j<BOARD_Y; ++j){
            chessLayout->addWidget(maps[i][j]->getImg(), i, j);
		}
	}
    INFO("info Chess::init all chessmans added to the chessLayout.\n");

	//game start
    INFO("info Chess::init game starting...\n");
	lastChessman = NULL;
	status = STATUS_PLAY;
    INFO("info Chess::init game started.\n");

    INFO("info Chess::init exited.\n");
}

void Chess::finit()
{
    INFO("info Chess::finit enterd.\n");
	//delete maps
	for (int i=0; i<BOARD_X; ++i){
		for (int j=0; j<BOARD_Y; ++j){
			if (maps[i][j] != NULL){
				delete maps[i][j];
			}
		}
	}

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
        }
        return;
    }

    //some chessman selected
    if (currTurn != chessman->getRole() && lastChessman->canGo(maps, chessman->getPos())){
        printf("debug can go\n");
        //can go
        if (chessman->getType() != NON){
            //die
            if (chessman->getType() == R_JIANG){
                status = STATUS_B_WIN;
            }else if (chessman->getType() == B_JIANG){
                status = STATUS_R_WIN;
            }
            rightFrame->updateStatusLabel(status);
            chessman->die(this, chessLayout);
        }


        updatePos(chessman, lastChessman);

        lastChessman = NULL;
        //toggle turn
        currTurn = (currTurn==ROLE_R)?ROLE_B:ROLE_R;
    }else{
        //cannot go
        printf("debug cannot go\n");
        lastChessman = chessman;
    }
    printf("info Chess::chessmanClicked exited\n");
}

void Chess::reverseBoard()
{
    INFO("info Chess::reverseBoard entered.\n");

    //animation
    QPropertyAnimation *anim;
    QParallelAnimationGroup *group = new QParallelAnimationGroup();

    for (int i=1; i<(BOARD_X+1)/2; ++i){
        for(int j=1; j<BOARD_Y; ++j){
            //if (maps[i][j]->getType() != NON || maps[BOARD_X-i][BOARD_Y-j]->getType() != NON){
            {
                INFO("info : %d %d\n", i, j);
                QPoint pos1 = maps[i][j]->getImg()->geometry().topLeft();
                QPoint pos2 = maps[BOARD_X-i][BOARD_Y-j]->getImg()->geometry().topLeft();
                anim = new QPropertyAnimation(maps[i][j]->getImg(), "pos");
                anim->setDuration(REV_ANIM_TIME);
                anim->setStartValue(pos1);
                anim->setEndValue(pos2);
                anim->setEasingCurve(QEasingCurve::InOutElastic);
                group->addAnimation(anim);

                anim = new QPropertyAnimation(maps[BOARD_X-i][BOARD_Y-j]->getImg(), "pos");
                anim->setDuration(REV_ANIM_TIME);
                anim->setStartValue(pos2);
                anim->setEndValue(pos1);
                anim->setEasingCurve(QEasingCurve::InOutElastic);
                group->addAnimation(anim);
            }
        }
    }
    group->start();

    //toggle Scene
    currScene = (currScene==ROLE_R)?ROLE_B:ROLE_R;

    //re-add chessmans to chessLayout
    INFO("info Chess::reverseBoard readding chessmans to chessLayout...\n");

    for (int i=1; i<BOARD_X; ++i){
        for (int j=1; j<BOARD_Y; ++j){
            chessLayout->removeWidget(maps[i][j]->getImg());
        }
    }
    for (int i=1; i<BOARD_X; ++i){
        for (int j=1; j<BOARD_Y; ++j){
            if (currScene == ROLE_B){
                chessLayout->addWidget(maps[i][j]->getImg(), BOARD_X-i, BOARD_Y-j);
            }else if (currScene == ROLE_R){
                chessLayout->addWidget(maps[i][j]->getImg(), i, j);
            }else{
                throw InvalidSceneError();
            }
        }
    }

    INFO("info Chess::reverseBoard all chessmans re-added to the chessLayout.\n");

    INFO("info Chess::reverseBoard exited.\n");
}




void Chess::startPlayerVsPlayerGame()
{
    init(ROLE_PLAYER, ROLE_PLAYER);
}

void Chess::startPlayerVsAiGame()
{


}

void Chess::startAiVsAiGame()
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

void Chess::startRecorder()
{

}

void Chess::showOptions()
{

}
