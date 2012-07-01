#include "Menu.h"

//consts
const QPoint Menu::MENU_LEFT_POINT = QPoint(580, 620);
const QPoint Menu::MENU_MID_POINT = QPoint(830, 300);
const QPoint Menu::MENU_RIGHT_POINT = QPoint(980, 620);
const QPoint Menu::MENU_STEP = QPoint(0, 50);
const int Menu::DURING = 800;

Menu::Menu(Chess *_parent)
    :parent(_parent)
{
    //curr menu
    isMaster = false;
    currSlaveIndex = 0;

    //master & slave menu buttons
    masterMenu.clear();
    slaveMenu.clear();

    //master & slave menu animation groups
    slaveAnimGroup.clear();
    masterAnimGroup = NULL;
}

Menu::~Menu()
{
}

//create animation
void Menu::createAnim()
{
    //create animation for MasterMenu
    if (masterAnimGroup != NULL){
        delete masterAnimGroup;
    }
    masterAnimGroup = createMasterAnimGroup();
    //create animation for SecondartMenus
    int size = masterMenu.size();
    slaveAnimGroup.clear();
    for (int i=0; i<size; ++i){
        slaveAnimGroup.push_back(createSlaveAnimGroup(i));
    }
}

//set menus visible
void Menu::setAllVisible(bool visible)
{
    setMasterVisible(visible);
    setSlaveVisible(visible);
}

void Menu::setMenuVisible(vector<MenuButton *> *menu, bool visible)
{
    if (menu->empty()){
        return;
    }

    vector<MenuButton *>::iterator it;
    for (it=menu->begin(); it!=menu->end(); ++it){
        (*it)->setVisible(visible);
    }

}

void Menu::setMasterVisible(bool visible)
{
    setMenuVisible(&masterMenu, visible);
}

void Menu::setSlaveVisible(bool visible)
{
    int size = masterMenu.size();
    for (int i=0; i<size; ++i){
        setMenuVisible(&slaveMenu[i], visible);
    }
}
//set button enabled
void Menu::setButtonEnabled(bool isMaster, int slaveIndex, int index, bool enabled)
{
    if (isMaster){
        //check range
        if (index >= masterMenu.size()){
            throw MasterIndexOutOfRangeError();
        }
        masterMenu[index]->setEnabled(enabled);
    }else{
        if (slaveIndex >= masterMenu.size()){
            throw MasterIndexOutOfRangeError();
        }
        if (index >= slaveMenu[slaveIndex].size()){
            throw SlaveIndexOutOfRangeError();
        }
        slaveMenu[slaveIndex][index]->setEnabled(enabled);
    }
}

//create MenuButton in master menu
void Menu::createMasterButton(const QString &text)
{
    //create button
    MenuButton *btn = new MenuButton(text, true, 0, masterMenu.size(), parent);
    //add button
    masterMenu.push_back(btn);
    //add animation position
    slaveAnimGroup.push_back(NULL);
    //add slaveMenu
    vector<MenuButton *> vec;
    slaveMenu.push_back(vec);
}

//create MenuButton in slave menu
void Menu::createSlaveButton(const QString &text, int slaveIndex)
{
    //range check
    if (slaveIndex >= masterMenu.size()){
        throw MasterIndexOutOfRangeError();
    }
    //create button
    MenuButton *btn = new MenuButton(text, false, slaveIndex, slaveMenu[slaveIndex].size(), parent);
    //add button
    slaveMenu[slaveIndex].push_back(btn);
}

//create master animation group
QParallelAnimationGroup *Menu::createMasterAnimGroup()
{
    //create animation for menu
    int size = masterMenu.size();
    QParallelAnimationGroup *group = new QParallelAnimationGroup();
    QPropertyAnimation *anim;
    for (int i=0; i<size; ++i){
        anim = new QPropertyAnimation(masterMenu[i], "pos");
        anim->setDuration(DURING);
        anim->setStartValue(MENU_LEFT_POINT);
        anim->setEndValue(MENU_MID_POINT + MENU_STEP * i);
        anim->setEasingCurve(QEasingCurve::OutElastic);
        group->addAnimation(anim);
    }
    return group;
}

//create slave animation group
QParallelAnimationGroup *Menu::createSlaveAnimGroup(int slaveIndex)
{
    //check range
    if (slaveIndex >= masterMenu.size()){
        throw SlaveIndexOutOfRangeError();
    }
    //create animation for menu
    int size = slaveMenu[slaveIndex].size();
    QParallelAnimationGroup *group = new QParallelAnimationGroup();
    QPropertyAnimation *anim;
    for (int i=0; i<size; ++i){
        anim = new QPropertyAnimation(slaveMenu[slaveIndex][i], "pos");
        anim->setDuration(DURING);
        anim->setStartValue(MENU_RIGHT_POINT);
        anim->setEndValue(MENU_MID_POINT + MENU_STEP * i);
        anim->setEasingCurve(QEasingCurve::OutBounce);
        group->addAnimation(anim);
    }
    return group;
}

typedef void (*FunPtr)(bool, int, int);

//connecter
void Menu::setConnection(RightFrame *_parent)//FunPtr fun)
{
    vector<MenuButton *>::iterator it;
    for (it=masterMenu.begin(); it!=masterMenu.end(); ++it){
        //connect(*it, SIGNAL(clicked(bool, int, int)), parent, SLOT((parent->*fun)));
        connect(*it, SIGNAL(clicked(bool, int, int)), _parent, SLOT(menuHandler(bool, int, int)));
    }
    int size = masterMenu.size();
    for (int i=0; i<size; ++i){
        for (it=slaveMenu[i].begin(); it!=slaveMenu[i].end(); ++it){
            connect(*it, SIGNAL(clicked(bool, int, int)), _parent, SLOT(menuHandler(bool, int, int)));
        }
    }

}

//getter
int Menu::getCurrSlaveIndex()const
{
    return currSlaveIndex;
}

//clicked slots
//switch to Master Menu
void Menu::switch2Master()
{
    //check current menu
    if (isMaster){
        return;
    }
    //show master
    setMasterVisible(true);

    //show animations
    slaveAnimGroup[currSlaveIndex]->setDirection(QParallelAnimationGroup::Backward);
    slaveAnimGroup[currSlaveIndex]->start();
    masterAnimGroup->setDirection(QParallelAnimationGroup::Forward);
    masterAnimGroup->start();

    //hide "current" menu
    setMenuVisible(&slaveMenu[currSlaveIndex], false);

    //set masterMenu as current menu
    isMaster = true;
}

//switch to Slave Menu
void Menu::switch2Seconary(int slaveIndex)
{
    //check current menu
    if (!isMaster){
        return;
    }
    //show slaveMenu
    setMenuVisible(&slaveMenu[slaveIndex], true);

    //show animations
    masterAnimGroup->setDirection(QParallelAnimationGroup::Backward);
    masterAnimGroup->start();
    slaveAnimGroup[slaveIndex]->setDirection(QParallelAnimationGroup::Forward);
    slaveAnimGroup[slaveIndex]->start();

    //hide master menu
    setMasterVisible(false);

    //set slaveIndex as current menu
    isMaster = false;
    currSlaveIndex = slaveIndex;
}

