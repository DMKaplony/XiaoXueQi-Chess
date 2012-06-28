// -*- C++ -*-
#ifndef IMAGE_H
#define IMAGE_H

#include <QLabel>
#include <QTimer>

#include "Chessman.h"

//forward declarations
class QLabel;
class QTimer;

class Chessman;

//class for ERROR
class ImageLoadError{};

//image class
class Image:public QLabel{
	Q_OBJECT
public:
	//constructor & destructor
    Image(const QString &path, const QSize &size, QWidget *parent=0);
	~Image();
	//addition of constructor
	void addFather(Chessman *father);
    void startFlicker();
    void stopFlicker();
protected:
	//implementation
    void mousePressEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);
private:
	//variables
	bool imagePressed;
	Chessman *fatherChessman;
    //timer
    QTimer *timer;
    //consts
    static const int TIME_INTERVAL = 600;

private slots:
    void flicker();

signals:
	//signal for click
	void clicked(Chessman *Chessman);
};

#endif // IMAGE_H
