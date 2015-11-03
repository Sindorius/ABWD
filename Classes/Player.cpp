#include "Player.h"

Player* Player::create()
{
	Player* pSprite = new Player();

	if (pSprite->initWithFile("res//man1_0.png"))
	{
		pSprite->autorelease();

		return pSprite;
	}

	CC_SAFE_DELETE(pSprite);
	return NULL;
}