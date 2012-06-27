#include "LeftFrame.h"

LeftFrame::LeftFrame(Chess *chess)
{
    headerB = new Image(QString((SOURCE_PATH + "headerB.png").c_str()), HEADER_SIZE);
    headerR = new Image(QString((SOURCE_PATH + "headerR.png").c_str()), HEADER_SIZE);
    infoB = new QLabel();
    infoR = new QLabel();
    revButton = new Button(tr("exchange"));
    chess->connectRevButton(revButton);
}

LeftFrame::~LeftFrame()
{
    delete headerR;
    delete headerB;
    delete infoB;
    delete infoR;
    delete revButton;
}
