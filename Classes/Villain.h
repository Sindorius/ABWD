#ifndef _VILLAIN_HPP_
#define _VILLAIN_HPP_

#include "cocos2d.h"
#include "Player.h"

class Villain : public cocos2d::Sprite
{

public:
	Villain(){};
	~Villain(){};

	
	static Villain* create();
	static Villain* create(int playernum);
	//gameloop villain function
	void runAI(std::vector<Player*>* players);
	//the index of the ai's current target
	int getTarget();
	//the current action type the villain uses, use to determine animations and whatnot
	//number key located at the end of file
	int getBehavior();

private:


	int target = 0;
	int behavior = 0;

};
/*
behavior code
code 0 - ai will walk towards the specified target parameter with no special actions
*/

#endif // _VILLAIN_HPP_
