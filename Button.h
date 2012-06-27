// -*- C++ -*-
#ifndef BUTTON_H
#define BUTTON_H

#include <QLabel>

class QLabel;

class Button:public QLabel{
    Q_OBJECT
public:
    Button(const QString &text);
    ~Button();
protected:
    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);
private:
    bool buttonPressed;
signals:
    void clicked();
};

#endif // BUTTON_H
