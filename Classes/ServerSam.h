
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
#include "ServerMessage.hpp"

class ServerDemo;

class ServerSam : public cocos2d::Sprite
{

public:
	ServerSam(std::vector<Player*>* players);
	~ServerSam() {};
	static ServerSam* create(std::vector<Player*>* players, bool vis = true);
	void initialize(bool vis = true);
	
	void setPriority(std::vector<std::vector<char>> tiles, std::vector<std::vector<char>> dry, int time);

	////////////////////////////////////////////////////////////////////////////////////////////
	//gameloop ServerSam function
	////////////////////////////////////////////////////////////////////////////////////////////
	void runAI();

	////////////////////////////////////////////////////////////////////////////////////////////
	//update ServerSam knowledge 
	////////////////////////////////////////////////////////////////////////////////////////////
	/*
	Identifies nearest player
	*/
	void calculations();

	////////////////////////////////////////////////////////////////////////////////////////////
	//determines which behavior the ai should use
	////////////////////////////////////////////////////////////////////////////////////////////
	/*
	Currently unused
	*/
	void chooseBehavior();

	////////////////////////////////////////////////////////////////////////////////////////////
	//walk to target
	////////////////////////////////////////////////////////////////////////////////////////////
	/*
	OBSOLETE
	*/
	void walk();

	//the index of the ai's current target
	int getTarget();
	
	//////////////////////////////////////////////////////////////////////////////////////////// 
	// Sam behaviors
	////////////////////////////////////////////////////////////////////////////////////////////
	
	////////////////////////////////////////////////////////////////////////////////////////////
	// Empty behavior for start
	////////////////////////////////////////////////////////////////////////////////////////////
	bool emptyBehavior() { return false; };


	////////////////////////////////////////////////////////////////////////////////////////////
	// Sam Tag
	////////////////////////////////////////////////////////////////////////////////////////////
	/*
	Sam pursues the nearest player
	If not caught, she will change behaviors
	If caught, Sam flees and waits for a player to catch her
	If Sam is caught, the pauses for a short time and changes behaviors
	If not caught, she throws a tantrum for a moment and erases board progress
	*/
	bool tag();
	void chase();
	void flee();
	void appear();
	void hide();
	void tantrum();
	void idle();


	////////////////////////////////////////////////////////////////////////////////////////////
	int getBehavior();
	bool timeCheck();
	void setAnim(std::string s) { animstate = s; }
	std::string getAnim() { return animstate; }
	void attachLevel(LevelManager* levelmanager);
	void lowerReactW(void);
	void incReactW(void);


	////////////////////////////////////////////////////////////////////////////////////////////
	//OBSOLETE
	/*
	void walkOn();
	void teleportOn();
	void candyOn();
	void pteraOn();
	void walkOff();
	void teleportOff();
	void candyOff();
	void pteraOff();
	*/
	////////////////////////////////////////////////////////////////////////////////////////////
	bool timer();


	////////////////////////////////////////////////////////////////////////////////////////////
	// Sam walking functions
	////////////////////////////////////////////////////////////////////////////////////////////

	//umbrella behavior
	//sam initially selects the closest target in view and runs after them
	//if sam loses sight of the player she will run to the last location
	//she saw them at and attempt to relocate them
	//if she can not locate the target, she will switch behaviors
	bool pursue();

	void follow();

	//sam moves 1 walkspeed towards the coordinates
	//accepts pixels
	void step(int x, int y);
	
	//returns a vector of tile coordinates to the destination at x y
	//accepts tile coordinates
	std::vector<std::pair<int, int>> generatePath(int x, int y);

	//accepts tile coordinates, not pixel coordinates
	bool isClear(int x, int y);

	//sam searches for a player in her line of sight
	//returns the id of the nearest seen player or -1 if none were seen
	//FIXME 
	// the formula to calculate line of sight is a slope aray that calculates every box it passes through
	// if every box it passes is clear then a line of sight is registered
	// however, this doesn't fit for slopes of 1 or -1 as they do not cross the side boxes ie.
	// --0100
	// --1000
	// 01--00
	// 10--00
	// where 0 is an empty square, - is a solid object, and 1 is line of sight, the slope directly slices between the corner
	// intersection walls because the floor and ceil functions used to determine the crossings at each coordinate
	// always return a single whole value on slopes of 1 and -1
	// ie with a slope of .5 at x = 3, .5 * x = 1.5, floor (1.5) = 1, ceil (1.5) = 2 and this gives the crossing tiles
	// slopes of 1 and -1 always return whole numbers so floor and ceil return the same value
	// for each, parallel rays need to be cast to either side and if either remains uninterrupted then vision is clear.
	// if both rays are blocked at any point, then there is no line of sight
	int search();

	// returns distance to visible player
	// returns -1 if there is no vision on the player
	int checkSight(int player);

	////////////////////////////////////////////////////////////////////////////////////////////////
	// Utility functions
	////////////////////////////////////////////////////////////////////////////////////////////////
	//takes a coordinate and returns the coordinates of the tile it is at
	Vec2 coordinateToTile(int x, int y);





	std::vector<ServerMessage> getServerMessage();
	bool sendMap();

	bool testingBehavior();
	void testPath();
	



private:
	
	//TypeDefs
	typedef bool (ServerSam::*FunctionPointer)(void);
	typedef void (ServerSam::*Phase)(void);

	//Function Pointers
	FunctionPointer current_behavior = &ServerSam::emptyBehavior;
	Phase current_phase;

	// Behavior vector and initial times
	/*
	1. Tag
	2. 
	*/
	//std::vector<FunctionPointer> behavior_list{ &ServerSam::tag };
	//testing vector
	std::vector<FunctionPointer> behavior_list{ &ServerSam::pursue };

	std::vector<int> behavior_timers{ 600 };


	// Map refresh
	bool send_map = false;

	// Data
	int target = 0;
	int behavior = 0;
	int behavior_timer = 0;
	bool initialize_behavior = true;

	// Behavior Timers
	float walk_speed = 2;
	int charge_speed = 4;
	int x = 0, y = 0;
	int candy_spawn_distance = 200;

	std::vector<Player*>* player_list;
	std::vector<int> distance;
	bool behavior_unlocked = true;
	int priority[4];
	bool flag = true;
	bool pteraphase = 0;

	//new vals for wait time before sam pursues candy
	int sam_candy_dist = 0;
	int player_candy_dist = 9999;
	int player_dist_check = 0;
	int reaction_time_weight = 10; //weight for player reaction time, default is avg human reaction time of 0.25s plus a little extra

	//statistics

	//how many times sam/player get candy
	int sam_candy_score = 0;
	int pl_candy_score = 0;


	//timers
	const int TAG_TIMER = 600;



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


	//pathing items
	struct PathNode  {
		int x = 0;
		int y = 0;
		float cost = 0;
		float step = 0;
		int index = 0;
		int parent_index = 0;

		PathNode::PathNode(int x, int y, float cost, float step, int index, int parent_index)
			: x{ x }, y{ y }, cost{ cost }, step{ step }, index{ index }, parent_index { parent_index }
		{}
	};

	std::vector<std::pair<int, int>> walk_path;

	Vec2 last_seen;

	//external items
	cocos2d::TMXLayer* blockage;
	LevelManager* lvm;

	//links
	Pterodactyl* ptera;
	Candy* candy;


	std::vector<ServerMessage> queued_messages;


	bool run_once = true;
	


	class NodePathCompare
	{
	public:
		bool operator()(int* n1, int* n2) {
			return *(n1+4)>*(n2+4);
		}
	};
	
};

#endif // _ServerSam_HPP_