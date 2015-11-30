#include "PaintTile.h"

PaintTile* PaintTile::create()
{
	PaintTile* pSprite = new PaintTile();

	if (pSprite->initWithFile("res//maps//newroom//Red.png"))
	{
		pSprite->setColor("clear");
		pSprite->autorelease();

		return pSprite;
	}

	CC_SAFE_DELETE(pSprite);
	return NULL;
}

PaintTile* PaintTile::create(std::string color)
{
	PaintTile* pSprite = new PaintTile();
	if (color == "red")
	{
		if (pSprite->initWithFile("res//maps//newroom//Red.png"))
		{
			pSprite->setColor("red");

			pSprite->autorelease();

			return pSprite;
		}
	}
	if (color == "blue")
	{
		if (pSprite->initWithFile("res//maps//newroom//Blue.png"))
		{
			pSprite->setColor("blue");

			pSprite->autorelease();

			return pSprite;
		}
	}
	if (color == "yellow")
	{
		if (pSprite->initWithFile("res//maps//newroom//Yellow.png"))
		{
			pSprite->setColor("yellow");

			pSprite->autorelease();

			return pSprite;
		}
	}
	if (color == "orange")
	{
		if (pSprite->initWithFile("res//maps//newroom//Orange.png"))
		{
			pSprite->setColor("orange");

			pSprite->autorelease();

			return pSprite;
		}
	}
	else
	{
		if (pSprite->initWithFile("res//maps//newroom//Red.png"))
		{
			pSprite->setColor("red");

			pSprite->autorelease();

			return pSprite;
		}

	}

	CC_SAFE_DELETE(pSprite);
	return NULL;
}

void PaintTile::refreshColor()
{
	if(color == "red")
	{
		setTexture("res//maps//newroom//Red.png");
	}
	if (color == "blue")
	{
		setTexture("res//maps//newroom//Blue.png");
	}

	if (color == "yellow")
	{
		setTexture("res//maps//newroom//Yellow.png");
	}

	if (color == "orange")
	{
		setTexture("res//maps//newroom//Orange.png");
	}



}