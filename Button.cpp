#include "Button.h"

//constructor
Button::Button(const QString &text, QWidget *parent)
    :QLabel(parent)
{
    setText(text);
    setFont(QFont(QString("AJU YaHei_Consolas"), 18));
}

//destructor
Button::~Button()
{
}


//slot
void Button::enable()
{
    setEnabled(true);
}


//implementations
void Button::mousePressEvent(QMouseEvent *)
{
    buttonPressed = true;
}

void Button::mouseReleaseEvent(QMouseEvent *)
{
    if (buttonPressed){
        emit clicked();
        buttonPressed = false;
    }
}

void Button::enterEvent(QEvent *)
{
    if(isEnabled()){
        QFont tmp = font();
        tmp.setBold(true);
        setFont(tmp);
        adjustSize();
    }
}

void Button::leaveEvent(QEvent *)
{
    QFont tmp = font();
    tmp.setBold(false);
    setFont(tmp);
    adjustSize();
}
