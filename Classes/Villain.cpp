#include "Villain.h"
#include "Player.h"
#include <math.h>

Villain* Villain::create()
{
	Villain* pSprite = new Villain();

	if (pSprite->initWithFile("res//villain.png"))
	{
		pSprite->autorelease();

		return pSprite;
	}

	CC_SAFE_DELETE(pSprite);
	return NULL;
}

void Villain::runAI(std::vector<Player*>* players)
{
	std::vector<int> distance;
	int villainX = this->getPositionX();
	int villainY = this->getPositionY();
	for (int i = 0; i < players->size(); i++) {
		int temp = sqrt(pow((villainX - players->at(i)->getPositionX()), 2) + pow((villainY - players->at(i)->getPositionY()), 2));
		distance.push_back(temp);
	}
	switch (behavior) {
	case(0) :
		int temp = -1;
		for (int i = 0; i < distance.size(); i++) {
			int temp1 = distance[i];
			if (temp == -1) { temp = temp1; target = i; }
			else if (temp > temp1) { temp = temp1; target = i; }

		}

		if (this->getPositionX() > players->at(target)->getPositionX())
		{
			this->setPositionX(this->getPositionX() - 1);
		}
		else if (this->getPositionX() < players->at(target)->getPositionX()) {
			this->setPositionX(this->getPositionX() + 1);
		}
		if (this->getPositionY() > players->at(target)->getPositionY())
		{
			this->setPositionY(this->getPositionY() - 1);
		}
		else if (this->getPositionY() < players->at(target)->getPositionY()) {
			this->setPositionY(this->getPositionY() + 1);
		}
	}


}

int Villain::getTarget() {
	return target;
}

int Villain::getBehavior() {
	return behavior;
}