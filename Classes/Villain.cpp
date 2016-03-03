
#include "Villain.h"
#include <math.h>
#include <stdlib.h>
#include "cocos2d.h"
#include <iostream>

Villain* Villain::create()
{
	Villain* pSprite = new Villain();

	if (pSprite->initWithFile("\\res\\sprites\\animations\\sam\\sam_walk_front0.png"))
	{
		pSprite->autorelease();

		return pSprite;
	}

	CC_SAFE_DELETE(pSprite);
	return NULL;
}

