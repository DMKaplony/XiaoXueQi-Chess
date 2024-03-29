#include "Yi.h"

Yi::Yi(QWidget *parent)
	:QWidget(parent), lastClicked(NULL)
{
	INFO("info Yi::Yi entered.\n");
	//create board image for backgroud
   	boardImg = new Image(
			          QString((SOURCE_PATH + BOARD_NAME + ".png").c_str()),
					  QSize(400, 400));

    //set title for the window
    setWindowTitle(tr("CHESS"));

    //create all layouts for the app
	mainLayout = new QHBoxLayout;
	leftLayout = new QVBoxLayout;
	rightLayout = new QVBoxLayout;
	chessLayout = new QGridLayout;
	revChessLayout = new QGridLayout;

    //add layouts to the mainLayout
    mainLayout->addLayout(leftLayout);
    mainLayout->addLayout(chessLayout);
    mainLayout->addLayout(rightLayout);
    mainLayout->setSizeConstraint(QLayout::SetFixedSize);

    //set mainLayout to the window
  	setLayout(mainLayout);

    //add widgets to leftLayout
    leftLayout->addWidget(new Image(QString((SOURCE_PATH + "head1.png").c_str()), QSize(50, 50)));
    leftLayout->addWidget(new QLabel());
    leftLayout->addWidget(new QPushButton(QIcon((SOURCE_PATH + "exchange.png").c_str()), tr("exchange")));
    leftLayout->addWidget(new Image(QString((SOURCE_PATH + "head2.png").c_str()), QSize(50, 50)));
    leftLayout->addWidget(new QLabel());

    //add backgroud to chessLayout & revChessLayout
    chessLayout->addWidget(boardImg, 0, 0, 30, 30);

    revChessLayout->addWidget(boardImg, 0, 0, 30, 30);

    //add widgets to rightLayout
    rightLayout->addWidget(new QTextEdit());
    rightLayout->addWidget(new QPushButton(QIcon((SOURCE_PATH + "pvsp.png").c_str()), tr("player vs player")));
    rightLayout->addWidget(new QPushButton(QIcon((SOURCE_PATH + "pvscom.png").c_str()), tr("player vs com")));
    rightLayout->addWidget(new QPushButton(QIcon((SOURCE_PATH + "comvscom.png").c_str()), tr("com vs com")));
    rightLayout->addWidget(new QPushButton(QIcon((SOURCE_PATH + "recoder.png").c_str()), tr("recode")));
	init();

    QPropertyAnimation *anim1=new QPropertyAnimation(revChessLayout, "pos");
        anim1->setDuration(2000);
        anim1->setStartValue(QPoint(0, 360));
        anim1->setEndValue(QPoint(110, 180));
        anim1->setEasingCurve(QEasingCurve::OutBounce);
        anim1->start();

	INFO("info Yi::Yi exited.\n");
}

Yi::~Yi()
{
	delete boardImg;
	delete mainLayout;
}
/*
Button *Yi::createButton(const QString &text, const char *member)
{
	Button *button = new Button(text);
	connect(button, SIGNAL(clicked()), this, member);
	return button;
}

Button *Yi::createButton(const QIcon &icon, const char *member)
{
	Button *button = new Button(QString(""));
	button->setIcon(icon);
	//connect(button, SINGAL(clicked()), this, member);
	return button;
}
*/
STATUS_TYPE Yi::checkStatus()
{
	//need to be modified

	//tie here to be added
	return PLAY;
}

void Yi::chessmanClicked(Chessman *chessman)
{
	INFO("info Yi::chessmanClicked entered.\n");

    //no chessman selected
	if (lastClicked == NULL || lastClicked->getType() == NON){
		lastClicked = chessman;
		return;
	}
    //some chessman selected
	if (lastClicked->canGo(maps, chessman->getPos())){
		printf("debug can go\n");
		//can go
		if (chessman->getType() != NON){
			//die
            chessman->die(this, chessLayout);
		}

		Point tmpPos = lastClicked->getPos();
		printf("%d\n", lastClicked->canGo(maps, chessman->getPos()));
		lastClicked->moveTo(maps, chessman->getPos());
		chessman->moveTo(maps, tmpPos);

		updateMaps(chessman, lastClicked);

		checkStatus();
		lastClicked = NULL;
	}else{
		//cannot go
		printf("debug cannot go\n");
		lastClicked = chessman;
	}
	printf("info Yi::chessmanClicked exited\n");
}

void Yi::updateMaps(Chessman *c1, Chessman *c2)
{
	Point tmp1 = c1->getPos();
	int x1 = tmp1.getX();
	int y1 = tmp1.getY();
	Point tmp2 = c2->getPos();
	int x2 = tmp2.getX();
	int y2 = tmp2.getY();
    chessLayout->removeWidget(maps[x1][y1]->getImg());
    chessLayout->removeWidget(maps[x2][y2]->getImg());
	maps[x1][y1] = c1;
	maps[x2][y2] = c2;
    chessLayout->addWidget(maps[x1][y1]->getImg(), x1, y1);
    chessLayout->addWidget(maps[x2][y2]->getImg(), x2, y2);

	printf("Yi::mapsupdated");
}

void Yi::clickConnect(Image *img)
{
    connect(img, SIGNAL(clicked(Chessman *)), this, SLOT(chessmanClicked(Chessman *)));
}

void Yi::init()
{
	INFO("info Yi::init entered.\n");
	//init maps
	printf("info Yi::init initing maps...\n");
	for (int i=0; i<BOARD_X; ++i){
		for (int j=0; j<BOARD_Y; ++j){
			maps[i][j] = NULL;
		}
	}
	INFO("info Yi::init maps inited.\n");

	//create chessman on maps
	INFO("info Yi::init creating chessman on maps...\n");
	Image *chessmanImg;
	int cnt = 0;
	for (int i=0; i<KIND_OF_CHESSMAN; ++i){
		for (int j=0; j<CHESS_NUM[i]; ++j){
			chessmanImg = new Image(
							QString((SOURCE_PATH + CHESS_NAME[i] + IMG_TYPE).c_str()),
							QSize(30, 30));
			int x = CHESS_POS[cnt][0];
			int y = CHESS_POS[cnt][1];
			maps[x][y] = new Chessman(Point(x,y), CHESS_TYPE(i), chessmanImg);
			chessmanImg->addFather(maps[x][y]);
			clickConnect(chessmanImg);
			++cnt;
		}
	}
	INFO("info Yi::init chessman created.\n");

	//create non-chessman(i.e. the board) on maps
	INFO("info Yi::init creating non-chessman(i.e. the board) on maps...\n");
	for (int i=1; i<BOARD_X; ++i){
		for (int j=1; j<BOARD_Y; ++j){
			if (maps[i][j] == NULL){
				chessmanImg = new Image(
									QString((SOURCE_PATH + BLANK + IMG_TYPE).c_str()),
									QSize(30,30));
				maps[i][j] = new Chessman(Point(i, j), NON, chessmanImg);
				chessmanImg->addFather(maps[i][j]);
				clickConnect(chessmanImg);
			}
		}
	}
	INFO("info Yi::init non-chessman created.\n");

    //add chessmans to chessLayout & revChessLayout
    INFO("info Yi::init adding chessmans to chessLayout & revChessLayout...\n");
	for (int i=1; i<BOARD_X; ++i){
		for (int j=1; j<BOARD_Y; ++j){
            chessLayout->addWidget(maps[i][j]->getImg(), i, j);
            revChessLayout->addWidget(maps[i][j]->getImg(), BOARD_X-i, BOARD_Y-j);
		}
	}
    INFO("info Yi::init all chessmans added to the chessLayout & revChessLayout.\n");
	INFO("info Yi::init exited.\n");
}

void Yi::finit()
{
	INFO("info YI::finit enterd.\n");
	//delete maps
	for (int i=0; i<BOARD_X; ++i){
		for (int j=0; j<BOARD_Y; ++j){
			if (maps[i][j] != NULL){
				delete maps[i][j];
			}
		}
	}

}
