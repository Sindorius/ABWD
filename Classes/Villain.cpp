#include "Villain.h"
#include "Player.h"

Villain* Villain::create()
{
	Villain* pSprite = new Villain();

	if (pSprite->initWithFile("res//villain.png"))
	{
		pSprite->autorelease();

		return pSprite;
	}

	CC_SAFE_DELETE(pSprite);
	return NULL;
}

void Villain::runAI(std::vector<Player*>* players)
{
	int testplayer1x = players->at(0)->getPositionX();

	if (this->getPositionX() > testplayer1x)
	{
		this->setPositionX(this->getPositionX() - 1);
	}
	else{
		this->setPositionX(this->getPositionX() + 1);
	}
}