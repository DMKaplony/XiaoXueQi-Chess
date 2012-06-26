/*
 * Main CPP file for the project YI
 * 
 *
 */

#include <QApplication>

#include "Yi.h"


int main(int argc, char **argv)
{
	QApplication app(argc, argv);

	Yi yi;
	yi.show();

	return app.exec();
}
