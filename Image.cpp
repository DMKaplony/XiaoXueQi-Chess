#include "Image.h"

//constructor
Image::Image(const QString &path, const QSize &size, QWidget *parent)
    :QLabel(parent)
{
	QImage *img = new QImage;
	if (!(img->load(path))){
		delete img;
		throw ImageLoadError();
	}
	this->setPixmap(QPixmap::fromImage(
							img->scaled(size, Qt::IgnoreAspectRatio)));
    fatherChessman = NULL;

    //create timer
    timer = new QTimer(this);
    timer->setSingleShot(false);
    timer->setInterval(TIME_INTERVAL);
    connect(timer, SIGNAL(timeout()), this, SLOT(flicker()));
}


//destructor
Image::~Image()
{
}

//add father to the Image (addition of construtor)
void Image::addFather(Chessman *father)
{
	fatherChessman = father;
}

//start flicker
void Image::startFlicker(){
    timer->start();
}
//stop flicker
void Image::stopFlicker(){
    timer->stop();
    show();
}

//implementation
void Image::mousePressEvent(QMouseEvent *)
{
    if (fatherChessman != NULL){
        imagePressed = true;
    }
}

void Image::mouseReleaseEvent(QMouseEvent *)
{
	if (imagePressed){
		printf("info Image::mouseReleaseEvent clicked emitted\n");
        printf("%d\n", this->fatherChessman->getType());
		emit clicked(fatherChessman);
		imagePressed = false;
	}
}


void Image::flicker()
{
    if (isVisible()){
        hide();
    }else{
        show();
    }
}
