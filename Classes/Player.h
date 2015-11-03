#ifndef _PLAYER_HPP_
#define _PLAYER_HPP_

#include "cocos2d.h"

class Player : public cocos2d::Sprite
{

public:
	Player(){};
	~Player(){};
	static Player* create();
	static Player* create(int playernum);

	int getPlayernum(){ return playernumber; };
	void setPlayernum(int playernum){ playernumber = playernum; };
	void setHitpoints(int hp){ hitpoints = hp; }
	int getHitpoints(){ return hitpoints; }

private:
	int playernumber = 0;
	int inventoryitem = 0;
	int hitpoints = 1;
	int speedboost = 1;

};


#endif // _PLAYER_HPP_
