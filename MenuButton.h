#ifndef MENUBUTTON_H
#define MENUBUTTON_H

#include "Button.h"

class MenuButton:public Button{
    Q_OBJECT
public:
    //constructor & destructor
    MenuButton(const QString &text, bool _isMaster,
               int _slaveIndex, int _index, QWidget *parent=0);
    ~MenuButton();
protected:
    //implementations
    void mouseReleaseEvent(QMouseEvent *);
private:
    //menu info
    bool isMaster;
    int slaveIndex;
    int index;
signals:
    //signal for click
    void clicked(bool isMater, int slaveIndex, int index);
};

#endif // MENUBUTTON_H
