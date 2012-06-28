#include "RightFrame.h"

//consts
const QPoint RightFrame::MENU_LEFT_POINT = QPoint(580, 620);
const QPoint RightFrame::MENU_MID_POINT = QPoint(830, 300);
const QPoint RightFrame::MENU_RIGHT_POINT = QPoint(980, 620);
const QPoint RightFrame::MENU_STEP = QPoint(0, 50);

const QPoint RightFrame::HISTORY_POS = QPoint(830, 20);
const QPoint RightFrame::STATUS_LABEL_POS = QPoint(830, 220);
const QSize RightFrame::HISTORY_SIZE = QSize(200, 180);
const int RightFrame::DURING = 800;
//const QSize STATUS_LABEL_SIZE = QS;


//constructor
RightFrame::RightFrame(Chess *chess)
{
    //save father pointer
    parent = chess;

    //create TextEdit to show history
    history = new QTextEdit(chess);
    history->setReadOnly(true);
    history->resize(HISTORY_SIZE);
    history->move(HISTORY_POS);

    //create label to show current status
    statusLabel =  new QLabel(chess);
//  statusLabel->resize(STATUS_LABEL_SIZE);
    statusLabel->move(STATUS_LABEL_POS);
    statusLabel->setText("status label");

	//create buttons in main-menu
    pVpButton = new Button(tr("Player vs Player"), chess);
    pVaButton = new Button(tr("Player vs AI"), chess);
    aVaButton = new Button(tr("AI vs AI"), chess);
    recorderButton = new Button(tr("Recorder"), chess);
    optionsButton = new Button(tr("Options"), chess);
    exitButton = new Button(tr("Exit"), chess);

	//connect main-menu and secondary-menu
    connect(pVpButton, SIGNAL(clicked()), this, SLOT(pVpButtonClicked()));
    connect(pVaButton, SIGNAL(clicked()), this, SLOT(pVaButtonClicked()));
    connect(aVaButton, SIGNAL(clicked()), this, SLOT(aVaButtonClicked()));
    connect(recorderButton, SIGNAL(clicked()), this, SLOT(recorderButtonClicked()));
    connect(optionsButton, SIGNAL(clicked()), this, SLOT(optionsButtonClicked()));
    connect(exitButton, SIGNAL(clicked()), chess, SLOT(exitGame()));

	//create buttons in secondary-menu
    startButton = new Button(tr("Start Game"), chess);
    regretButton = new Button(tr("Regret"), chess);
    endButton = new Button(tr("End Game"), chess);
    saveGameButton = new Button(tr("Save Game"), chess);
    loadGameButton = new Button(tr("Load Game"), chess);
    backButton = new Button(tr("Back"), chess);
    loadAIButton = new Button(tr("Load AI"), chess);
    loseButton = new Button(tr("Give Up"), chess);
    prevStepButton = new Button(tr("Prev Step"), chess);
    nextStepButton = new Button(tr("Next Step"), chess);

    connect(backButton, SIGNAL(clicked()), this, SLOT(backButtonClicked()));
    connect(startButton, SIGNAL(clicked()), this, SLOT(startButtonClicked()));
    connect(regretButton, SIGNAL(clicked()), this, SLOT(regretButtonClicked()));
    connect(endButton, SIGNAL(clicked()), this, SLOT(endButtonClicked()));
    connect(saveGameButton, SIGNAL(clicked()), this, SLOT(saveGameButtonClicked()));
    connect(loadGameButton, SIGNAL(clicked()), this, SLOT(loadGameButtonClicked()));
    connect(loadAIButton, SIGNAL(clicked()), this, SLOT(loadAIButtonClicked()));
    connect(loseButton, SIGNAL(clicked()), this, SLOT(loseButtonClicked()));
    connect(prevStepButton, SIGNAL(clicked()), this, SLOT(prevStepButtonClicked()));
    connect(nextStepButton, SIGNAL(clicked()), this, SLOT(nextStepButtonClicked()));



	//hide all secondary-menu buttons
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

	//attach each-menu buttons to array
    mainMenu[0] = pVpButton;
    mainMenu[1] = pVaButton;
    mainMenu[2] = aVaButton;
    mainMenu[3] = recorderButton;
    mainMenu[4] = optionsButton;
    mainMenu[5] = exitButton;

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
    mainAnimGroup = createMasterAnimGroup(mainMenu, MAIN_MENU_SIZE, MENU_LEFT_POINT, DURING);
    pVpAnimGroup = createSecondaryAnimGroup(pVpMenu, PVP_MENU_SIZE, MENU_RIGHT_POINT, DURING);
    pVaAnimGroup = createSecondaryAnimGroup(pVaMenu, PVA_MENU_SIZE, MENU_RIGHT_POINT, DURING);
    aVaAnimGroup = createSecondaryAnimGroup(aVaMenu, AVA_MENU_SIZE, MENU_RIGHT_POINT, DURING);
    recorderAnimGroup = createSecondaryAnimGroup(recorderMenu, RECORDER_MENU_SIZE, MENU_RIGHT_POINT, DURING);
//    optionsAnimGroup = createSecondaryAnimGroup(optionsMenu, OPTIONS_MENU_SIZE, MENU_RIGHT_POINT, DURING);

	//set current menu
    currMenu = NON_MENU;
}

//destructor
RightFrame::~RightFrame()
{
    delete history;
	delete statusLabel;

    delete startButton;
    delete regretButton;
    delete endButton;
    delete saveGameButton;
    delete loadGameButton;
    delete backButton;
    delete loadAIButton;
    delete loseButton;
    delete prevStepButton;
    delete nextStepButton;

	delete mainAnimGroup;
	delete pVpAnimGroup;
	delete pVaAnimGroup;
	delete aVaAnimGroup;
	delete recorderAnimGroup;
//	delete optionsAnimGroup;
    delete exitButton;

}

//update status label
void RightFrame::updateStatusLabel(STATUS_TYPE status)
{

}


//create animation group for master menu
QParallelAnimationGroup *RightFrame::createMasterAnimGroup(Button *menu[], int size, const QPoint &startPoint, int during)
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
        anim->setEasingCurve(QEasingCurve::InQuint);
        group->addAnimation(anim);

    }
    return group;
}

//create animation group for secondary menu
QParallelAnimationGroup *RightFrame::createSecondaryAnimGroup(Button *menu[], int size, const QPoint &startPoint, int during)
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
        anim->setEasingCurve(QEasingCurve::InQuint);
        group->addAnimation(anim);
    }
    return group;
}


//show animation
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
    for (int i=0; i<PVP_MENU_SIZE; ++i){
        pVaMenu[i]->show();
    }
    mainAnimGroup->setDirection(mainAnimGroup->Backward);
    mainAnimGroup->start();
    pVaAnimGroup->setDirection(pVaAnimGroup->Forward);
    pVaAnimGroup->start();
}

void RightFrame::aVaButtonClicked()
{
    currMenu = AVA_MENU;
    for (int i=0; i<PVP_MENU_SIZE; ++i){
        aVaMenu[i]->show();
    }
    mainAnimGroup->setDirection(mainAnimGroup->Backward);
    mainAnimGroup->start();
    aVaAnimGroup->setDirection(aVaAnimGroup->Forward);
    aVaAnimGroup->start();
}

void RightFrame::recorderButtonClicked()
{
    currMenu = RECORDER_MENU;
    for (int i=0; i<PVP_MENU_SIZE; ++i){
        recorderMenu[i]->show();
    }
    mainAnimGroup->setDirection(mainAnimGroup->Backward);
    mainAnimGroup->start();
    recorderAnimGroup->setDirection(recorderAnimGroup->Forward);
    recorderAnimGroup->start();
}

void RightFrame::optionsButtonClicked()
{
    currMenu = OPTIONS_MENU;
    for (int i=0; i<PVP_MENU_SIZE; ++i){
        optionsMenu[i]->show();
    }
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
    default:
        break;
    }
    mainAnimGroup->setDirection(mainAnimGroup->Forward);
    mainAnimGroup->start();
    currMenu = MAIN_MENU;
}


void RightFrame::startButtonClicked()
{
    switch (currMenu){
    case PVP_MENU:
        parent->startPlayerVsPlayerGame();
        break;
    case PVA_MENU:
        parent->startPlayerVsAiGame();
        break;
    case AVA_MENU:
        parent->startAiVsAiGame();
        break;
    default:
        break;
    }
}

void RightFrame::regretButtonClicked()
{
    parent->regret();
}

void RightFrame::endButtonClicked()
{
    parent->stopGame();
}

void RightFrame::saveGameButtonClicked()
{

}

void RightFrame::loadGameButtonClicked()
{

}

void RightFrame::loadAIButtonClicked()
{

}

void RightFrame::loseButtonClicked()
{

}

void RightFrame::prevStepButtonClicked()
{

}

void RightFrame::nextStepButtonClicked()
{

}
