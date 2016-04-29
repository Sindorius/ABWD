
#include "Villain.h"
#include <math.h>
#include <stdlib.h>
#include "cocos2d.h"
#include <iostream>

Villain* Villain::create(bool vis)
{
	Villain* pSprite = new Villain();

	if (pSprite->initWithFile("\\res\\sprites\\animations\\sam\\sam_walk_front0.png"))
	{
		pSprite->autorelease();

		pSprite->initialize(vis);

		return pSprite;
	}

	CC_SAFE_DELETE(pSprite);
	return NULL;
}

void Villain::initialize(bool vis)
{
	this->getTexture()->setAliasTexParameters();
	this->setAnchorPoint(Vec2(0.5, 0.0));
	this->setPosition(Vec2(-250, -150));
	this->setVisible(vis);
}

