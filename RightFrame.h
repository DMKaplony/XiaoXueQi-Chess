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

//forward declarations
class QObject;
class QTextEdit;
class QPoint;
class Chess;
class Button;

//RightFrame class
class RightFrame:public QObject{
    Q_OBJECT
public:
	//constructor & destructor
    RightFrame(Chess *chess);
    ~RightFrame();
	//other functions
	void updateStatusLabel(STATUS_TYPE status);
    //friend class
    friend class Chess;

private slots:
	//slots
    void pVpButtonClicked();
    void pVaButtonClicked();
    void aVaButtonClicked();
    void recorderButtonClicked();
    void optionsButtonClicked();
    void backButtonClicked();
    void startButtonClicked();
    void regretButtonClicked();
    void endButtonClicked();
    void saveGameButtonClicked();
    void loadGameButtonClicked();
    void loadAIButtonClicked();
    void loseButtonClicked();
    void prevStepButtonClicked();
    void nextStepButtonClicked();

private:

    //enum & consts
    enum MENU_TYPE{MAIN_MENU, PVP_MENU, PVA_MENU, AVA_MENU, RECORDER_MENU, OPTIONS_MENU, NON_MENU};
    MENU_TYPE currMenu;
    static const QPoint MENU_LEFT_POINT;
    static const QPoint MENU_MID_POINT;
    static const QPoint MENU_RIGHT_POINT;
    static const QPoint MENU_STEP;

    static const int MAIN_MENU_SIZE = 6;
    static const int PVP_MENU_SIZE = 6;
    static const int PVA_MENU_SIZE = 7;
    static const int AVA_MENU_SIZE = 5;
    static const int RECORDER_MENU_SIZE = 4;
    static const int OPTIONS_MENU_SIZE = 100;
    static const int DURING;
    static const QPoint HISTORY_POS;
    static const QPoint STATUS_LABEL_POS;
    static const QSize HISTORY_SIZE;

    //father pointer
    Chess *parent;

	//history
    QTextEdit *history;

	//status
	QLabel *statusLabel;

	//main-menu buttons
    Button *pVpButton;
    Button *pVaButton;
    Button *aVaButton;
    Button *recorderButton;
    Button *optionsButton;
    Button *exitButton;

	//secondary-menu buttons
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

	//arrays for menu
    Button *mainMenu[MAIN_MENU_SIZE];
    Button *pVpMenu[PVP_MENU_SIZE];
    Button *pVaMenu[PVA_MENU_SIZE];
    Button *aVaMenu[AVA_MENU_SIZE];
    Button *recorderMenu[RECORDER_MENU_SIZE];
    Button *optionsMenu[OPTIONS_MENU_SIZE];

	//animation groups
    QParallelAnimationGroup *mainAnimGroup;
    QParallelAnimationGroup *pVpAnimGroup;
    QParallelAnimationGroup *pVaAnimGroup;
    QParallelAnimationGroup *aVaAnimGroup;
    QParallelAnimationGroup *recorderAnimGroup;
    QParallelAnimationGroup *optionsAnimGroup;


    //animation-creator
    QParallelAnimationGroup *createMasterAnimGroup(Button *menu[], int size, const QPoint &startPoint, int during);
    QParallelAnimationGroup *createSecondaryAnimGroup(Button *menu[], int size, const QPoint &startPoint, int during);

};



#endif // RightFrame_H
