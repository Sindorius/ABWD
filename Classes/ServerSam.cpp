
#include "ServerSam.h"
#include <math.h>
#include <stdlib.h>
#include "cocos2d.h"
#include <iostream>
#include <random>
#include <time.h>


ServerSam::ServerSam(std::vector<Player*>* players)
	:player_list(players)
{
}

ServerSam* ServerSam::create(std::vector<Player*>* players, bool vis)
{
	ServerSam* pSprite = new ServerSam(players);
	if (pSprite->initWithFile("\\res\\sprites\\animations\\sam\\sam_walk_front0.png"))
	{
		pSprite->autorelease();

		pSprite->initialize(vis);

		return pSprite;
	}

	CC_SAFE_DELETE(pSprite);
	return NULL;
}

void ServerSam::initialize(bool vis)
{
	this->getTexture()->setAliasTexParameters();
	this->setPosition(Vec2(-250, -150));
	this->setAnchorPoint(Vec2(0.5, 0.0));
	this->setVisible(vis);
}


void ServerSam::setPriority(std::vector<std::vector<char>> tiles, std::vector<std::vector<char>> dry, int time) {

}

void ServerSam::runAI()
{
	send_map = false;
	queued_messages.clear();
	current_behavior = behavior_list[0];
	if ((this->*current_behavior)()) {}
	else {
		std::default_random_engine generator;
		std::uniform_int_distribution<int> distribution(0, behavior_list.size() - 1);
		int selection = distribution(generator);
		current_behavior = behavior_list[selection];
		behavior_timer = behavior_timers[selection];
	}
}

void ServerSam::calculations() {
	distance.erase(distance.begin(), distance.end());
	int ServerSamX = this->getPositionX();
	int ServerSamY = this->getPositionY();
	for (unsigned int i = 0; i < player_list->size(); i++) {
		if (player_list->at(i)->isVisible()) {
			int temp = sqrt(pow((ServerSamX - player_list->at(i)->getPositionX()), 2) + pow((ServerSamY - player_list->at(i)->getPositionY()), 2));
			distance.push_back(temp);
		}
		else {
			distance.push_back(20000);
		}
	}
}


void ServerSam::chooseBehavior() {

}


void ServerSam::walk() {
	if (timeCheck()) {
		behavior_timer--;
		int temp = -1;
		bool anything = false;
		for (unsigned int i = 0; i < distance.size(); i++) {
			int temp1 = distance[i];
			if (temp == -1 && priority[i] > 0) { 
				temp = temp1; 
				target = i; 
				anything = true;
			}
			else if (temp > temp1 && priority[i] > 0) { 
				temp = temp1; 
				target = i; 
			}
		}
		if (anything) {
			double playerx, playery, samx, samy;
			playerx = player_list->at(target)->getPositionX();
			playery = player_list->at(target)->getPositionY();
			samx = this->getPositionX();
			samy = this->getPositionY();
			double theta;
			if (playerx >= samx) {
				theta = atan((playery - samy) / (playerx - samx)) * 180 / 3.14159;
			}
			else if (playery > samy) {
				theta = 180 + (atan((playery - samy) / (playerx - samx)) * 180 / 3.14159);
			}
			else {
				theta = -180 + atan((playery - samy) / (playerx - samx)) * 180 / 3.14159;
			}
			if (priority[target] > 0 && distance[target] > 2) {

				this->setPositionX(this->getPositionX() + walk_speed*(cos(theta * 3.14159 / 180)));
				this->setPositionY(this->getPositionY() + walk_speed*(sin(theta * 3.14159 / 180)));

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

		}

	}

}





int ServerSam::getTarget() {
	return target;
}

bool ServerSam::tag()
{
	
	if (tag_phase == 0) {
		chase();
	}
	else if (tag_phase == 1) {
		flee();
	}
	else if (tag_phase == 2) {
		appear();
	}
	else if (tag_phase == 3) {
		hide();
	}
	else if (tag_phase == 4) {
		tantrum();
	}
	else if (tag_phase == 5) {
		idle();
	}

	return timer();
}

void ServerSam::chase()
{
	calculations();
	behavior_timer--;
	int temp = -1;
	for (unsigned int i = 0; i < distance.size(); i++) {
		int temp1 = distance[i];
		if (temp == -1) {
			temp = temp1;
			target = i;
		}
		else if (temp > temp1) {
			temp = temp1;
			target = i;
		}
	}
	double playerx = player_list->at(target)->getPositionX();
	double playery = player_list->at(target)->getPositionY();

	step(playerx, playery);
	if (abs(this->getPositionX() - playerx) < 5 && abs(this->getPositionY() - playery) < 5)
	{
		tag_phase = 1;
		behavior_timer = 60;
	}
}

void ServerSam::flee()
{
	behavior_timer--;
	if (behavior_timer > 0) {
		setAnim("samwarp");
	}
	else {
		this->setPositionX(50);
		this->setPositionY(50);
		tag_phase = 2;
		behavior_timer = 60;
	}
}

void ServerSam::appear()
{
	behavior_timer--;
	if (behavior_timer > 0) {
		setAnim("samappear");
	}
	else {
		tag_phase = 3;
		behavior_timer = 210;
	}
}

void ServerSam::hide()
{
	behavior_timer--;
	setAnim("samleft");
	double playerx = player_list->at(target)->getPositionX();
	double playery = player_list->at(target)->getPositionY();
	if (abs(this->getPositionX() - playerx) < 5 && abs(this->getPositionY() - playery) < 5)
	{
		tag_phase = 5;
		behavior_timer = 60;
	}
	else if (behavior_timer == 0) {
		tag_phase = 4;
		behavior_timer = 60;
	}
}

void ServerSam::tantrum()
{
	behavior_timer--;
	if (behavior_timer > 0) {
		setAnim("samright");
	}
	else {
		tag_phase = 0;
		int erase = lvm->puzzle.getTotalTiles() / 5;
		srand(time(NULL));
		std::default_random_engine generator;
		std::uniform_int_distribution<int> distribution(0, lvm->puzzle.currenttilevector.size() - 1);
		std::uniform_int_distribution<int> distribution1(0, lvm->puzzle.currenttilevector[0].size() - 1);
		for (int i = 0; i < erase; i++) {

			int selectionx = rand() % lvm->puzzle.currenttilevector.size();
			int selectiony = rand() % lvm->puzzle.currenttilevector[0].size();
			if (lvm->puzzle.checkTile(selectionx, selectiony))
			{
				lvm->puzzle.tileErased();
			}
			lvm->puzzle.currenttilevector[selectionx][selectiony] = 1;
			lvm->puzzle.tilespritevector[selectionx][selectiony]->setColor("clear");
			lvm->puzzle.tilespritevector[selectionx][selectiony]->refreshColor();
		}
		queued_messages.emplace_back(ServerMessage(13, 0, 0, target+1));
		send_map = true;
	}
}

void ServerSam::idle()
{
	behavior_timer--;
	setAnim("samup");
	if (behavior_timer > 0)
	{
	}
	else{
		tag_phase = 0;
	}
}

int ServerSam::getBehavior() {
	return behavior;
}

bool ServerSam::timeCheck() {
	return behavior_timer > 0;
}



void ServerSam::walkOff() {
	if (b_walk) {
		b_walk = false;
		for (unsigned int i = 0; i < behaviors.size(); i++) {
			if (behaviors[i] == 1) {
				behaviors.erase(behaviors.begin() + i);
				break;
			}
		}
	}
}


void ServerSam::pteraOff() {
	if (b_ptera) {
		ptera->setVisible(false);
		b_ptera = false;
		for (unsigned int i = 0; i < behaviors.size() != 2; i++) {
			if (behaviors[i] == 2) {
				behaviors.erase(behaviors.begin() + i);
				break;
			}
		}
	}
}

bool ServerSam::timer()
{
	if (behavior_timer > 0) {
		return true;
	}
	else {
		return false;
	}
}

void ServerSam::step(int x, int y)
{
	double playerx, playery, samx, samy;
	playerx = x;
	playery = y;
	samx = this->getPositionX();
	samy = this->getPositionY();
	double theta;
	if (playerx >= samx) {
		theta = atan((playery - samy) / (playerx - samx)) * 180 / 3.14159;
	}
	else if (playery > samy) {
		theta = 180 + (atan((playery - samy) / (playerx - samx)) * 180 / 3.14159);
	}
	else {
		theta = -180 + atan((playery - samy) / (playerx - samx)) * 180 / 3.14159;
	}
	if (distance[target] > 2) {

		this->setPositionX(this->getPositionX() + walk_speed*(cos(theta * 3.14159 / 180)));
		this->setPositionY(this->getPositionY() + walk_speed*(sin(theta * 3.14159 / 180)));

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
}

std::vector<ServerMessage> ServerSam::getServerMessage()
{
	return queued_messages;
}

bool ServerSam::sendMap()
{
	return send_map;
}

void ServerSam::teleportOff() {
	if (b_teleport) {
		b_teleport = false;
		for (unsigned int i = 0; i < behaviors.size(); i++) {
			if (behaviors[i] == 3) {
				behaviors.erase(behaviors.begin() + i);
				break;
			}
		}
	}
}

void ServerSam::candyOff() {
	if (b_candy) {
		b_candy = false;
		for (unsigned int i = 0; i < behaviors.size() != 4; i++) {
			if (behaviors[i] == 4) {
				behaviors.erase(behaviors.begin() + i);
				break;
			}
		}
	}
}

void ServerSam::attachLevel(LevelManager* levelmanager) {
	lvm = levelmanager;
	blockage = lvm->levelmap->getLayer("Collision");
}

void ServerSam::walkOn() {
	if (!b_walk) {
		b_walk = true;
		behaviors.push_back(1);
	}
}

void ServerSam::teleportOn() {
	if (!b_teleport) {
		b_teleport = true;
		behaviors.push_back(3);
	}
}

void ServerSam::candyOn() {
	if (!b_candy) {
		b_candy = true;
		behaviors.push_back(4);
	}
}

void ServerSam::pteraOn() {
	if (!b_ptera) {
		ptera->setVisible(true);
		b_ptera = true;
		behaviors.push_back(2);
	}
}

void ServerSam::lowerReactW(void) {
	//5 frames is bottom limt of reaction time weight.
	//5 frames at 30 fps is 0.167s and fastest possible human reaction time is 0.15s
	if (reaction_time_weight > 4) {
		reaction_time_weight -= 2;
	}
}

void ServerSam::incReactW(void) {
	//15 frames is upper limt of reaction time weight.
	//15 frames at 30 fps is 0.5s which is kind of the upper outlier of normal human reaction time
	if (reaction_time_weight < 16) {
		reaction_time_weight += 2;
	}
}

//For lovely statistics on human reaction time, check out
//http://www.humanbenchmark.com/tests/reactiontime/statistics