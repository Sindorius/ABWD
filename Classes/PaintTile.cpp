#include "PaintTile.h"

PaintTile* PaintTile::create()
{
	PaintTile* pSprite = new PaintTile();

	if (pSprite->initWithFile("res//sprites//paint_overlay_dry.png"))
	{
		pSprite->setColor("clear");
		pSprite->autorelease();

		pSprite->getTexture()->setAliasTexParameters();
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
			pSprite->getTexture()->setAliasTexParameters();
			return pSprite;
		}
	}
	else if (color == "blue")
	{
		if (pSprite->initWithFile("res//sprites//objects//tile_correct_wet_blue1.png"))
		{
			pSprite->setColor("blue");

			pSprite->autorelease();

			pSprite->getTexture()->setAliasTexParameters();
			return pSprite;
		}
	}
	else if (color == "yellow")
	{
		if (pSprite->initWithFile("res//sprites//objects//tile_correct_wet_yellow1.png"))
		{
			pSprite->setColor("yellow");

			pSprite->autorelease();

			pSprite->getTexture()->setAliasTexParameters();
			return pSprite;
		}
	}
	else if (color == "orange")
	{
		if (pSprite->initWithFile("res//sprites//objects//tile_correct_wet_orange.png"))
		{
			pSprite->setColor("orange");

			pSprite->autorelease();

			pSprite->getTexture()->setAliasTexParameters();
			return pSprite;
		}
	}
	else if (color == "black")
	{
		if (pSprite->initWithFile("res//sprites//objects//tile_correct_wet_black.png"))
		{
			pSprite->setColor("black");

			pSprite->autorelease();

			pSprite->getTexture()->setAliasTexParameters();
			return pSprite;
		}
	}
	/// The Tera picture colors
	else if (color == "blue2")
	{
		if (pSprite->initWithFile("res//sprites//objects//tile_correct_wet_blue2.png"))
		{
			pSprite->setColor("blue2");

			pSprite->autorelease();

			pSprite->getTexture()->setAliasTexParameters();
			return pSprite;
		}
	}
	else if (color == "blue3")
	{
		if (pSprite->initWithFile("res//sprites//objects//tile_correct_wet_blue3.png"))
		{
			pSprite->setColor("blue3");

			pSprite->autorelease();

			pSprite->getTexture()->setAliasTexParameters();
			return pSprite;
		}
	}
	else if (color == "green1")
	{
		if (pSprite->initWithFile("res//sprites//objects//tile_correct_wet_green1.png"))
		{
			pSprite->setColor("green1");

			pSprite->autorelease();

			pSprite->getTexture()->setAliasTexParameters();
			return pSprite;
		}
	}
	else if (color == "green2")
	{
		if (pSprite->initWithFile("res//sprites//objects//tile_correct_wet_green2.png"))
		{
			pSprite->setColor("green2");

			pSprite->autorelease();

			pSprite->getTexture()->setAliasTexParameters();
			return pSprite;
		}
	}
	else if (color == "green3")
	{
		if (pSprite->initWithFile("res//sprites//objects//tile_correct_wet_green3.png"))
		{
			pSprite->setColor("green3");

			pSprite->autorelease();

			pSprite->getTexture()->setAliasTexParameters();
			return pSprite;
		}
	}
	/////////////////////////////
	////// THE SAM IMAGE COLORS
	else if (color == "grey1")
	{
		if (pSprite->initWithFile("res//sprites//objects//tile_correct_wet_grey1.png"))
		{
			pSprite->setColor("grey1");

			pSprite->autorelease();

			pSprite->getTexture()->setAliasTexParameters();
			return pSprite;
		}
	}
	else if (color == "grey2")
	{
		if (pSprite->initWithFile("res//sprites//objects//tile_correct_wet_grey2.png"))
		{
			pSprite->setColor("grey2");

			pSprite->autorelease();

			pSprite->getTexture()->setAliasTexParameters();
			return pSprite;
		}
	}
	else if (color == "white")
	{
		if (pSprite->initWithFile("res//sprites//objects//tile_correct_wet_white.png"))
		{
			pSprite->setColor("white");

			pSprite->autorelease();

			pSprite->getTexture()->setAliasTexParameters();
			return pSprite;
		}
	}
	else if (color == "red1")
	{
		if (pSprite->initWithFile("res//sprites//objects//tile_correct_wet_red1.png"))
		{
			pSprite->setColor("red1");

			pSprite->autorelease();

			pSprite->getTexture()->setAliasTexParameters();
			return pSprite;
		}
	}
	else if (color == "red2")
	{
		if (pSprite->initWithFile("res//sprites//objects//tile_correct_wet_red2.png"))
		{
			pSprite->setColor("red2");

			pSprite->autorelease();

			pSprite->getTexture()->setAliasTexParameters();
			return pSprite;
		}
	}
	else if (color == "purple1")
	{
		if (pSprite->initWithFile("res//sprites//objects//tile_correct_wet_purple1.png"))
		{
			pSprite->setColor("purple1");

			pSprite->autorelease();

			pSprite->getTexture()->setAliasTexParameters();
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

			pSprite->getTexture()->setAliasTexParameters();return pSprite;
		}
	}
	*/
	else if (color == "Xblue")
	{
		if (pSprite->initWithFile("res//sprites//objects//tile_incorrect_wet_blue1.png"))
		{
			pSprite->setColor("Xblue");

			pSprite->autorelease();

			pSprite->getTexture()->setAliasTexParameters();
			return pSprite;
		}
	}
	else if (color == "Xyellow")
	{
		if (pSprite->initWithFile("res//sprites//objects//tile_incorrect_wet_yellow1.png"))
		{
			pSprite->setColor("Xyellow");

			pSprite->autorelease();

			pSprite->getTexture()->setAliasTexParameters();
			return pSprite;
		}
	}
	else if (color == "Xorange")
	{
		if (pSprite->initWithFile("res//sprites//objects//tile_incorrect_wet_orange.png"))
		{
			pSprite->setColor("Xorange");

			pSprite->autorelease();

			pSprite->getTexture()->setAliasTexParameters();
			return pSprite;
		}
	}
	else if (color == "Xblack")
	{
		if (pSprite->initWithFile("res//sprites//objects//tile_incorrect_wet_black.png"))
		{
			pSprite->setColor("Xblack");

			pSprite->autorelease();

			pSprite->getTexture()->setAliasTexParameters();
			return pSprite;
		}
	}
	// The Tera picture colors
	else if (color == "Xblue2")
	{
		if (pSprite->initWithFile("res//sprites//objects//tile_incorrect_wet_blue2.png"))
		{
			pSprite->setColor("Xblue2");

			pSprite->autorelease();

			pSprite->getTexture()->setAliasTexParameters();
			return pSprite;
		}
	}
	else if (color == "Xblue3")
	{
		if (pSprite->initWithFile("res//sprites//objects//tile_incorrect_wet_blue3.png"))
		{
			pSprite->setColor("Xblue3");

			pSprite->autorelease();

			pSprite->getTexture()->setAliasTexParameters();
			return pSprite;
		}
	}
	else if (color == "Xgreen1")
	{
		if (pSprite->initWithFile("res//sprites//objects//tile_incorrect_wet_green1.png"))
		{
			pSprite->setColor("Xgreen1");

			pSprite->autorelease();

			pSprite->getTexture()->setAliasTexParameters();
			return pSprite;
		}
	}
	else if (color == "Xgreen2")
	{
		if (pSprite->initWithFile("res//sprites//objects//tile_incorrect_wet_green2.png"))
		{
			pSprite->setColor("Xgreen2");

			pSprite->autorelease();

			pSprite->getTexture()->setAliasTexParameters();
			return pSprite;
		}
	}
	else if (color == "Xgreen3")
	{
		if (pSprite->initWithFile("res//sprites//objects//tile_incorrect_wet_green3.png"))
		{
			pSprite->setColor("Xgreen3");

			pSprite->autorelease();

			pSprite->getTexture()->setAliasTexParameters();
			return pSprite;
		}
	}
	/////////////////////////////
	// SAMS INCORRECT TILE COLORS
	else if (color == "Xgrey1")
	{
		if (pSprite->initWithFile("res//sprites//objects//tile_incorrect_wet_grey1.png"))
		{
			pSprite->setColor("Xgrey1");

			pSprite->autorelease();

			pSprite->getTexture()->setAliasTexParameters();
			return pSprite;
		}
	}
	else if (color == "Xgrey2")
	{
		if (pSprite->initWithFile("res//sprites//objects//tile_incorrect_wet_grey2.png"))
		{
			pSprite->setColor("Xgrey2");

			pSprite->autorelease();

			pSprite->getTexture()->setAliasTexParameters();
			return pSprite;
		}
	}
	else if (color == "Xwhite")
	{
		if (pSprite->initWithFile("res//sprites//objects//tile_incorrect_wet_white.png"))
		{
			pSprite->setColor("Xwhite");

			pSprite->autorelease();

			pSprite->getTexture()->setAliasTexParameters();
			return pSprite;
		}
	}
	else if (color == "Xred1")
	{
		if (pSprite->initWithFile("res//sprites//objects//tile_incorrect_wet_red1.png"))
		{
			pSprite->setColor("Xred1");

			pSprite->autorelease();

			pSprite->getTexture()->setAliasTexParameters();
			return pSprite;
		}
	}
	else if (color == "Xred2")
	{
		if (pSprite->initWithFile("res//sprites//objects//tile_incorrect_wet_red2.png"))
		{
			pSprite->setColor("Xred2");

			pSprite->autorelease();

			pSprite->getTexture()->setAliasTexParameters();
			return pSprite;
		}
	}
	else if (color == "Xpurple1")
	{
		if (pSprite->initWithFile("res//sprites//objects//tile_incorrect_wet_purple1.png"))
		{
			pSprite->setColor("Xpurple1");

			pSprite->autorelease();

			pSprite->getTexture()->setAliasTexParameters();
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

			pSprite->getTexture()->setAliasTexParameters();
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
		if (isDry())
		{
			setTexture("res//sprites//objects//tile_correct_dry_red1.png");
		}
		else
		{
			setTexture("res//sprites//objects//tile_correct_wet_red1.png");
		}
	}
	else if (color == "blue")
	{
		if (isDry())
		{
			setTexture("res//sprites//objects//tile_correct_dry_blue1.png");
		}
		else
		{
			setTexture("res//sprites//objects//tile_correct_wet_blue1.png");
		}
	}

	else if (color == "yellow")
	{
		if (isDry())
		{
			setTexture("res//sprites//objects//tile_correct_dry_yellow1.png");
		}
		else
		{
			setTexture("res//sprites//objects//tile_correct_wet_yellow1.png");
		}
	}

	else if (color == "orange")
	{
		if (isDry())
		{
			setTexture("res//sprites//objects//tile_correct_dry_orange.png");
		}
		else
		{
			setTexture("res//sprites//objects//tile_correct_wet_orange.png");
		}
	}

	else if (color == "black")
	{
		if (isDry())
		{
			setTexture("res//sprites//objects//tile_correct_dry_black.png");
		}
		else
		{
			setTexture("res//sprites//objects//tile_correct_wet_black.png");
		}
	}
	///////////////////// NEW CODE ADDED
	else if (color == "blue2")
	{
		if (isDry())
		{
			setTexture("res//sprites//objects//tile_correct_dry_blue2.png");
		}
		else
		{
			setTexture("res//sprites//objects//tile_correct_wet_blue2.png");
		}
	}
	else if (color == "blue3")
	{
		if (isDry())
		{
			setTexture("res//sprites//objects//tile_correct_dry_blue3.png");
		}
		else
		{
			setTexture("res//sprites//objects//tile_correct_wet_blue3.png");
		}
	}
	else if (color == "green1")
	{
		if (isDry())
		{
			setTexture("res//sprites//objects//tile_correct_dry_green1.png");
		}
		else
		{
			setTexture("res//sprites//objects//tile_correct_wet_green1.png");
		}
	}
	else if (color == "green2")
	{
		if (isDry())
		{
			setTexture("res//sprites//objects//tile_correct_dry_green2.png");
		}
		else
		{
			setTexture("res//sprites//objects//tile_correct_wet_green2.png");
		}
	}
	else if (color == "green3")
	{
		if (isDry())
		{
			setTexture("res//sprites//objects//tile_correct_dry_green3.png");
		}
		else
		{
			setTexture("res//sprites//objects//tile_correct_wet_green3.png");
		}
	}
	else if (color == "grey1")
	{
		if (isDry())
		{
			setTexture("res//sprites//objects//tile_correct_dry_grey1.png");
		}
		else
		{
			setTexture("res//sprites//objects//tile_correct_wet_grey1.png");
		}
	}
	else if (color == "grey2")
	{
		if (isDry())
		{
			setTexture("res//sprites//objects//tile_correct_dry_grey2.png");
		}
		else
		{
			setTexture("res//sprites//objects//tile_correct_wet_grey2.png");
		}
	}
	else if (color == "white")
	{
		if (isDry())
		{
			setTexture("res//sprites//objects//tile_correct_dry_white.png");
		}
		else
		{
			setTexture("res//sprites//objects//tile_correct_wet_white.png");
		}
	}
	else if (color == "red1")
	{
		if (isDry())
		{
			setTexture("res//sprites//objects//tile_correct_dry_red1.png");
		}
		else
		{
			setTexture("res//sprites//objects//tile_correct_wet_red1.png");
		}
	}
	else if (color == "red2")
	{
		if (isDry())
		{
			setTexture("res//sprites//objects//tile_correct_dry_red2.png");
		}
		else
		{
			setTexture("res//sprites//objects//tile_correct_wet_red2.png");
		}
	}
	else if (color == "purple1")
	{
		if (isDry())
		{
			setTexture("res//sprites//objects//tile_correct_dry_purple1.png");
		}
		else
		{
			setTexture("res//sprites//objects//tile_correct_wet_purple1.png");
		}
	}
	////////////////////////////////////
	else if (color == "Xred")
	{
		if (isDry())
		{
			setTexture("res//sprites//objects//tile_incorrect_dry_red1.png");
		}
		else
		{
			setTexture("res//sprites//objects//tile_incorrect_wet_red1.png");
		}
	}

	else if (color == "Xblue")
	{
		if (isDry())
		{
			setTexture("res//sprites//objects//tile_incorrect_dry_blue1.png");
		}
		else
		{
			setTexture("res//sprites//objects//tile_incorrect_wet_blue1.png");
		}
	}

	else if (color == "Xyellow")
	{
		if (isDry())
		{
			setTexture("res//sprites//objects//tile_incorrect_dry_yellow1.png");
		}
		else
		{
			setTexture("res//sprites//objects//tile_incorrect_wet_yellow1.png");
		}
	}

	else if (color == "Xorange")
	{
		if (isDry())
		{
			setTexture("res//sprites//objects//tile_incorrect_dry_orange.png");
		}
		else
		{
			setTexture("res//sprites//objects//tile_incorrect_wet_orange.png");
		}
	}

	else if (color == "Xblack")
	{
		if (isDry())
		{
			setTexture("res//sprites//objects//tile_incorrect_dry_black.png");
		}
		else
		{
			setTexture("res//sprites//objects//tile_incorrect_wet_black.png");
		}
	}
	///////////////////// NEW CODE ADDED
	else if (color == "Xblue2")
	{
		if (isDry())
		{
			setTexture("res//sprites//objects//tile_incorrect_dry_blue2.png");
		}
		else
		{
			setTexture("res//sprites//objects//tile_incorrect_wet_blue2.png");
		}
	}
	else if (color == "Xblue3")
	{
		if (isDry())
		{
			setTexture("res//sprites//objects//tile_incorrect_dry_blue3.png");
		}
		else
		{
			setTexture("res//sprites//objects//tile_incorrect_wet_blue3.png");
		}
	}
	else if (color == "Xgreen1")
	{
		if (isDry())
		{
			setTexture("res//sprites//objects//tile_incorrect_dry_green1.png");
		}
		else
		{
			setTexture("res//sprites//objects//tile_incorrect_wet_green1.png");
		}
	}
	else if (color == "Xgreen2")
	{
		if (isDry())
		{
			setTexture("res//sprites//objects//tile_incorrect_dry_green2.png");
		}
		else
		{
			setTexture("res//sprites//objects//tile_incorrect_wet_green2.png");
		}
	}
	else if (color == "Xgreen3")
	{
		if (isDry())
		{
			setTexture("res//sprites//objects//tile_incorrect_dry_green3.png");
		}
		else
		{
			setTexture("res//sprites//objects//tile_incorrect_wet_green3.png");
		}
	}
	else if (color == "Xgrey1")
	{
		if (isDry())
		{
			setTexture("res//sprites//objects//tile_incorrect_dry_grey1.png");
		}
		else
		{
			setTexture("res//sprites//objects//tile_incorrect_wet_grey1.png");
		}
	}
	else if (color == "Xgrey2")
	{
		if (isDry())
		{
			setTexture("res//sprites//objects//tile_incorrect_dry_grey2.png");
		}
		else
		{
			setTexture("res//sprites//objects//tile_incorrect_wet_grey2.png");
		}
	}
	else if (color == "Xwhite")
	{
		if (isDry())
		{
			setTexture("res//sprites//objects//tile_incorrect_dry_white.png");
		}
		else
		{
			setTexture("res//sprites//objects//tile_incorrect_wet_white.png");
		}
	}
	else if (color == "Xred1")
	{
		if (isDry())
		{
			setTexture("res//sprites//objects//tile_incorrect_dry_red1.png");
		}
		else
		{
			setTexture("res//sprites//objects//tile_incorrect_wet_red1.png");
		}
	}
	else if (color == "Xred2")
	{
		if (isDry())
		{
			setTexture("res//sprites//objects//tile_incorrect_dry_red2.png");
		}
		else
		{
			setTexture("res//sprites//objects//tile_incorrect_wet_red2.png");
		}
	}
	else if (color == "Xpurple1")
	{
		if (isDry())
		{
			setTexture("res//sprites//objects//tile_incorrect_dry_purple1.png");
		}
		else
		{
			setTexture("res//sprites//objects//tile_incorrect_wet_purple1.png");
		}
	}
	////////////////////////////////////

	else if (color == "clear")
	{
		setTexture("res//sprites//paint_overlay_dry.png");
	}
	getTexture()->setAliasTexParameters();
}

