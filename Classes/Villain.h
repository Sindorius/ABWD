#ifndef _VILLAIN_HPP_
#define _VILLAIN_HPP_

#include "cocos2d.h"
#include "Player.h"
#include <array>

class Villain : public cocos2d::Sprite
{

public:
	Villain() {};
	~Villain() {};


	static Villain* create();
	//static Villain* create(int playernum);
	
	void setPriority(std::vector<std::vector<char>> tiles);

	//gameloop villain function
	void runAI(std::vector<Player*>* players);
	//update villain knowledge
	void calculations();
	//determines which behavior the ai should use
	void chooseBehavior();
	//walk to target
	void walk();
	//charge at target
	void charge();
	//charge charge
	void chargeCharge();
	//warp to a location
	void teleport();
	//charge teleport
	void chargeTeleport();
	//idle
	void wait();
	//the index of the ai's current target
	int getTarget();
	//the current action type the villain uses, use to determine animations and whatnot
	//number key located at the end of file
	int getBehavior();
	bool timeCheck();
	void setAnim(std::string s) { animstate = s; }
	std::string getAnim() { return animstate; }

private:


	int target = 0;
	int behavior = 0;
	int behavior_timer = 0;
	float walk_speed = 2;
	int charge_speed = 4;
	int x, y;
	int teleport_cd = 150;
	std::vector<Player*>* player_list;
	std::vector<int> distance;
	bool behavior_unlocked = true;
	int priority[4];
	bool idle = false;


	int idle_time = 50;
	int walk_time = 100;
	int charge_teleport_time = 80;
	int teleport_fail_timer = 50;

	std::string animstate = "";

};
/*
behavior code
code 0 - ai will walk towards the specified target parameter with no special actions
code 1 - ai does a charge sequence
*/

#endif // _VILLAIN_HPP_