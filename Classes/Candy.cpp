#include "Candy.h"

Candy* Candy::create(bool vis)
{
	Candy* pSprite = new Candy();
	if (pSprite->initWithFile("\\res\\sprites\\objects\\candy.png"))
	{
		pSprite->autorelease();

		pSprite->initialize(vis);

		return pSprite;
	}



	CC_SAFE_DELETE(pSprite);
	return NULL;
}


void Candy::initialize(bool vis)
{
	this->getTexture()->setAliasTexParameters();
	this->setPosition(Vec2(-1000, -1000));
	this->setAnchorPoint(Vec2(0.5, 0.0));
	this->setVisible(vis);
}
