#include "PaintTile.h"

PaintTile* PaintTile::create()
{
	PaintTile* pSprite = new PaintTile();

	if (pSprite->initWithFile("res//sprites//paint_overlay_dry.png"))
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
		if (pSprite->initWithFile("res//sprites//objects//tile_red_paint_correct.png"))
		{
			pSprite->setColor("red");

			pSprite->autorelease();

			return pSprite;
		}
	}
	if (color == "blue")
	{
		if (pSprite->initWithFile("res//sprites//objects//tile_blue1_paint_correct.png"))
		{
			pSprite->setColor("blue");

			pSprite->autorelease();

			return pSprite;
		}
	}
	if (color == "yellow")
	{
		if (pSprite->initWithFile("res//sprites//objects//tile_yellow1_paint_correct.png"))
		{
			pSprite->setColor("yellow");

			pSprite->autorelease();

			return pSprite;
		}
	}
	if (color == "orange")
	{
		if (pSprite->initWithFile("res//sprites//objects//tile_orange_paint_correct.png"))
		{
			pSprite->setColor("orange");

			pSprite->autorelease();

			return pSprite;
		}
	}
	if (color == "black")
	{
		if (pSprite->initWithFile("res//sprites//objects//tile_black_paint_correct.png"))
		{
			pSprite->setColor("black");

			pSprite->autorelease();

			return pSprite;
		}
	}
	if (color == "Xred")
	{
		if (pSprite->initWithFile("res//sprites//objects//tile_red_paint_incorrect.png"))
		{
			pSprite->setColor("Xred");

			pSprite->autorelease();

			return pSprite;
		}
	}
	if (color == "Xblue")
	{
		if (pSprite->initWithFile("res//sprites//objects//tile_blue1_paint_incorrect.png"))
		{
			pSprite->setColor("Xblue");

			pSprite->autorelease();

			return pSprite;
		}
	}
	if (color == "Xyellow")
	{
		if (pSprite->initWithFile("res//sprites//objects//tile_yellow1_paint_incorrect.png"))
		{
			pSprite->setColor("Xyellow");

			pSprite->autorelease();

			return pSprite;
		}
	}
	if (color == "Xorange")
	{
		if (pSprite->initWithFile("res//sprites//objects//tile_orange_paint_incorrect.png"))
		{
			pSprite->setColor("Xorange");

			pSprite->autorelease();

			return pSprite;
		}
	}
	if (color == "Xblack")
	{
		if (pSprite->initWithFile("res//sprites//objects//tile_black_paint_incorrect.png"))
		{
			pSprite->setColor("Xblack");

			pSprite->autorelease();

			return pSprite;
		}
	}
	else
	{
		if (pSprite->initWithFile("res//sprites//paint_overlay_dry.png"))
		{
			pSprite->setColor("clear");

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
		setTexture("res//sprites//objects//tile_red_paint_correct.png");
	}
	if (color == "blue")
	{
		setTexture("res//sprites//objects//tile_blue1_paint_correct.png");
	}

	if (color == "yellow")
	{
		setTexture("res//sprites//objects//tile_yellow1_paint_correct.png");
	}

	if (color == "orange")
	{
		setTexture("res//sprites//objects//tile_orange_paint_correct.png");
	}

	if (color == "black")
	{
		setTexture("res//sprites//objects//tile_black_paint_correct.png");
	}

	if (color == "Xred")
	{
		setTexture("res//sprites//objects//tile_red_paint_incorrect.png");
	}

	if (color == "Xblue")
	{
		setTexture("res//sprites//objects//tile_blue1_paint_incorrect.png");
	}

	if (color == "Xyellow")
	{
		setTexture("res//sprites//objects//tile_yellow1_paint_incorrect.png");
	}

	if (color == "Xorange")
	{
		setTexture("res//sprites//objects//tile_orange_paint_incorrect.png");
	}

	if (color == "Xblack")
	{
		setTexture("res//sprites//objects//tile_black_paint_incorrect.png");
	}

	if (color == "clear")
	{
		setTexture("res//sprites//paint_overlay_dry.png");
	}
}

