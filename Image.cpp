#include "Image.h"

Image::Image(const QString &path, const QSize &size)
{
	QImage *img = new QImage;
	if (!(img->load(path))){
		delete img;
		throw ImageLoadError();
	}
	this->setPixmap(QPixmap::fromImage(
							img->scaled(size, Qt::IgnoreAspectRatio)));
}

Image::~Image()
{
}


void Image::addFather(Chessman *father)
{
	fatherChessman = father;
}


void Image::mousePressEvent(QMouseEvent *e)
{
	imagePressed = true;
}

void Image::mouseReleaseEvent(QMouseEvent *e)
{
	if (imagePressed){
		printf("info Image::mouseReleaseEvent clicked emitted\n");
        //printf("%d\n", this->fatherChessman->getType());
		emit clicked(fatherChessman);
		imagePressed = false;
	}
}
