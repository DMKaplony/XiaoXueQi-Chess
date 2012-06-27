/*
 * Main CPP file for the project CHESS
 */

#include <QApplication>

#include "Chess.h"


int main(int argc, char **argv)
{
    //create the application
	QApplication app(argc, argv);

    Chess chess;
    chess.show();

	return app.exec();
}
