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
	
	boost::bimap<char, std::string> charstringmap;

	AnimationManager();
	char charFromString(std::string s)
	{
		return charstringmap.right.at(s);
	}
	std::string stringFromChar(char i)
	{
		return charstringmap.left.at(i);

	}
};