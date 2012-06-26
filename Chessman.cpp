#include "Chessman.h"

Chessman::Chessman(Point _pos, CHESS_TYPE _type, Image *_img)
	:img(_img)
{
	pos = _pos;
	type = _type;
	printf("");
	//	alive = false;
}

Chessman::~Chessman()
{
	delete img;
}

Point Chessman::getPos()const
{
	return pos;
}

CHESS_TYPE Chessman::getType()const
{
	return type;
}

Image *Chessman::getImg()const
{
	return img;
}

bool Chessman::checkPos(const Point &_pos)const
{
	INFO("info Chessman::checkPos executed.\n");
	int x = _pos.getX();
	int y = _pos.getY();
	if (x < 1 || y < 1 || x >= BOARD_X || y >= BOARD_Y){
		return false;
	}
	switch (type){
	case R_JIANG:
		if (abs(9-x)<=1 && abs(5-y)<=1){
			return true;
		}else{
			return false;
		}
		break;
	case B_JIANG:
		if (abs(2-x)<=1 && abs(5-y)<=1){
			return true;
		}else{
			return false;
		}
		break;
	case R_SHI:
		if (x==8 || x==10){
			if (y==4 || y==6){
				return true;
			}else{
				return false;
			}
		}else if (x==9 && y==5){
			return true;
		}else{
			return false;
		}
		break;
	case B_SHI:
		if (x==1 || x==3){
			if (y==4 || y==6){
				return true;
			}else{
				return false;
			}
		}else if (x==2 && y==5){
			return true;
		}else{
			return false;
		}
		break;
	case R_XIANG:
		if (x==6 || x==10){
			if (y==3 || y==7){
				return true;
			}else{
				return false;
			}
		}else if (x==8){
			if (y==1 || y==5 || y==9){
				return true;
			}else{
				return false;
			}
		}else{
			return false;
		}
		break;
	case B_XIANG:
		if (x==1 || x==5){
			if (y==3 || y==7){
				return true;
			}else{
				return false;
			}
		}else if (x==3){
			if (y==1 || y==5 || y==9){
				return true;
			}else{
				return false;
			}
		}else{
			return false;
		}
		break;
	case R_BING:
		if (x > 5){
            if ((x<8)&&(y%2==1)){//y==1,3,5,7,9
				return true;
            }else{
                return false;
            }
		}
        return true;
		break;
	case B_BING:
		if (x < 6){
            if ((x>3)&&(y%2==1)){//y==1,3,5,7,9
				return true;
            }else{
                return false;
            }
		}
        return true;
		break;
	case BOARD:
	case NON:
		printf("312");
		throw InvalidMoveError();
		break;
	default:
		return true;
	};
	throw UnreachableError();
}


bool Chessman::canGo(Chessman *maps[11][10], const Point &_pos)const
{
	printf("info Chessman::canGo entered\n");
	if (!checkPos(_pos)){
		return false;
	}

	if (pos == _pos){//precheck for speed
		return false;
	}
	int x = pos.getX();
	int y = pos.getY();
	int _x = _pos.getX();
	int _y = _pos.getY();

	switch (type){
	case R_JIANG:
	case B_JIANG:
		if (abs(x-_x)+abs(y-_y)==1){
			return true;
		}
		return false;
		break;
	case R_SHI:
	case B_SHI:
		if (abs(x-_x)==1 && abs(y-_y)==1){
			return true;
		}
		return false;
		break;
	case R_XIANG:
	case B_XIANG:
		if (abs(x-_x)==2 && abs(y-_y)==2){
			if (maps[(x+_x)/2][(y+_y)/2]->getType() == NON){
				return true;
			}
		}
		return false;
		break;
	case R_MA:
	case B_MA:
		if (abs(x-_x)==2){
			if (abs(y-_y)==1 && maps[(x+_x)/2][y]->getType()==NON){
				return true;
			}
		}else if (abs(x-_x)==1){
            if (abs(y-_y)==2 && maps[x][(y+_y)/2]->getType()==NON){
				return true;
			}
		}
		return false;
		break;
	case R_CHE:
	case B_CHE:
		if (x==_x){
			int cnt = 0;
			int i = min(y, _y);
			int j = max(y, _y);
			while (++i<j){
				if (maps[x][i]->getType() != NON){
					++cnt;
				}
			}
			if (cnt == 0){
				return true;
			}else{
				return false;
			}
		}
		if (y==_y){
			int cnt = 0;
			int i = min(x, _x);
			int j = max(x, _x);
			while (++i<j){
				if (maps[i][y]->getType() != NON){
					++cnt;
				}
			}
			if (cnt == 0){
				return true;
			}else{
				return false;
			}
		}
		return false;
		break;
	case R_PAO:
	case B_PAO:
		if (x==_x){
			int cnt = 0;
			int i = min(y, _y);
			int j = max(y, _y);
			while (++i<j){
				if (maps[x][i]->getType() != NON){
					++cnt;
				}
			}
			if ((maps[x][_y]->getType()==NON && cnt==0)
				|| (maps[x][_y]->getType()!=NON && cnt==1)){
				return true;
			}else{
				return false;
			}
		}
		if (y==_y){
			int cnt = 0;
			int i = min(x, _x);
			int j = max(x, _x);
			while (++i<j){
				if (maps[i][y]->getType() != NON){
					++cnt;
				}
			}
			if ((maps[_x][y]->getType()==NON && cnt==0)
				|| (maps[_x][y]->getType()!=NON && cnt==1)){
				return true;
			}else{
				return false;
			}

		}
		return false;
		break;

	case R_BING:
		if ((x==7 && _x==6 && y==_y)
			|| (x==6 && _x==5 && y==_y)){
			return true;
		}
		if (x<=5 && _x<=x && abs(x-_x)+abs(y-_y)==1){
			return true;
		}
		return false;
		break;
	case B_BING:
		if ((x==4 && _x==5 && y==_y)
			|| (x==5 && _x==6 && y==_y)){
			return true;
		}
		if (x>=6 && _x>=x && abs(x-_x)+abs(y-_y)==1){
			return true;
		}
		return false;
		break;
	default:
		printf("205");
		throw InvalidMoveError();
	};
	throw UnreachableError();
}




void Chessman::moveTo(Chessman *maps[11][10], const Point &_pos)
{
	printf("info Chessman::moveTo entered\n");
    /*
    if (type != NON && !canGo(maps, _pos)){
        //	printf("%d", canGo(maps, _pos));
		throw InvalidMoveError();
    }*/
	pos = _pos;
	printf("info Chessman::moveTO exited\n");
}

void Chessman::die(Yi *yi, QGridLayout *chessLayout)
{
	printf("info Chessman::die entered\n");
	//	alive = false;
	type = NON;
    chessLayout->removeWidget(img);
	delete img;
    img = new Image(QString((SOURCE_PATH + "board.jpg").c_str()), QSize(30,30));
	img->addFather(this);
    yi->clickConnect(img);
    chessLayout->addWidget(img, pos.getX(), pos.getY());
    printf("infor Chessman::die exited\n");
}

void Chessman::revive()
{

}
