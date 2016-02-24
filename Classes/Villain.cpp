
#include "Villain.h"
#include <math.h>
#include <stdlib.h>
#include "cocos2d.h"
#include <iostream>

Villain* Villain::create()
{
	Villain* pSprite = new Villain();

	if (pSprite->initWithFile("\\res\\sprites\\animations\\sam\\sam_front_0.png"))
	{
		pSprite->autorelease();

		return pSprite;
	}

	CC_SAFE_DELETE(pSprite);
	return NULL;
}

void Villain::setPriority(std::vector<std::vector<char>> tiles) {
	for (int i = 0; i < 4; i++) {
		priority[i] = 0;
		idle = true;
		setAnim("samdown");
	}
	for (int i = 0; i < tiles.size(); i++) {
		for (int j = 0; j < tiles[i].size(); j++) {
			if (tiles[i][j] == 1) {
				priority[0]++;
				idle = false;
			}
			else if (tiles[i][j] == 2) {
				priority[1]++;
				idle = false;
			}
			else if (tiles[i][j] == 3) {
				priority[2]++;
				idle = false;
			}
			else if (tiles[i][j] == 4) {
				priority[3]++;
				idle = false;
			}
		}
	}
}

void Villain::runAI(std::vector<Player*>* players)
{

	player_list = players;
	calculations();
	teleport_cd--;
	candy->run();
	if (!(candy->active())) {
		candy->setOwner(-1);
	}
	if (behavior_unlocked) {
		chooseBehavior();
	}
	switch (behavior) {
	case 0:
		walk();
		break;
	case 1:
		pteraSummon();
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
	case 5:
		wait();
		break;
	case 6:

		munch();
		break;
	}
	if (behavior != 1) {
		ptera->run(this->getPositionX(), this->getPositionY());
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
	int choose;
	if (idle) {
		choose = 0;
	}
	else {
		choose = (rand() % 4) + 1;
	}
	switch (choose) {
	case 0:
		behavior_timer = idle_time;
		behavior = 5;
		break;
	case 1:
		behavior_timer = walk_time;
		behavior = 0;
		break;
		
	case 2:
		behavior_timer = 400;
		secondary_time = 30;
		behavior = 1;
		break;

	case 3:
		if (teleport_cd <= 0) {
			int total = priority[0] + priority[1] + priority[2] + priority[3];
			int guess = rand() % (total + 1);
			int guess1 = rand() % (total - priority[0] + 1);
			int guess2 = rand() % (total - priority[0] - priority[1] + 1);
			int guess3 = rand() % (total - priority[0] - priority[1] - priority[2] + 1);

			if (guess < priority[0]) {
				target = 0;
				x = player_list->at(target)->getPositionX();
				y = player_list->at(target)->getPositionY();
				behavior_timer = charge_teleport_time;
				behavior = 3;
			}
			else if (guess1 < priority[1]) {
				target = 1;
				x = player_list->at(target)->getPositionX();
				y = player_list->at(target)->getPositionY();
				behavior_timer = charge_teleport_time;
				behavior = 3;
			}
			else if (guess2 < priority[2]) {
				target = 2;
				x = player_list->at(target)->getPositionX();
				y = player_list->at(target)->getPositionY();
				behavior_timer = charge_teleport_time;
				behavior = 3;
			}
			else if (guess3 < priority[3]) {
				target = 3;
				x = player_list->at(target)->getPositionX();
				y = player_list->at(target)->getPositionY();
				behavior_timer = charge_teleport_time;
				behavior = 3;
			}
			else {
				behavior_timer = teleport_fail_timer;
				behavior = 0;
			}
		}
		break;

	case 4:
		behavior = 6;
		behavior_timer = 120;
		secondary_time = 30;
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
			else if (temp > temp1 && priority[i] > 0) { temp = temp1; target = i; }
		}
		double playerx, playery, samx, samy;
		playerx = player_list->at(target)->getPositionX();
		playery = player_list->at(target)->getPositionY();
		samx = this->getPositionX();
		samy = this->getPositionY();
		double theta;
		if (playerx >= samx) {
			theta = atan((playery - samy) / (playerx - samx)) * 180 / 3.14159;
		}
		else if (playery > samy){
			theta = 180 + (atan((playery - samy) / (playerx - samx)) * 180 / 3.14159);
		}
		else {
			theta = -180 + atan((playery - samy) / (playerx - samx)) * 180 / 3.14159;
		}
		if (priority[target] > 0) {
			
			this->setPositionX(this->getPositionX() + walk_speed*(cos(theta * 3.14159/180)));
			this->setPositionY(this->getPositionY() + walk_speed*(sin(theta * 3.14159/180)));
			
			if (theta > 45 && theta < 135) {
				setAnim("samup");
			}
			else if (theta >= 135 || theta <= -135) {
				setAnim("samleft");
			}
			else if (theta <= 45 && theta >= -45) {
				setAnim("samright");
			}
			else if (theta < -45 && theta > -135) {
				setAnim("samdown");
			}
			
		}
		else {
			behavior_timer = 0;
		}
	}
	else {
		behavior_unlocked = true;
		walk_speed = 2;
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
		
		behavior = 0;
		behavior_timer = 150;
		teleport_cd = 150;
	}
}

void Villain::chargeTeleport() {
	if (timeCheck()) {
		setAnim("samwarp");
		behavior_timer--;
	}
	else {
		setAnim("samappear");
		this->setPositionX(x);
		this->setPositionY(y);
		behavior_timer = teleport_arrival_time;
		behavior = 4;
	}
}

void Villain::wait() {
	if (timeCheck()) {
		behavior_timer--;
	}
	else {
		behavior_timer = 0;
		behavior_unlocked = true;
	}
}

void Villain::pteraSummon() {
	if (timeCheck()) {
		animstate = "samwhistle";
		if (secondary_time <= 0) {
			ptera->attack();
		}
		else {
			secondary_time--;
		}
		int temp = -1;
		for (int i = 0; i < distance.size(); i++) {
			int temp1 = distance[i];
			if (temp < temp1 && priority[i] > 0) { temp = temp1; target = i; }
		}
		ptera->run(player_list->at(target)->getPositionX(), player_list->at(target)->getPositionY());
		behavior_timer--;
	}
	else {
		behavior = 0;
		behavior_timer = 300;
		ptera->peace();
	}
}

void Villain::munch() {
	if (flag) {
		int temp = -1;
		for (int i = 0; i < distance.size(); i++) {
			int temp1 = distance[i];
			if (temp < temp1 && priority[i] > 0) { temp = temp1; target = i; }
		}
		flag = false;
		candy->setPosition(this->getPositionX() - (this->getPositionX() - player_list->at(target)->getPositionX()) / 2, this->getPositionY() - (this->getPositionY() - player_list->at(target)->getPositionY()) / 2);

	}

	double theta;
	if (candy->getPositionX() >= this->getPositionX()) {
		theta = atan((candy->getPositionY() - this->getPositionY()) / (candy->getPositionX() - this->getPositionX())) * 180 / 3.14159;
	}
	else if (candy->getPositionX() > this->getPositionY()) {
		theta = 180 + (atan((candy->getPositionY() - this->getPositionY()) / (candy->getPositionX() - this->getPositionX())) * 180 / 3.14159);
	}
	else {
		theta = -180 + atan((candy->getPositionY() - this->getPositionY()) / (candy->getPositionX() - this->getPositionX())) * 180 / 3.14159;
	}

	this->setPositionX(this->getPositionX() + walk_speed*(cos(theta * 3.14159 / 180)));
	this->setPositionY(this->getPositionY() + walk_speed*(sin(theta * 3.14159 / 180)));

	for (int i = 0; i < player_list->size(); i++) {
		if (abs(player_list->at(i)->getPositionX() - candy->getPositionX()) < 10 && abs(player_list->at(i)->getPositionY() - candy->getPositionY()) < 10 && candy->notCollected()) {
			candy->setStatus(false);
			candy->setOwner(target);
			candy->start();
			candy->setPosition(-1000, -1000);
			flag = true;
			behavior_unlocked = true;
		}
	}
	if (abs(this->getPositionX() - candy->getPositionX()) < 10 && abs(this->getPositionY() - candy->getPositionY()) < 10 && candy->notCollected()) {
		candy->setStatus(false);
		candy->setPosition(-1000, -1000);
		behavior = 0;
		behavior_timer = 150;
		flag = true;
		walk_speed = 2.5;
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

void Villain::linkPtera(Pterodactyl* pterodactyl) {
	ptera = pterodactyl;
	ptera->on();
}

void Villain::linkCandy(Candy* candies) {
	candy = candies;
}
