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

	void setColor(std::string c) { color = c; }
	std::string getColor() { return color; }
	void setAnim(std::string s) { animstate = s; }
	std::string getAnim() { return animstate; }



private:
	int playernumber = 0;
	int inventoryitem = 0;
	int hitpoints = 1;
	int speedboost = 1;

	std::string color = "";
	std::string animstate = "";
};


#endif // _PLAYER_HPP_
