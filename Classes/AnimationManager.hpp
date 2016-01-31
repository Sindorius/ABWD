#pragma once

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include "cocos2d.h"
#include <boost/bimap.hpp>

class AnimationManager
{
public:
	std::map<std::string, cocos2d::Animate*> animationmap;
	
	boost::bimap<int, std::string> intstringmap;

	AnimationManager();
	int intFromString(std::string s)
	{
		return intstringmap.right.at(s);
	}
	std::string stringFromInt(int i)
	{
		return intstringmap.left.at(i);

	}
};