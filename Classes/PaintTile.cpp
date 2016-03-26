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
		if (pSprite->initWithFile("res//sprites//objects//tile_correct_wet_red1.png.png"))
		{
			pSprite->setColor("red");

			pSprite->autorelease();

			return pSprite;
		}
	}
	if (color == "blue")
	{
		if (pSprite->initWithFile("res//sprites//objects//tile_correct_wet_blue1.png"))
		{
			pSprite->setColor("blue");

			pSprite->autorelease();

			return pSprite;
		}
	}
	if (color == "yellow")
	{
		if (pSprite->initWithFile("res//sprites//objects//tile_correct_wet_yellow1.png"))
		{
			pSprite->setColor("yellow");

			pSprite->autorelease();

			return pSprite;
		}
	}
	if (color == "orange")
	{
		if (pSprite->initWithFile("res//sprites//objects//tile_correct_wet_orange.png"))
		{
			pSprite->setColor("orange");

			pSprite->autorelease();

			return pSprite;
		}
	}
	if (color == "black")
	{
		if (pSprite->initWithFile("res//sprites//objects//tile_correct_wet_black.png"))
		{
			pSprite->setColor("black");

			pSprite->autorelease();

			return pSprite;
		}
	}
	/// The Tera picture colors
	if (color == "blue2")
	{
		if (pSprite->initWithFile("res//sprites//objects//tile_correct_wet_blue2.png"))
		{
			pSprite->setColor("blue2");

			pSprite->autorelease();

			return pSprite;
		}
	}
	if (color == "blue3")
	{
		if (pSprite->initWithFile("res//sprites//objects//tile_correct_wet_blue3.png"))
		{
			pSprite->setColor("blue3");

			pSprite->autorelease();

			return pSprite;
		}
	}
	if (color == "green1")
	{
		if (pSprite->initWithFile("res//sprites//objects//tile_correct_wet_green1.png"))
		{
			pSprite->setColor("green1");

			pSprite->autorelease();

			return pSprite;
		}
	}
	if (color == "green2")
	{
		if (pSprite->initWithFile("res//sprites//objects//tile_correct_wet_green2.png"))
		{
			pSprite->setColor("green2");

			pSprite->autorelease();

			return pSprite;
		}
	}
	if (color == "green3")
	{
		if (pSprite->initWithFile("res//sprites//objects//tile_correct_wet_green3.png"))
		{
			pSprite->setColor("green3");

			pSprite->autorelease();

			return pSprite;
		}
	}
	/////////////////////////////
	////// THE SAM IMAGE COLORS
	if (color == "grey1")
	{
		if (pSprite->initWithFile("res//sprites//objects//tile_correct_wet_grey1.png"))
		{
			pSprite->setColor("grey1");

			pSprite->autorelease();

			return pSprite;
		}
	}
	if (color == "grey2")
	{
		if (pSprite->initWithFile("res//sprites//objects//tile_correct_wet_grey2.png"))
		{
			pSprite->setColor("grey2");

			pSprite->autorelease();

			return pSprite;
		}
	}
	if (color == "white")
	{
		if (pSprite->initWithFile("res//sprites//objects//tile_correct_wet_white.png"))
		{
			pSprite->setColor("white");

			pSprite->autorelease();

			return pSprite;
		}
	}
	if (color == "red1")
	{
		if (pSprite->initWithFile("res//sprites//objects//tile_correct_wet_red1.png"))
		{
			pSprite->setColor("red1");

			pSprite->autorelease();

			return pSprite;
		}
	}
	if (color == "red2")
	{
		if (pSprite->initWithFile("res//sprites//objects//tile_correct_wet_red2.png"))
		{
			pSprite->setColor("red2");

			pSprite->autorelease();

			return pSprite;
		}
	}
	if (color == "purple1")
	{
		if (pSprite->initWithFile("res//sprites//objects//tile_correct_wet_purple1.png"))
		{
			pSprite->setColor("purple1");

			pSprite->autorelease();

			return pSprite;
		}
	}
	/////////////////////////////
	/*

	if (color == "Xred")
	{
		if (pSprite->initWithFile("res//sprites//objects//tile_red_paint_incorrect.png"))
		{
			pSprite->setColor("Xred");

			pSprite->autorelease();

			return pSprite;
		}
	}
	*/
	if (color == "Xblue")
	{
		if (pSprite->initWithFile("res//sprites//objects//tile_incorrect_wet_blue1.png"))
		{
			pSprite->setColor("Xblue");

			pSprite->autorelease();

			return pSprite;
		}
	}
	if (color == "Xyellow")
	{
		if (pSprite->initWithFile("res//sprites//objects//tile_incorrect_wet_yellow1.png"))
		{
			pSprite->setColor("Xyellow");

			pSprite->autorelease();

			return pSprite;
		}
	}
	if (color == "Xorange")
	{
		if (pSprite->initWithFile("res//sprites//objects//tile_incorrect_wet_orange.png"))
		{
			pSprite->setColor("Xorange");

			pSprite->autorelease();

			return pSprite;
		}
	}
	if (color == "Xblack")
	{
		if (pSprite->initWithFile("res//sprites//objects//tile_incorrect_wet_black.png"))
		{
			pSprite->setColor("Xblack");

			pSprite->autorelease();

			return pSprite;
		}
	}
	// The Tera picture colors
	if (color == "Xblue2")
	{
		if (pSprite->initWithFile("res//sprites//objects//tile_incorrect_wet_blue2.png"))
		{
			pSprite->setColor("Xblue2");

			pSprite->autorelease();

			return pSprite;
		}
	}
	if (color == "Xblue3")
	{
		if (pSprite->initWithFile("res//sprites//objects//tile_incorrect_wet_blue3.png"))
		{
			pSprite->setColor("Xblue3");

			pSprite->autorelease();

			return pSprite;
		}
	}
	if (color == "Xgreen1")
	{
		if (pSprite->initWithFile("res//sprites//objects//tile_incorrect_wet_green1.png"))
		{
			pSprite->setColor("Xgreen1");

			pSprite->autorelease();

			return pSprite;
		}
	}
	if (color == "Xgreen2")
	{
		if (pSprite->initWithFile("res//sprites//objects//tile_incorrect_wet_green2.png"))
		{
			pSprite->setColor("Xgreen2");

			pSprite->autorelease();

			return pSprite;
		}
	}
	if (color == "Xgreen3")
	{
		if (pSprite->initWithFile("res//sprites//objects//tile_incorrect_wet_green3.png"))
		{
			pSprite->setColor("Xgreen3");

			pSprite->autorelease();

			return pSprite;
		}
	}
	/////////////////////////////
	// SAMS INCORRECT TILE COLORS
	if (color == "Xgrey1")
	{
		if (pSprite->initWithFile("res//sprites//objects//tile_incorrect_wet_grey1.png"))
		{
			pSprite->setColor("Xgrey1");

			pSprite->autorelease();

			return pSprite;
		}
	}
	if (color == "Xgrey2")
	{
		if (pSprite->initWithFile("res//sprites//objects//tile_incorrect_wet_grey2.png"))
		{
			pSprite->setColor("Xgrey2");

			pSprite->autorelease();

			return pSprite;
		}
	}
	if (color == "Xwhite")
	{
		if (pSprite->initWithFile("res//sprites//objects//tile_incorrect_wet_white.png"))
		{
			pSprite->setColor("Xwhite");

			pSprite->autorelease();

			return pSprite;
		}
	}
	if (color == "Xred1")
	{
		if (pSprite->initWithFile("res//sprites//objects//tile_incorrect_wet_red1.png"))
		{
			pSprite->setColor("Xred1");

			pSprite->autorelease();

			return pSprite;
		}
	}
	if (color == "Xred2")
	{
		if (pSprite->initWithFile("res//sprites//objects//tile_incorrect_wet_red2.png"))
		{
			pSprite->setColor("Xred2");

			pSprite->autorelease();

			return pSprite;
		}
	}
	if (color == "Xpurple1")
	{
		if (pSprite->initWithFile("res//sprites//objects//tile_incorrect_wet_purple1.png"))
		{
			pSprite->setColor("Xpurple1");

			pSprite->autorelease();

			return pSprite;
		}
	}
	////////////////////////
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
	if (color == "red")
	{
		setTexture("res//sprites//objects//tile_red_paint_correct.png");
	}
	if (color == "blue")
	{
		setTexture("res//sprites//objects//tile_correct_wet_blue1.png");
	}

	if (color == "yellow")
	{
		setTexture("res//sprites//objects//tile_correct_wet_yellow1.png");
	}

	if (color == "orange")
	{
		setTexture("res//sprites//objects//tile_correct_wet_orange.png");
	}

	if (color == "black")
	{
		setTexture("res//sprites//objects//tile_correct_wet_black.png");
	}
	///////////////////// NEW CODE ADDED
	if (color == "blue2")
	{
		setTexture("res//sprites//objects//tile_correct_wet_blue2.png");
	}
	if (color == "blue3")
	{
		setTexture("res//sprites//objects//tile_correct_wet_blue3.png");
	}
	if (color == "green1")
	{
		setTexture("res//sprites//objects//tile_correct_wet_green1.png");
	}
	if (color == "green2")
	{
		setTexture("res//sprites//objects//tile_correct_wet_green2.png");
	}
	if (color == "green3")
	{
		setTexture("res//sprites//objects//tile_correct_wet_green3.png");
	}
	if (color == "grey1")
	{
		setTexture("res//sprites//objects//tile_correct_wet_grey1.png");
	}
	if (color == "grey2")
	{
		setTexture("res//sprites//objects//tile_correct_wet_grey2.png");
	}
	if (color == "white")
	{
		setTexture("res//sprites//objects//tile_correct_wet_white.png");
	}
	if (color == "red1")
	{
		setTexture("res//sprites//objects//tile_correct_wet_red1.png");
	}
	if (color == "red2")
	{
		setTexture("res//sprites//objects//tile_correct_wet_red2.png");
	}
	if (color == "purple1")
	{
		setTexture("res//sprites//objects//tile_correct_wet_purple1.png");
	}
	////////////////////////////////////
	if (color == "Xred")
	{
		setTexture("res//sprites//objects//tile_red_paint_incorrect.png");
	}

	if (color == "Xblue")
	{
		setTexture("res//sprites//objects//tile_incorrect_wet_blue1.png");
	}

	if (color == "Xyellow")
	{
		setTexture("res//sprites//objects//tile_incorrect_wet_yellow1.png");
	}

	if (color == "Xorange")
	{
		setTexture("res//sprites//objects//tile_incorrect_wet_orange.png");
	}

	if (color == "Xblack")
	{
		setTexture("res//sprites//objects//tile_incorrect_wet_black.png");
	}
	///////////////////// NEW CODE ADDED
	if (color == "Xblue2")
	{
		setTexture("res//sprites//objects//tile_incorrect_wet_blue2.png");
	}
	if (color == "Xblue3")
	{
		setTexture("res//sprites//objects//tile_incorrect_wet_blue3.png");
	}
	if (color == "Xgreen1")
	{
		setTexture("res//sprites//objects//tile_incorrect_wet_green1.png");
	}
	if (color == "Xgreen2")
	{
		setTexture("res//sprites//objects//tile_incorrect_wet_green2.png");
	}
	if (color == "Xgreen3")
	{
		setTexture("res//sprites//objects//tile_incorrect_wet_green3.png");
	}
	if (color == "Xgrey1")
	{
		setTexture("res//sprites//objects//tile_incorrect_wet_grey1.png");
	}
	if (color == "Xgrey2")
	{
		setTexture("res//sprites//objects//tile_incorrect_wet_grey2.png");
	}
	if (color == "Xwhite")
	{
		setTexture("res//sprites//objects//tile_incorrect_wet_white.png");
	}
	if (color == "Xred1")
	{
		setTexture("res//sprites//objects//tile_incorrect_wet_red1.png");
	}
	if (color == "Xred2")
	{
		setTexture("res//sprites//objects//tile_incorrect_wet_red2.png");
	}
	if (color == "Xpurple1")
	{
		setTexture("res//sprites//objects//tile_incorrect_wet_purple1.png");
	}
	////////////////////////////////////

	if (color == "clear")
	{
		setTexture("res//sprites//paint_overlay_dry.png");
	}
}

