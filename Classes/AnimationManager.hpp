#pragma once

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include "cocos2d.h"

class AnimationManager
{
public:
	std::map<std::string, cocos2d::Animate*> animationmap;

	AnimationManager();
};