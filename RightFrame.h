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

class QObject;
class QTextEdit;
class QPoint;
class Chess;
class Button;


class RightFrame:public QObject{
    Q_OBJECT
public:
    RightFrame(Chess *chess);
    ~RightFrame();
	void updateStatusLabel(STATUS_TYPE status);
    void showButtons();

private slots:
    void pVpButtonClicked();
    void pVaButtonClicked();
    void aVaButtonClicked();
    void recorderButtonClicked();
    void optionsButtonClicked();
    void backButtonClicked();

private:
    QParallelAnimationGroup *createAnimGroup(Button *menu[], int size, const QPoint &startPoint, int during);


    QTextEdit *history;
	QLabel *statusLabel;
    Button *pVpButton;
    Button *pVaButton;
    Button *aVaButton;
    Button *recorderButton;
    Button *optionsButton;

    Button *startButton;
	Button *regretButton;
	Button *endButton;
	Button *saveGameButton;
	Button *backButton;
	Button *loadAIButton;
	Button *loseButton;
	Button *loadGameButton;
	Button *prevStepButton;
	Button *nextStepButton;

    Button *mainMenu[5];
    Button *pVpMenu[6];
    Button *pVaMenu[7];
    Button *aVaMenu[5];
    Button *recorderMenu[4];
    Button *optionsMenu[100];

    QParallelAnimationGroup *mainAnimGroup;
    QParallelAnimationGroup *pVpAnimGroup;
    QParallelAnimationGroup *pVaAnimGroup;
    QParallelAnimationGroup *aVaAnimGroup;
    QParallelAnimationGroup *recorderAnimGroup;
    QParallelAnimationGroup *optionsAnimGroup;

    enum MENU_TYPE{MAIN_MENU, PVP_MENU, PVA_MENU, AVA_MENU, RECORDER_MENU, OPTIONS_MENU, NON_MENU};
    MENU_TYPE currMenu;
    static const QPoint MENU_LEFT_POINT;
    static const QPoint MENU_MID_POINT;
    static const QPoint MENU_RIGHT_POINT;
    static const QPoint MENU_STEP;

    static const int MAIN_MENU_SIZE;
    static const int PVP_MENU_SIZE;
    static const int PVA_MENU_SIZE;
    static const int AVA_MENU_SIZE;
    static const int RECORDER_MENU_SIZE;
    static const int OPTIONS_MENU_SIZE;


};



#endif // RightFrame_H
