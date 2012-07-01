// -*- C++ -*-
#ifndef RightFrame_H
#define RightFrame_H

#include <QObject>
#include <QTextEdit>
#include <QPoint>
#include <QParallelAnimationGroup>
#include <QPropertyAnimation>

#include "def.h"
#include "Chess.h"
#include "Button.h"
#include "Menu.h"

//forward declarations
class Chess;
class Menu;

//RightFrame class
class RightFrame:public QObject{
    Q_OBJECT

public:
	//constructor & destructor
    RightFrame(Chess *chess);
    ~RightFrame();
    void connectMenuButtons();
    void setStatus(const QString &text);

    void setSlaveMenuEndState();

public slots:
    void menuHandler(bool isMaster, int slaveIndex, int index);

private:
    static const QPoint RECORDER_TEXT_POS;
    static const QPoint STATUS_LABEL_POS;
    static const QSize RECORDER_TEXT_SIZE;

    //father pointer
    Chess *parent;

    //recorderText
    QTextEdit *recorderText;

	//status
	QLabel *statusLabel;

    //menu
    Menu *menu;

    void setSlaveMenuInitState(int slaveIndex);
    void setSlaveMenuStartState(int slaveIndex);
    void setSlaveMenuEndState(int slaveIndex);
};



#endif // RightFrame_H
