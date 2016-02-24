#include "Candy.h"

Candy* Candy::create()
{
	Candy* pSprite = new Candy();
	if (pSprite->initWithFile("\\res\\sprites\\objects\\candy.png"))
	{
		pSprite->autorelease();

		return pSprite;
	}



	CC_SAFE_DELETE(pSprite);
	return NULL;
}
