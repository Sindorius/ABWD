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

Player* Player::create(int playernum, bool vis)
{
	Player* pSprite = new (std::nothrow) Player();

	if (playernum == 1)
	{
		if (pSprite->initWithFile("\\res\\sprites\\animations\\main_characters\\char_red_walking_down0.png"))
		{
			pSprite->autorelease();

			pSprite->initialize(playernum, vis);

			return pSprite;
		}
	}
	else if (playernum == 2)
	{
		if (pSprite->initWithFile("\\res\\sprites\\animations\\main_characters\\char_blue_walking_down0.png"))
		{
			pSprite->autorelease();

			pSprite->initialize(playernum, vis);

			return pSprite;
		}
	}
	else if (playernum == 3)
	{
		if (pSprite->initWithFile("\\res\\sprites\\animations\\main_characters\\char_green_walking_down0.png"))
		{
			pSprite->autorelease();

			pSprite->initialize(playernum, vis);

			return pSprite;
		}
	}
	else if (playernum == 4)
	{
		if (pSprite->initWithFile("\\res\\sprites\\animations\\main_characters\\char_yellow_walking_down0.png"))
		{
			pSprite->autorelease();

			pSprite->initialize(playernum, vis);

			return pSprite;
		}
	}
	else
	{
		CC_SAFE_DELETE(pSprite);
		return NULL;
	}
}

void Player::initialize(int playernum, bool vis)
{
	this->setPlayernum(playernum);
	std::string str = "P" + std::to_string(playernum);
	this->addLabel(str, "fonts/arial.ttf", 9);
	this->getTexture()->setAliasTexParameters();
	this->setAnchorPoint(Vec2(0.5, 0.0));
	this->setVisible(vis);
}

void Player::addLabel(const std::string& string, const std::string& fontName, float fontSize,
	const Size& dimensions, TextHAlignment hAlignment,
	TextVAlignment vAlignment)
{
	pLabel = Label::createWithTTF(string, fontName, fontSize, dimensions, hAlignment, vAlignment);
	pLabel->enableOutline(Color4B::WHITE);
	pLabel->enableShadow(Color4B::BLACK, Size(1, 0), 50.0);
	pLabel->setPosition(Vec2(this->getPositionX() + 14, this->getPositionY() + 55));
	pLabel->setOpacity(0);

	this->addChild(pLabel, 100);
}