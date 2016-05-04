
#ifndef _VILLAIN_HPP_
#define _VILLAIN_HPP_

#include "cocos2d.h"
#include "Player.h"
#include <array>
#include "Pterodactyl.h"
#include "Candy.h"
#include "ServerMessage.hpp"
#include "ServerDemoScene.h" 



class Villain : public cocos2d::Sprite
{

public:
	Villain() {};
	~Villain() {};
	static Villain* create(bool vis = true);
	void initialize(bool vis = true);
	
	void setAnim(std::string s) { animstate = s; }
	std::string getAnim() { return animstate; }
	
private:

	std::string animstate = "";

};
/*
behavior code
code 0 - ai will walk towards the specified target parameter with no special actions
code 1 - ai does a charge sequence
*/

#endif // _VILLAIN_HPP_