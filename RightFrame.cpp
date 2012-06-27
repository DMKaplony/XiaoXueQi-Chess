#include "RightFrame.h"

const QPoint RightFrame::MENU_LEFT_POINT = QPoint(700, 500);
const QPoint RightFrame::MENU_MID_POINT = QPoint(750, 400);
const QPoint RightFrame::MENU_RIGHT_POINT = QPoint(800, 500);
const QPoint RightFrame::MENU_STEP = QPoint(0, 20);

const int RightFrame::MAIN_MENU_SIZE = 5;
const int RightFrame::PVP_MENU_SIZE = 6;
const int RightFrame::PVA_MENU_SIZE = 7;
const int RightFrame::AVA_MENU_SIZE = 5;
const int RightFrame::RECORDER_MENU_SIZE = 4;
const int RightFrame::OPTIONS_MENU_SIZE = 100;


RightFrame::RightFrame(Chess *chess)
{
    history = new QTextEdit;

    statusLabel =  new QLabel();
    pVpButton = new Button(tr("Player vs Player"));
    pVaButton = new Button(tr("Player vs AI"));
    pVaButton->hide();
    aVaButton = new Button(tr("AI vs AI"));
    recorderButton = new Button(tr("recorder"));
    optionsButton = new Button(tr("options"));

    connect(pVpButton, SIGNAL(clicked()), this, SLOT(pVpButtonClicked()));
    connect(pVaButton, SIGNAL(clicked()), this, SLOT(pVaButtonClicked()));
    connect(aVaButton, SIGNAL(clicked()), this, SLOT(aVaButtonClicked()));
    connect(recorderButton, SIGNAL(clicked()), this, SLOT(recorderButtonClicked()));
    connect(optionsButton, SIGNAL(clicked()), this, SLOT(optionsButtonClicked()));



    startButton = new Button(tr("Start Game"));
	regretButton = new Button(tr("Regret"));
	endButton = new Button(tr("End Game"));
	saveGameButton = new Button(tr("Save Game"));
	loadGameButton = new Button(tr("Load Game"));
	backButton = new Button(tr("Back"));
    loadAIButton = new Button(tr("Load AI"));
    loseButton = new Button(tr("Give Up"));
    prevStepButton = new Button(tr("Prev Step"));
    nextStepButton = new Button(tr("Next Step"));

    connect(backButton, SIGNAL(clicked()), this, SLOT(backButtonClicked()));


    startButton->hide();
    regretButton->hide();
    endButton->hide();
    saveGameButton->hide();
    loadGameButton->hide();
    backButton->hide();
    loadAIButton->hide();
    loseButton->hide();
    prevStepButton->hide();
    nextStepButton->hide();


    mainMenu[0] = pVpButton;
    mainMenu[1] = pVaButton;
    mainMenu[2] = aVaButton;
    mainMenu[3] = recorderButton;
    mainMenu[4] = optionsButton;

    pVpMenu[0] = startButton;
    pVpMenu[1] = regretButton;
    pVpMenu[2] = endButton;
    pVpMenu[3] = saveGameButton;
    pVpMenu[4] = loadGameButton;
    pVpMenu[5] = backButton;

    pVaMenu[0] = loadAIButton;
    pVaMenu[1] = startButton;
    pVaMenu[2] = regretButton;
    pVaMenu[3] = loseButton;
	pVaMenu[4] = saveGameButton;
	pVaMenu[5] = loadGameButton;
	pVaMenu[6] = backButton;

    aVaMenu[0] = loadAIButton;
    aVaMenu[1] = startButton;
	aVaMenu[2] = endButton;
	aVaMenu[3] = saveGameButton;
	aVaMenu[4] = backButton;

	recorderMenu[0] = loadGameButton;
	recorderMenu[1] = prevStepButton;
	recorderMenu[2] = nextStepButton;
	recorderMenu[3] = backButton;

    //create animation for menus
    mainAnimGroup = createAnimGroup(mainMenu, MAIN_MENU_SIZE, MENU_LEFT_POINT, 600);
    pVpAnimGroup = createAnimGroup(pVpMenu, PVP_MENU_SIZE, MENU_RIGHT_POINT, 600);
    pVaAnimGroup = createAnimGroup(pVaMenu, PVA_MENU_SIZE, MENU_RIGHT_POINT, 600);
    aVaAnimGroup = createAnimGroup(aVaMenu, AVA_MENU_SIZE, MENU_RIGHT_POINT, 600);
    recorderAnimGroup = createAnimGroup(recorderMenu, RECORDER_MENU_SIZE, MENU_RIGHT_POINT, 600);
//    optionsAnimGroup = createAnimGroup(optionsMenu, OPTIONS_MENU_SIZE, MENU_RIGHT_POINT, 2000);
    currMenu = NON_MENU;
}

RightFrame::~RightFrame()
{
    delete history;
    delete recorderButton;
    delete optionsButton;
}


void RightFrame::updateStatusLabel(STATUS_TYPE status)
{

}

void RightFrame::showButtons()
{
    backButtonClicked();
}

QParallelAnimationGroup *RightFrame::createAnimGroup(Button *menu[], int size, const QPoint &startPoint, int during)
{
    //create animation for menu
    QParallelAnimationGroup *group = new QParallelAnimationGroup();
    QPropertyAnimation *anim;
    for (int i=0; i<size; ++i)
    {
        anim = new QPropertyAnimation(menu[i], "pos");
        anim->setDuration(during);
        anim->setStartValue(startPoint);
        anim->setEndValue(MENU_MID_POINT + MENU_STEP * i);
        anim->setEasingCurve(QEasingCurve::OutBounce);
        group->addAnimation(anim);
    }
    return group;
}

void RightFrame::pVpButtonClicked()
{
    currMenu = PVP_MENU;
    for (int i=0; i<PVP_MENU_SIZE; ++i){
        pVpMenu[i]->show();
    }
    mainAnimGroup->setDirection(mainAnimGroup->Backward);
    mainAnimGroup->start();
    pVpAnimGroup->setDirection(pVpAnimGroup->Forward);
    pVpAnimGroup->start();
}

void RightFrame::pVaButtonClicked()
{
    currMenu = PVA_MENU;
    mainAnimGroup->setDirection(mainAnimGroup->Backward);
    mainAnimGroup->start();
    pVaAnimGroup->setDirection(pVaAnimGroup->Forward);
    pVaAnimGroup->start();
}

void RightFrame::aVaButtonClicked()
{
    currMenu = AVA_MENU;
    mainAnimGroup->setDirection(mainAnimGroup->Backward);
    mainAnimGroup->start();
    aVaAnimGroup->setDirection(aVaAnimGroup->Forward);
    aVaAnimGroup->start();
}

void RightFrame::recorderButtonClicked()
{
    currMenu = RECORDER_MENU;
    mainAnimGroup->setDirection(mainAnimGroup->Backward);
    mainAnimGroup->start();
    recorderAnimGroup->setDirection(recorderAnimGroup->Forward);
    recorderAnimGroup->start();
}

void RightFrame::optionsButtonClicked()
{
    currMenu = OPTIONS_MENU;
    mainAnimGroup->setDirection(mainAnimGroup->Backward);
    mainAnimGroup->start();
    optionsAnimGroup->setDirection(optionsAnimGroup->Forward);
    optionsAnimGroup->start();
}

void RightFrame::backButtonClicked()
{
    switch (currMenu){
    case PVP_MENU:
        pVpAnimGroup->setDirection(pVpAnimGroup->Backward);
        pVpAnimGroup->start();
        break;
    case PVA_MENU:
        pVaAnimGroup->setDirection(pVaAnimGroup->Backward);
        pVaAnimGroup->start();
        break;
    case AVA_MENU:
        aVaAnimGroup->setDirection(aVaAnimGroup->Backward);
        aVaAnimGroup->start();
        break;
    case RECORDER_MENU:
        recorderAnimGroup->setDirection(recorderAnimGroup->Backward);
        recorderAnimGroup->start();
        break;
    case OPTIONS_MENU:
        optionsAnimGroup->setDirection(optionsAnimGroup->Backward);
        optionsAnimGroup->start();
        break;
    defulat:
        break;
    }
    mainAnimGroup->setDirection(mainAnimGroup->Forward);
    mainAnimGroup->start();
    currMenu = MAIN_MENU;
}
