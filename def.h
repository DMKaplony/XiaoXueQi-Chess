#ifndef DEF_H
#define DEF_H

#include <string>

using namespace std;

#include "Point.h"

#ifdef DEBUG
#define INFO
#else
#define INFO printf
#endif

const int BOARD_X = 11;
const int BOARD_Y = 10;

const string BLANK = "BLANK";

const int CHESS_POS[][2] = {{10,5},{10,4},{10,6},{10,3},{10,7},
								 {10,2},{10,8},{10,1},{10,9},{8,2},
								 {8,8},{7,1},{7,3},{7,5},{7,7},{7,9},
								 {1,5},{1,4},{1,6},{1,3},{1,7},
								 {1,2},{1,8},{1,1},{1,9},{3,2},
								 {3,8},{4,1},{4,3},{4,5},{4,7},{4,9}};
//consts for the game
const string CHESS_NAME[] = {"R_JIANG", "R_SHI", "R_XIANG", 
							 "R_MA", "R_CHE", "R_PAO", "R_BING",
							 "B_JIANG", "B_SHI", "B_XIANG",
							 "B_MA", "B_CHE", "B_PAO", "B_BING"};
const int NUM_OF_CHESSMAN = 32;
const int KIND_OF_CHESSMAN = 14;
const string SOURCE_PATH = "./sources/";
const string BOARD_NAME = "BOARD";
const string IMG_TYPE = ".png";
const int CHESS_NUM[] = {1, 2, 2, 2, 2, 2, 5,
						 1, 2, 2, 2, 2, 2, 5};
enum CHESS_TYPE{R_JIANG, R_SHI, R_XIANG, R_MA, R_CHE, R_PAO, R_BING,
				B_JIANG, B_SHI, B_XIANG, B_MA, B_CHE, B_PAO, B_BING,
				BOARD, NON};

enum STATUS_TYPE{PLAY, R_WIN, B_WIN, TIE, NOTBEGIN};

#endif
