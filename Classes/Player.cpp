#include "Player.h"

Player* Player::create()
{
	Player* pSprite = new Player();

	if (pSprite->initWithFile("sprites//animations//char_red_front_0.png"))
	{
		pSprite->autorelease();
		return pSprite;
	}

	CC_SAFE_DELETE(pSprite);
	return NULL;
}

Player* Player::create(int playernum)
{
	Player* pSprite = new Player();

	if (playernum == 1)
	{
		if (pSprite->initWithFile("sprites//animations//char_red_front_0.png"))
		{
			pSprite->autorelease();
			return pSprite;
		}
	}
	else if (playernum == 2)
	{
		if (pSprite->initWithFile("sprites//animations//char_blue_front_0.png"))
		{
			pSprite->autorelease();
			return pSprite;
		}
	}
	else if (playernum == 3)
	{
		if (pSprite->initWithFile("sprites//animations//char_green_front_0.png"))
		{
			pSprite->autorelease();
			return pSprite;
		}
	}
	else if (playernum == 4)
	{
		if (pSprite->initWithFile("sprites//animations//char_yellow_front_0.png"))
		{
			pSprite->autorelease();
			return pSprite;
		}
	}
	else

	CC_SAFE_DELETE(pSprite);
	return NULL;
}