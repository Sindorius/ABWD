#pragma once

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include "cocos2d.h"
#include "AudioEngine.h"

USING_NS_CC;

class TransitionManager
{
public:
	int transition;
	std::vector<Sprite*> transitionSprite;
	void loadTransition(int level);
	bool timer_status();
	int start_timer = 0;
};