#ifndef _PLAYER_HPP_
#define _PLAYER_HPP_

#include "cocos2d.h"

USING_NS_CC;

class Player : public cocos2d::Sprite
{

public:
	Player() {};
	~Player(){};
	static Player* create();
	static Player* create(int playernum, bool vis = true);

	void initialize(int playernum, bool vis = true);

	void addLabel(const std::string& string, const std::string& fontName, float fontSize,
		const Size& dimensions = Size::ZERO, TextHAlignment hAlignment = TextHAlignment::CENTER,
		TextVAlignment vAlignment = TextVAlignment::TOP);

	int getPlayernum(){ return playernumber; };
	void setPlayernum(int playernum){ playernumber = playernum; };
	void setColor(std::string c) { color = c; }
	std::string getColor() { return color; }
	void setAnim(std::string s) { animstate = s; }
	std::string getAnim() { return animstate; }
	void setSpeed(int s) { speed = s; }
	int getSpeed(void) { return speed; }
	Label* getLabel(void) { return pLabel; }

	int speedboost = 1;
	//std::vector<Vec2> paintedTiles; //coords of all player's painted tiles
	std::vector<std::pair<int, int>> paintedTiles;

private:

	int playernumber = 0;
	int speed = 2;

	Label* pLabel;

	std::string color = "";
	std::string animstate = "";
};


#endif // _PLAYER_HPP_
