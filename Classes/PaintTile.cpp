#include "PaintTile.h"

PaintTile* PaintTile::create()
{
	PaintTile* pSprite = new PaintTile();

	if (pSprite->initWithFile("res//sprites//paint_r.png"))
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
		if (pSprite->initWithFile("res//sprites//paint_r.png"))
		{
			pSprite->setColor("red");

			pSprite->autorelease();

			return pSprite;
		}
	}
	if (color == "blue")
	{
		if (pSprite->initWithFile("res//sprites//paint_b.png"))
		{
			pSprite->setColor("blue");

			pSprite->autorelease();

			return pSprite;
		}
	}
	if (color == "yellow")
	{
		if (pSprite->initWithFile("res//sprites//paint_y.png"))
		{
			pSprite->setColor("yellow");

			pSprite->autorelease();

			return pSprite;
		}
	}
	if (color == "orange")
	{
		if (pSprite->initWithFile("res//sprites//paint_o.png"))
		{
			pSprite->setColor("orange");

			pSprite->autorelease();

			return pSprite;
		}
	}
	else
	{
		if (pSprite->initWithFile("res//sprites//paint_r.png"))
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
		setTexture("res//sprites//paint_r.png");
	}
	if (color == "blue")
	{
		setTexture("res//sprites//paint_b.png");
	}

	if (color == "yellow")
	{
		setTexture("res//sprites//paint_y.png");
	}

	if (color == "orange")
	{
		setTexture("res//sprites//paint_o.png");
	}

	if (color == "black")
	{
		setTexture("res//sprites//paint_overlay_dry.png");
	}



}