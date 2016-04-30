
#ifndef _SERVERSAM_HPP_
#define _SERVERSAM_HPP_

#include "cocos2d.h"
#include "Player.h"
#include <array>
#include "Pterodactyl.h"
#include "Candy.h"
#include "ServerMessage.hpp"
#include "ServerDemoScene.h" 
#include "LevelManager.hpp"

class ServerDemo;

class ServerSam : public cocos2d::Sprite
{

public:
	ServerSam() {};
	~ServerSam() {};
	static ServerSam* create(ServerDemo* ptr, bool vis = true);
	void initialize(bool vis = true);
	
	void setPriority(std::vector<std::vector<char>> tiles, std::vector<std::vector<char>> dry, int time);

	//gameloop ServerSam function
	void runAI(std::vector<Player*>* players);
	//update ServerSam knowledge
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
	// CAW CAW CAW
	void pteraSummon();

	void munch();

	void munching();
	//the index of the ai's current target
	int getTarget();
	//the current action type the ServerSam uses, use to determine animations and whatnot
	

	//number key located at the end of file
	int getBehavior();
	bool timeCheck();
	void setAnim(std::string s) { animstate = s; }
	std::string getAnim() { return animstate; }
	void linkPtera(Pterodactyl* pterodactyl);
	void linkCandy(Candy* candies);
	void attachLevel(LevelManager* levelmanager);
	void lowerReactW(void);
	void incReactW(void);

	void walkOn();
	void teleportOn();
	void candyOn();
	void pteraOn();
	void walkOff();
	void teleportOff();
	void candyOff();
	void pteraOff();



	ServerDemo* serverptr;

private:


	int target = 0;
	int behavior = 0;
	int behavior_timer = 0;
	float walk_speed = 2;
	int charge_speed = 4;
	int x = 0, y = 0;
	int candy_spawn_distance = 200;

	std::vector<Player*>* player_list;
	std::vector<int> distance;
	bool behavior_unlocked = true;
	int priority[4];
	bool idle = false;
	bool flag = true;
	bool pteraphase = 0;

	//new vals for wait time before sam pursues candy
	int sam_candy_dist = 0;
	int player_candy_dist = 9999;
	int player_dist_check = 0;
	int reaction_time_weight = 8; //weight for player reaction time, default is avg human reaction time of 0.25s

	//statistics

	//how many times sam/player get candy
	int sam_candy_score = 0;
	int pl_candy_score = 0;


	//timers
	int teleport_cd = 150;
	int secondary_time = 0;
	int idle_time = 50;
	int walk_time = 100;
	int charge_teleport_time = 50;
	int teleport_arrival_time = 25;
	int teleport_fail_timer = 50;
	int munch_time = 100;
	int sprint_timer = 60;
	int candy_wait = 0;

	std::string animstate = "";

	std::vector<int> behaviors{1,3};
	bool b_walk = true;
	bool b_teleport = true;
	bool b_candy = false;
	bool b_ptera = false;

	//external items
	cocos2d::TMXLayer* blockage;
	LevelManager* lvm;

	//links
	Pterodactyl* ptera;
	Candy* candy;

};

#endif // _ServerSam_HPP_