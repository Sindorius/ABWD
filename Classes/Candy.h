#ifndef _CANDY_HPP_
#define _CANDY_HPP_

#include <cocos2d.h>

USING_NS_CC;

class Candy : public cocos2d::Sprite {
public:
	Candy() {};
	~Candy() {};
	static Candy* create(bool vis = true);
	void initialize(bool vis = true);


	bool notCollected() { return not_collected; }
	void setStatus(bool collect) { not_collected = collect; }
	void run() { time--; }
	bool active() { return time > 0; }
	void setOwner(int target) { owner = target; }
	int getOwner() { return owner; }
	void start() { time = 150; }
	int getTime() { return time; }

private:
	bool not_collected = true;
	int time = 0;
	int owner = -1;

};



#endif //_CANDY_HPP_