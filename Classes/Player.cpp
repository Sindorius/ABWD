#include "Player.h"

Player* Player::create()
{
	Player* pSprite = new Player();

	if (pSprite->initWithFile("\\res\\sprites\\animations\\main_characters\\char_red_walking_down0.png"))
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
		if (pSprite->initWithFile("\\res\\sprites\\animations\\main_characters\\char_red_walking_down0.png"))
		{
			pSprite->autorelease();
			return pSprite;
		}
	}
	else if (playernum == 2)
	{
		if (pSprite->initWithFile("\\res\\sprites\\animations\\main_characters\\char_blue_walking_down0.png"))
		{
			pSprite->autorelease();
			return pSprite;
		}
	}
	else if (playernum == 3)
	{
		if (pSprite->initWithFile("\\res\\sprites\\animations\\main_characters\\char_green_walking_down0.png"))
		{
			pSprite->autorelease();
			return pSprite;
		}
	}
	else if (playernum == 4)
	{
		if (pSprite->initWithFile("\\res\\sprites\\animations\\main_characters\\char_yellow_walking_down0.png"))
		{
			pSprite->autorelease();
			return pSprite;
		}
	}
	else

	CC_SAFE_DELETE(pSprite);
	return NULL;
}