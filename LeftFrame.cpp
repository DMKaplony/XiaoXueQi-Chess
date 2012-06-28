#include "LeftFrame.h"

//consts

const QSize LeftFrame::HEADER_SIZE = QSize(100, 100);
const QPoint LeftFrame::HEADER_B_POS = QPoint(20, 30);
const QPoint LeftFrame::HEADER_R_POS = QPoint(20, 350);
const QPoint LeftFrame::INFO_B_POS = QPoint(20, 130);
const QPoint LeftFrame::INFO_R_POS = QPoint(20, 450);
const QPoint LeftFrame::REV_BUTTON_POS = QPoint(20, 300);

//constructor
LeftFrame::LeftFrame(Chess *chess)
{
    headerB = new Image(QString((SOURCE_PATH + HEADER_B_IMG).c_str()), HEADER_SIZE, chess);
	headerB->move(HEADER_B_POS);
    headerR = new Image(QString((SOURCE_PATH + HEADER_R_IMG).c_str()), HEADER_SIZE, chess);
	headerR->move(HEADER_R_POS);
    infoB = new QLabel("infoB", chess);
	infoB->move(INFO_B_POS);
    infoR = new QLabel("infoR", chess);
	infoR->move(INFO_R_POS);
    revButton = new Button(tr(EXCHANGE_STR.c_str()), chess);
	revButton->move(REV_BUTTON_POS);
    chess->connectRevButton(revButton);
}

//destructor
LeftFrame::~LeftFrame()
{
    delete headerR;
    delete headerB;
    delete infoB;
    delete infoR;
    delete revButton;
}

