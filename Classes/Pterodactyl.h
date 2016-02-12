#ifndef _PTERODACTYL_HPP_
#define _PTERODACTYL_HPP_

#include "cocos2d.h"
#include <array>
#include <stdlib.h>

class Pterodactyl : public cocos2d::Sprite 
{
public:
	Pterodactyl() {};
	~Pterodactyl() {};
	void run(int x, int y);
	void on() { running = true; }
	void off() { running = false; }
	bool isOn() { return running; }
	void attack() { hostile = true; cap = 5; }
	void peace() { hostile = false; cap = 3; }
	bool isHostile() { return hostile; }
	static Pterodactyl* create();
	void setAnim(std::string state) { animstate = state; }
	std::string getAnim() { return animstate; }


private:
	int posx;
	int posy;
	float Xvelocity = 0;
	float Yvelocity = 0;
	float acceleration = .1;
	std::string animstate = "";
	bool running = false;
	bool hostile = false;
	int cap = 5;
};

#endif //_PTERODACTYL_HPP_