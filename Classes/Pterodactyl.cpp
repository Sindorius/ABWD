#include "Pterodactyl.h"
#include "cocos2d.h"

Pterodactyl* Pterodactyl::create()
{
	Pterodactyl* pSprite = new Pterodactyl();
	if (pSprite->initWithFile("\\res\\sprites\\animations\\pteradactyl\\pteradactyl_left0.png"))
	{
		pSprite->autorelease();

		return pSprite;
	}

	CC_SAFE_DELETE(pSprite);
	return NULL;
}

void Pterodactyl::run(int x, int y) {

	
	if (this->getPositionX() > x && Xvelocity < cap) {
		Xvelocity += acceleration;
		if (isHostile()) {
			setAnim("pteraANGRYleft");
		}
		else {
			setAnim("pteraleft");
		}
	}
	else if (this->getPositionX() < x && Xvelocity > -cap) {
		Xvelocity -= acceleration;
		if (isHostile()) {
			setAnim("pteraANGRYright");
		}
		else {
			setAnim("pteraright");
		}
	}
	if (this->getPositionY() > y && Yvelocity < cap) {
		Yvelocity += acceleration;
	}
	else if (this->getPositionY() < y && Yvelocity > -cap) {
		Yvelocity -= acceleration;
	}

	this->setPositionX(this->getPositionX() - Xvelocity);
	this->setPositionY(this->getPositionY() - Yvelocity);

}