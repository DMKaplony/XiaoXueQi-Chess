// -*- C++ -*-
#ifndef IMAGE_H
#define IMAGE_H

#include <QLabel>
#include "Chessman.h"

class Chessman;

class ImageLoadError{};

class Image:public QLabel{
	Q_OBJECT
public:
    Image(const QString &path, const QSize &size);
	~Image();
	void addFather(Chessman *father);
protected:
	void mousePressEvent(QMouseEvent *e);
	void mouseReleaseEvent(QMouseEvent *e);
private:
	bool imagePressed;
	Chessman *fatherChessman;
signals:
	void clicked(Chessman *Chessman);
};

#endif
