#pragma once

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include "cocos2d.h"
#include "PaintTile.h"
#include "Puzzle.hpp"

USING_NS_CC;

class LevelManager
{
public:
	int currentlevel = 0; //needed for loadlevel check
	Vec2 tilestartpoint;
	TMXTiledMap* levelmap;
	Puzzle puzzle;

	void setLevel(int level);
	bool isLastLevel(void) { return lastLevel; }

private:
	bool lastLevel = false;
};
