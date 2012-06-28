// -*- C++ -*-
#ifndef BUTTON_H
#define BUTTON_H

#include <QLabel>

class QLabel;

//button class
class Button:public QLabel{
    Q_OBJECT
public:
	//constructor & destructor
    Button(const QString &text, QWidget *parent=0);
    ~Button();
public slots:
    void enable();
protected:
	//implementations
    void mousePressEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);
    void enterEvent(QEvent *);
    void leaveEvent(QEvent *);
private:
	//variable
    bool buttonPressed;
signals:
	//signal for click
    void clicked();
};

#endif // BUTTON_H
