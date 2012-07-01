#include "MenuButton.h"

//constructor
MenuButton::MenuButton(const QString &text, bool _isMaster,
                       int _slaveIndex, int _index, QWidget *parent)
    :Button(text, parent)
{
    isMaster = _isMaster;
    slaveIndex = _slaveIndex;
    index = _index;
}

//destructor
MenuButton::~MenuButton()
{
}

//overwrite mouseReleaseEvent
void MenuButton::mouseReleaseEvent(QMouseEvent *)
{
    if (buttonPressed){
        emit clicked(isMaster, slaveIndex, index);
        buttonPressed = false;
    }
}


