#pragma once

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include "cocos2d.h"
#include "Puzzle.hpp"

USING_NS_CC;

class LevelManager
{
public:
	int level;
	cocos2d::Vec2 tilestartpoint;
	CCTMXTiledMap* levelmap;
	std::vector<Sprite*> levelsprites;
	Puzzle puzzle;

	void changeLevel(int level);

};
