#ifndef DEF_H
#define DEF_H

#include <string>
using namespace std;

#include <QSize>
#include <QPoint>


#define DEBUG

#ifdef DEBUG
#define INFO printf
#else
#define INFO
#endif

const int TIE_STEP = 60;
const string WIN_TITLE = "CHESS";
const string EXCHANGE_STR = "Exchange";
const string HEADER_R_IMG = "headerR.png";
const string HEADER_B_IMG = "headerB.png";

const int REV_ANIM_TIME = 2000;
const int BOARD_X = 11;
const int BOARD_Y = 10;




const string BLANK_IMG = "BLANK.png";

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

const string CHESSMAN_IMG[] = {"R_JIANG.png", "R_SHI.png", "R_XIANG.png",
                               "R_MA.png", "R_CHE.png", "R_PAO.png", "R_BING.png",
                               "B_JIANG.png", "B_SHI.png", "B_XIANG.png",
                               "B_MA.png", "B_CHE.png", "B_PAO.png", "B_BING.png"};

const int NUM_OF_CHESSMAN = 32;
const int KIND_OF_CHESSMAN = 14;
const string SOURCE_PATH = "./sources/";
const string BOARD_IMG = "BOARD.png";
const string BACKGROUND_IMG = "background.png";
const string INDICATOR_IMG = "indicator.png";

const string RAI_NAME = "RAI.so";
const string BAI_NAME = "BAI.so";

const int CHESS_NUM[] = {1, 2, 2, 2, 2, 2, 5,
						 1, 2, 2, 2, 2, 2, 5};
enum CHESSMAN_TYPE{R_JIANG, R_SHI, R_XIANG, R_MA, R_CHE, R_PAO, R_BING,
				B_JIANG, B_SHI, B_XIANG, B_MA, B_CHE, B_PAO, B_BING,
				NON};

enum STATUS_TYPE{STATUS_PLAY, STATUS_R_WIN, STATUS_B_WIN, STATUS_TIE, STATUS_END, STATUS_NON};
enum CHESS_ROLE{ROLE_R, ROLE_B, ROLE_NON};
enum PLAYER_ROLE{ROLE_PLAYER, ROLE_AI, NO_PLAYER};
enum GAME_TYPE{GAME_PVP, GAME_PVA, GAME_AVA, GAME_REC};




const string R_TURN_STR = "Red's Turn";
const string B_TURN_STR = "Black's Turn";
const string NO_PLAYER_STR = "No Player";
const string R_WIN_STR = "Red Win!";
const string B_WIN_STR = "Black Win!";
const string TIE_STR = "Tie!";
const string NO_GAME_STR = "No Game";
const string GAME_ENDED_STR = "Game Ended";


const int MASTER_MENU_ITEM_NUM = 6;
const string MASTER_MENU_ITEM_NAME[]=
{"Player vs Player", "Player vs AI", "AI vs AI",
 "Recorder", "Options", "Exit"
};

const int SLAVE_MENU_ITEM_NUM[] = {6,7,6,6,0,0};
const string SLAVE_MENU_ITEM_NAME[][7]=
{{"Start Game", "Regret", "End Game", "Save Game", "Load Game", "Back", ""},
 {"Load AI", "Start Game", "Regret", "Give Up", "Save Game", "Load Game", "Back"},
 {"Load AI", "Start Game", "End Game", "Save Game", "Load Game", "Back", ""},
 {"Load Game", "Prev Step", "Next Step", "Auto Step", "End Game","Back", ""},
 {"", "", "", "", "", "", ""},
 {"", "", "", "", "", "", ""}
};
const bool SLAVE_MENU_INIT_STATE[][7]=
{
{1,0,0,0,1,1,0},
{1,1,0,0,0,1,1},
{1,1,0,0,1,1,0},
{1,0,0,0,0,1,0},
{0,0,0,0,0,0,0},
{0,0,0,0,0,0,0}
};
const bool SLAVE_MENU_START_STATE[][7]=
{
{0,1,1,1,0,1,0},
{0,0,1,1,1,0,1},
{0,0,1,1,0,1,0},
{0,1,1,1,1,1,0},
{0,0,0,0,0,0,0},
{0,0,0,0,0,0,0}
};
const bool SLAVE_MENU_END_STATE[][7]=
{
{1,0,0,1,1,1,0},
{1,1,0,0,1,1,1},
{1,1,0,1,1,1,0},
{1,0,0,0,0,1,0},
{0,0,0,0,0,0,0},
{0,0,0,0,0,0,0}
};
#endif
