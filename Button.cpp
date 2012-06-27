#include "Button.h"

Button::Button(const QString &text)
{
    this->setText(text);
    this->setFont(QFont(QString("AJU YaHei_Consolas"), 25));
}

Button::~Button()
{
}



void Button::mousePressEvent(QMouseEvent *e)
{
    buttonPressed = true;
}

void Button::mouseReleaseEvent(QMouseEvent *e)
{
    if (buttonPressed){
        emit clicked();
        buttonPressed = false;
    }
}
