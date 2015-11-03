#ifndef _VILLAIN_HPP_
#define _VILLAIN_HPP_

#include "cocos2d.h"
#include "Player.h"

class Villain : public cocos2d::Sprite
{

public:
	Villain(){};
	~Villain(){};

	void runAI(std::vector<Player*>* players);
	static Villain* create();
	static Villain* create(int playernum);


	void setHitpoints(int hp){ hitpoints = hp; }
	int getHitpoints(){ return hitpoints; }

private:

	int hitpoints = 1;
	int speedboost = 1;
	int state = 1;
	int jeffreygivememoreattributes = 1;

};


#endif // _VILLAIN_HPP_
