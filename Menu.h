// -*- c++ -*-
#ifndef MENU_H
#define MENU_H

#include <QObject>
#include <QPropertyAnimation>
#include <QParallelAnimationGroup>

#include <vector>

using namespace std;

#include "MenuButton.h"
#include "Chess.h"
#include "RightFrame.h"

//forward declarations
class Chess;
class RightFrame;

class Menu:public QObject{
    Q_OBJECT
public:
    //Error classes
    class MasterIndexOutOfRangeError{};
    class SlaveIndexOutOfRangeError{};
    class InvalidMenuButtonError{};
    //constructor & destructor
    Menu(Chess *_parent=0);
    ~Menu();
    //visible setters
    void setAllVisible(bool visible);
    void setMasterVisible(bool visible);
    void setSlaveVisible(bool visible);
    //enabled setters
    void setButtonEnabled(bool isMaster, int slaveIndex, int index, bool enabled);

    //MenuButton creators
    void createMasterButton(const QString &text);
    void createSlaveButton(const QString &text, int slaveIndex);
    //animation creator
    void createAnim();
    //connecter
    //void setConnection(void (*fun)(bool, int, int));
    void setConnection(RightFrame *_parent);
    //getter
    int getCurrSlaveIndex()const;

public slots:
    //slots
    void switch2Master();
    void switch2Seconary(int slaveIndex);
private:
    //consts
    static const QPoint MENU_LEFT_POINT;
    static const QPoint MENU_MID_POINT;
    static const QPoint MENU_RIGHT_POINT;
    static const QPoint MENU_STEP;
    static const int DURING;

    //parent pointer
    Chess *parent;
    //curr menu
    bool isMaster;
    int currSlaveIndex;

    //master & slave menu buttons
    vector<MenuButton *> masterMenu;
    vector< vector<MenuButton *> > slaveMenu;

    //master & slave menu animation groups
    vector<QParallelAnimationGroup *> slaveAnimGroup;
    QParallelAnimationGroup *masterAnimGroup;

    //menu visibility setter
    void setMenuVisible(vector<MenuButton *> *menu, bool visible);

    //animation-creator
    QParallelAnimationGroup *createMasterAnimGroup();
    QParallelAnimationGroup *createSlaveAnimGroup(int slaveIndex);
};

#endif // MENU_H
