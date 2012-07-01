#include "Chessman.h"

//constructor
Chessman::Chessman(const QPoint &_pos, CHESSMAN_TYPE _type, Image *_img,
                   CHESSMAN_TYPE _bakType, Image *_bakImg)
    :bakImg(_bakImg), img(_img)
{
	pos = _pos;
	type = _type;
    bakType = _bakType;
    if (_bakImg != NULL){
        _bakImg->hide();
    }
}

//destructor
Chessman::~Chessman()
{
	delete img;
}

//get-functions
QPoint Chessman::getPos()const
{
	return pos;
}

CHESSMAN_TYPE Chessman::getType()const
{
	return type;
}

CHESS_ROLE Chessman::getRole()const
{
	if (type == NON){
		return ROLE_NON;
	}else if (type < B_JIANG){
		return ROLE_R;
	}else{
		return ROLE_B;
	}
}

Image *Chessman::getImg()const
{
	return img;
}


//check-functions
//check validness of a position
bool Chessman::checkPos(const QPoint &_pos)const
{
	INFO("info Chessman::checkPos executed.\n");
    int x = _pos.x();
    int y = _pos.y();
	//check range
	if (x < 1 || y < 1 || x >= BOARD_X || y >= BOARD_Y){
		return false;
	}
	//check valid position according to type
	switch (type){
	case R_JIANG:
	case B_JIANG:
        if ((abs(9-x)<=1 && abs(5-y)<=1)
            || (abs(2-x)<=1 && abs(5-y)<=1)){
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
	case NON:
		throw InvalidMoveError();
		break;
	default:
		return true;
	};
	throw UnreachableError();
}

//check whether can go
bool Chessman::canGo(Chessman *maps[11][10], const QPoint &_pos)const
{
	printf("info Chessman::canGo entered\n");
	//check the target position
	if (!checkPos(_pos)){
		return false;
	}

	//same position
	if (pos == _pos){
		return false;
	}

    int x = pos.x();
    int y = pos.y();
    int _x = _pos.x();
    int _y = _pos.y();

	//check whether can go according to type
	switch (type){
	case R_JIANG:
	case B_JIANG:
		if (abs(x-_x)+abs(y-_y)==1){
			return true;
        }else if (maps[_x][_y]->getType() == R_JIANG
                || maps[_x][_y]->getType() == B_JIANG){
            int i = min(x, _x);
            int j = max(x, _x);
            while (++i<j){
                if (maps[i][y]->getType() != NON){
                    return false;
                }
            }
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
		throw InvalidMoveError();
	};
	throw UnreachableError();
}



//set-functions
//move the chessman
void Chessman::moveTo(const QPoint &_pos)
{
	printf("info Chessman::moveTo entered\n");
	pos = _pos;
	printf("info Chessman::moveTO exited\n");
}

void Chessman::toggleDeadAndAlive()
{
    printf("info Chessman::toggleDeadAndAlive entered\n");
    //check whether can toggle
    if (bakImg == NULL){
        return;
    }
    //toggle type
    CHESSMAN_TYPE tmpType = type;
    type = bakType;
    bakType = tmpType;

    //hide old img from layout
    img->hide();

    //toggle img
    Image *tmpImg = img;
    img = bakImg;
    bakImg = tmpImg;
    img->move(bakImg->pos());

    //show img
    img->show();
    printf("info Chessman::toggleDeadAndAlive exited\n");
}

//let chessman die
void Chessman::die()
{
    //check whether is dead already
    if (bakType != NON || (bakType == type)){
        //dead already
        return;
    }
    toggleDeadAndAlive();
}

//revive the chessman
void Chessman::revive()
{
    //check whether is alive already
    if (type != NON || bakType == type){
        //alive already
        return;
    }
    toggleDeadAndAlive();
}
