#ifndef _PAINTTILE_HPP_
#define _PAINTTILE_HPP_

#include "cocos2d.h"

class PaintTile : public cocos2d::CCSprite
{
public:
	PaintTile() {};
	~PaintTile() {};
	static PaintTile* create();
	static PaintTile* create(std::string color);
	void setColor(std::string c) { color = c; }
	std::string getColor() { return color; }
	bool isDry() { return dry; }
	void setDry(bool b) { dry = b; }
	void refreshColor();

private:
	std::string color;
	bool dry = false;
};


#endif // _PAINTTILE_HPP_