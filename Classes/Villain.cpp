
#include "Villain.h"
#include "Player.h"
#include <math.h>
#include <stdlib.h>
#include "cocos2d.h"
#include <iostream>

Villain* Villain::create()
{
	Villain* pSprite = new Villain();

	if (pSprite->initWithFile("sprites//animations//sam_front_0.png"))
	{
		pSprite->autorelease();

		return pSprite;
	}

	CC_SAFE_DELETE(pSprite);
	return NULL;
}

void Villain::setPriority(std::array<std::array<int, 6>, 6> tiles) {
	priority1 = 0;
	priority2 = 0;
	priority3 = 0;
	priority4 = 0;
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 6; j++) {
			if (tiles[i][j] == 1) {
				priority1++;
			}
			else if (tiles[i][j] == 2) {
				priority2++;
			}
			else if (tiles[i][j] == 3) {
				priority3++;
			}
			else if (tiles[i][j] == 4) {
				priority4++;
			}
		}
	}
}

void Villain::runAI(std::vector<Player*>* players)
{
	std::cout << target << std::endl;
	player_list = players;
	calculations();
	teleport_cd--;
	if (behavior_unlocked) {
		chooseBehavior();
	}

	switch (behavior) {
	case 0:
		walk();
		break;
	case 1:
		chargeCharge();
		break;
	case 2:
		charge();
		break;
	case 3:
		chargeTeleport();
		break;
	case 4:
		teleport();
		break;

	}

}

void Villain::calculations() {
	distance.erase(distance.begin(), distance.end());
	int villainX = this->getPositionX();
	int villainY = this->getPositionY();
	for (int i = 0; i < player_list->size(); i++) {
		int temp = sqrt(pow((villainX - player_list->at(i)->getPositionX()), 2) + pow((villainY - player_list->at(i)->getPositionY()), 2));
		distance.push_back(temp);
	}
}


void Villain::chooseBehavior() {
	int choose = rand() % 3;
	switch (choose) {
	case 0:
		behavior_timer = 200;
		behavior = 0;
		break;
		/*
		case 1:
		behavior_timer = 30;
		behavior = 1;
		break;*/
	case 2:
		if (teleport_cd <= 0) {
			int player;
			//target = rand() % player_list->size();
			player = rand() % (priority1 + priority2 + priority3 + priority4 + 1);
			if (player < priority1) {
				target = 0;
			}
			else if (player < (priority1 + priority2)) {
				target = 1;
			}
			else if (player < (priority1 + priority2 + priority3)) {
				target = 2;
			}
			else if (player < (priority1 + priority2 + priority3 + priority4)) {
				target = 3;
			}
			x = player_list->at(target)->getPositionX();
			y = player_list->at(target)->getPositionY();
			behavior_timer = 80;
			behavior = 3;
		}
		break;
	}
	behavior_unlocked = false;
}


void Villain::walk() {
	if (timeCheck()) {
		behavior_timer--;
		int temp = -1;
		for (int i = 0; i < distance.size(); i++) {
			int temp1 = distance[i];
			if (temp == -1) { temp = temp1; target = i; }
			else if (temp > temp1) { temp = temp1; target = i; }
		}


		if (this->getPositionX() > player_list->at(target)->getPositionX())
		{
			this->setPositionX(this->getPositionX() - walk_speed);
		}
		else if (this->getPositionX() < player_list->at(target)->getPositionX()) {
			this->setPositionX(this->getPositionX() + walk_speed);
		}
		if (this->getPositionY() > player_list->at(target)->getPositionY())
		{
			this->setPositionY(this->getPositionY() - walk_speed);
		}
		else if (this->getPositionY() < player_list->at(target)->getPositionY()) {
			this->setPositionY(this->getPositionY() + walk_speed);
		}
	}
	else {
		behavior_unlocked = true;
	}
}


void Villain::charge() {
	if (timeCheck()) {
		behavior_timer--;
	}
	else {
		behavior_unlocked = true;
	}
}


void Villain::chargeCharge() {
	if (timeCheck()) {
		behavior_timer--;
	}
	else {
		behavior = 2;
		behavior_timer = 300;
	}
}


void Villain::teleport() {
	if (timeCheck()) {
		behavior_timer--;
	}
	else {
		this->setPositionX(x);
		this->setPositionY(y);
		behavior_unlocked = true;
		teleport_cd = 150;
	}
}

void Villain::chargeTeleport() {
	if (timeCheck()) {
		behavior_timer--;
	}
	else {
		behavior_timer = 1;
		behavior = 4;
	}
}

int Villain::getTarget() {
	return target;
}

int Villain::getBehavior() {
	return behavior;
}

bool Villain::timeCheck() {
	return behavior_timer > 0;
}