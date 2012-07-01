#include "RightFrame.h"

//consts
const QPoint RightFrame::RECORDER_TEXT_POS = QPoint(830, 20);
const QPoint RightFrame::STATUS_LABEL_POS = QPoint(830, 220);
const QSize RightFrame::RECORDER_TEXT_SIZE = QSize(200, 180);


//constructor
RightFrame::RightFrame(Chess *chess)
    :parent(chess)
{
    //create TextEdit to show recorderText
    recorderText = new QTextEdit(chess);
    recorderText->setReadOnly(true);
    recorderText->resize(RECORDER_TEXT_SIZE);
    recorderText->move(RECORDER_TEXT_POS);

    //create label to show current status
    statusLabel =  new QLabel(chess);
    statusLabel->move(STATUS_LABEL_POS);

    //create menu
    menu = new Menu(chess);
    for (int i=0; i<MASTER_MENU_ITEM_NUM; ++i){
        menu->createMasterButton(QString(MASTER_MENU_ITEM_NAME[i].c_str()));
        for (int j=0; j<SLAVE_MENU_ITEM_NUM[i]; ++j){
            menu->createSlaveButton(QString(SLAVE_MENU_ITEM_NAME[i][j].c_str()), i);
        }
    }
    menu->createAnim();
    menu->setConnection(this);
    //hide all slave-menu buttons
    menu->setAllVisible(false);
    menu->switch2Master();
}

void RightFrame::connectMenuButtons()
{
//    menu->setConnection(menuHandler);
}

void RightFrame::setStatus(const QString &text)
{
    statusLabel->setText(text);
    statusLabel->adjustSize();
}

//destructor
RightFrame::~RightFrame()
{
    delete recorderText;
	delete statusLabel;

}


void RightFrame::setSlaveMenuInitState(int slaveIndex)
{
    for (int i=0; i<SLAVE_MENU_ITEM_NUM[slaveIndex]; ++i){
        menu->setButtonEnabled(0, slaveIndex, i, SLAVE_MENU_INIT_STATE[slaveIndex][i]);
    }
}

void RightFrame::setSlaveMenuStartState(int slaveIndex)
{
    for (int i=0; i<SLAVE_MENU_ITEM_NUM[slaveIndex]; ++i){
        menu->setButtonEnabled(0, slaveIndex, i, SLAVE_MENU_START_STATE[slaveIndex][i]);
    }
}

void RightFrame::setSlaveMenuEndState(int slaveIndex)
{
    for (int i=0; i<SLAVE_MENU_ITEM_NUM[slaveIndex]; ++i){
        menu->setButtonEnabled(0, slaveIndex, i, SLAVE_MENU_END_STATE[slaveIndex][i]);
    }
}

void RightFrame::setSlaveMenuEndState()
{
    int slaveIndex=menu->getCurrSlaveIndex();
    for (int i=0; i<SLAVE_MENU_ITEM_NUM[slaveIndex]; ++i){
        menu->setButtonEnabled(0, slaveIndex, i, SLAVE_MENU_END_STATE[slaveIndex][i]);
    }
}


void RightFrame::menuHandler(bool isMaster, int slaveIndex, int index)
{
    if (isMaster){
        menu->switch2Seconary(index);
        if (index >= MASTER_MENU_ITEM_NUM){
            throw Menu::InvalidMenuButtonError();
        }
        if (index == MASTER_MENU_ITEM_NUM-1){
            parent->exitApp();
            return;
        }
        setSlaveMenuInitState(index);
    }else{
        switch(slaveIndex){
        case 0://Player Vs Player
            switch(index){
            case 0://Start Game
                parent->startGame(GAME_PVP);
                setSlaveMenuStartState(0);
                break;
            case 1://Regret
                parent->regret();
                break;
            case 2://End Game
                parent->endGame();
                setSlaveMenuEndState(0);
                break;
            case 3://Save Game
                parent->saveGame();
                break;
            case 4://Load Game
                parent->loadGame();
                setSlaveMenuStartState(0);
                break;
            case 5://Back
                parent->exitGame();
                menu->switch2Master();
                break;
            default:
                throw Menu::InvalidMenuButtonError();
            }
            break;
        case 1://Player Vs Ai
            switch(index){
            case 0://Load AI
                parent->loadSingleAI();
                break;
            case 1://Start Game
                parent->startGame(GAME_PVA);
                setSlaveMenuStartState(1);
                break;
            case 2://Regret
                parent->regret();
                break;
            case 3://End Game
                parent->endGame();
                setSlaveMenuEndState(1);
                break;
            case 4://Save Game
                parent->saveGame();
                break;
            case 5://Load Game
                parent->loadGame();
                setSlaveMenuStartState(1);
                break;
            case 6://Back
                parent->exitGame();
                menu->switch2Master();
                break;
            default:
                throw Menu::InvalidMenuButtonError();
            }
            break;
        case 2://Ai Vs Ai
            switch(index){
            case 0://Load AI
                parent->loadDoubleAI();
                break;
            case 1://Start Game
                parent->startGame(GAME_AVA);
                setSlaveMenuStartState(2);
                break;
            case 2://End Game
                parent->endGame();
                setSlaveMenuEndState(2);
                break;
            case 3://Save Game
                parent->saveGame();
                break;
            case 4://Load Game
                parent->loadGame();
                setSlaveMenuStartState(2);
                break;
            case 5://Back
                parent->exitGame();
                menu->switch2Master();
                break;
            default:
                throw Menu::InvalidMenuButtonError();
            }
            break;
        case 3://recorder
            switch(index){
            case 0://Load Game
                parent->loadGame();
                setSlaveMenuStartState(3);
                break;
            case 1://Prev Step
                parent->prevStep();
                break;
            case 2://Next Step
                parent->nextStep();
                break;
            case 3://Auto Step
                //coming soon
                break;
            case 4://End Game
                parent->endGame();
                setSlaveMenuEndState(3);
                break;
            case 5://Back
                parent->exitGame();
                menu->switch2Master();
                break;
            default:
                throw Menu::InvalidMenuButtonError();
            }
            break;
        case 4://options
            //coming soon
            break;
        case 5://exit
            break;
        }
    }
}
