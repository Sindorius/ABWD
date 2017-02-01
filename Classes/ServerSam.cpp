
#include "ServerSam.h"
#include <math.h>
#include <stdlib.h>
#include "cocos2d.h"
#include <iostream>
#include <random>
#include <time.h>
#include <algorithm>


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
	/*
	if (run_once){
		generatePath(13, 1);
		run_once = false;
		log(std::to_string(lvm->levelmap->getMapSize().height).c_str());
		
	}
	*/
	send_map = false;
	queued_messages.clear();
	target = 0;
	//function pointers return bools which self indicate when the behavior is completed
	if ((this->*current_behavior)()) {
	}
	else {
		std::default_random_engine generator;
		std::uniform_int_distribution<int> distribution(0, behavior_list.size() - 1);
		int selection = distribution(generator);
		current_behavior = behavior_list[selection];
		behavior_timer = behavior_timers[selection];
		initialize_behavior = true;
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
	if (initialize_behavior) {
		current_phase = &ServerSam::chase;
		initialize_behavior = false; 
	}
	(this->*current_phase)();
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
		behavior_timer = 60;
		current_phase = &ServerSam::flee;
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
		behavior_timer = 60;
		current_phase = &ServerSam::appear;
	}
}

void ServerSam::appear()
{
	behavior_timer--;
	if (behavior_timer > 0) {
		setAnim("samappear");
	}
	else {
		current_phase = &ServerSam::hide;
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
		current_phase = &ServerSam::idle;
		behavior_timer = 60;
	}
	else if (behavior_timer == 0) {
		current_phase = &ServerSam::tantrum;
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
		current_phase = &ServerSam::chase;
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
		current_phase = &ServerSam::chase;
	}
}

int ServerSam::getBehavior() {
	return behavior;
}

bool ServerSam::timeCheck() {
	return behavior_timer > 0;
}
/*
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
*/
bool ServerSam::timer()
{
	if (behavior_timer > 0) {
		return true;
	}
	else {
		return false;
	}
}

bool ServerSam::pursue()
{
	if (initialize_behavior) {
		Vec2 coordinate = coordinateToTile(player_list->at(target)->getPositionX(), player_list->at(target)->getPositionY());
		log("generating path");
		walk_path = generatePath(coordinate.x, coordinate.y);
		log("path generated");
		player_list->at(target)->getPositionX();
		current_phase = &ServerSam::testPath;
		initialize_behavior = false;
	}
	step(24 * walk_path[0].first + 12, 24 * walk_path[0].second + 12);
	Vec2 check = coordinateToTile(this->getPositionX(), this->getPositionY());
	if (check.x == walk_path[0].first && check.y == walk_path[0].second) {
		log(" ");
		log(std::to_string(walk_path[0].first).c_str());
		log(std::to_string(walk_path[0].second).c_str());
		walk_path.erase(walk_path.begin());
	}
	//log(std::to_string(walk_path.size()).c_str());
	return (walk_path.size() > 0);
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

std::vector<std::pair<int, int>> ServerSam::generatePath(int x, int y)
{
	//log("start");
	// parameter x and y indicate the destination tile coordinates
	//the cost at start is not 0, fix that for block distance
	bool success = false;
	std::vector<PathNode> open_list = {};
	std::vector<PathNode> closed_list = {};
	int temp_x = this->getPositionX() / lvm->levelmap->getTileSize().width;
	int temp_y = this->getPositionY() / lvm->levelmap->getTileSize().height;
	//log(std::to_string(temp_x).c_str());
	//log(std::to_string(temp_y).c_str());
	PathNode initial_node = { temp_x, temp_y, (float)(abs(x - temp_x) + abs(y - temp_y)), 0, 0, 0 };
	open_list.push_back(initial_node);
	
	bool searching = true;
	//tiles are 24x24
	
	while (searching) {
		//log("iteration");
		//index of lowest score item in open list reset
		int score_search = -1;

		//theres nothing in the open list and we didn't find a destination so stop searching
		// FIXME
		// there is not option yet for when there is no path
		if (open_list.size() == 0) {
			//log("open list empty");
			searching = false;
			success = false;
			break;
		}


		// iterate through the open list searching for the lowest score
		for (int i = 0; i < open_list.size(); i++) {
			if (score_search == -1 || open_list[i].cost + open_list[i].step <= open_list[score_search].cost + open_list[score_search].step) {
				score_search = i;
			}
		}
		

		// add the cheapest item location to the closed list and remove it from the open list
		closed_list.push_back(open_list[score_search]);
		open_list.erase(open_list.begin() + score_search);


		//if the new item is the destination, exit
		if (closed_list[closed_list.size() - 1].x == x && closed_list[closed_list.size() - 1].y == y) {
			//log("solution in closed list");
			searching = false;
			success = true;
			break;
		}


		//search every surrounding walkable tile of the newly added item
		int baseX = closed_list[closed_list.size() - 1].x;
		int baseY = closed_list[closed_list.size() - 1].y;
		bool not_in_closed = true;
		bool not_in_open = true;

		//log("searching around: ");
		//log(std::to_string(baseX).c_str());
		//log(std::to_string(23-baseY).c_str());

		//iterates 9 squares around current open list
		for (int i = -1; i < 2; i++) {
			for (int j = -1; j < 2; j++) {
				not_in_closed = true;
				not_in_open = true;
				float step_weight = 1;
				if (i != 0 && j != 0) {
					step_weight = 1.414;
				}
				//bars selecting the center tile and blockage tiles from being checked
				if (!(i == 0 && j == 0) && isClear(baseX + i, baseY + j)) {
					//if a tile is in the closed list, ignore it
					for (int closed_index = 0; closed_index < closed_list.size() && not_in_closed; closed_index++) {
						if (closed_list[closed_index].x == baseX + i && closed_list[closed_index].y == baseY + j) {
							not_in_closed = false;
						}
					}
					
					
					//else if it is in the open list, save the cheaper item and update its parent cost
					if (not_in_closed) {
						for (int open_index = 0; open_index < open_list.size() && not_in_open; open_index++) {
							if (open_list[open_index].x == baseX + i && open_list[open_index].y == baseY + j) {
								not_in_open = false;
								//log("hit");
								int old_cost = open_list[open_index].step;
								int new_cost = closed_list[closed_list.size() - 1].step + step_weight;
								if (new_cost < old_cost) {
									open_list[open_index].step = closed_list[closed_list.size() - 1].step + step_weight;
									open_list[open_index].parent_index = closed_list.size() - 1;

								}
							}
						}
					}
					
					
					//else if it is not in the open list, add it to the open list and give it a score
					if (not_in_open && not_in_closed) {
						float step_weight = 1;
						if (i != 0 && j != 0) {
							step_weight = 1.414;
						}
						int end = closed_list.size();
						int parent = closed_list.size() - 1;
						PathNode new_node = { 
							baseX + i, 
							baseY + j, 
							(float)(abs(x - (baseX + i)) + abs(y - (baseY + j))), 
							(float) (closed_list[closed_list.size() - 1].step) + step_weight,
							end,
							parent
						};

						open_list.push_back(new_node);
					}
				}
			}
		}
	}


	std::vector <std::pair<int, int>> solution_vector;
	if (success) {
		
		int trace_index = closed_list[closed_list.size() - 1].index;
		
		bool tracing = true; 
		//log("we got here");
		while (tracing) {
			
			std::pair<int, int> next_item = { closed_list[trace_index].x, closed_list[trace_index].y };
			log(std::to_string(next_item.first).c_str());
			log(std::to_string(next_item.second).c_str());
			log("");

			solution_vector.push_back(next_item);
			
			trace_index = closed_list[trace_index].parent_index;

			if (closed_list[trace_index].index == 0) { tracing = false; }
		}
		std::reverse(solution_vector.begin(), solution_vector.end());
	}
	return solution_vector;
}

bool ServerSam::isClear(int x, int y)
{
	Vec2 tileCoord = Vec2(x, lvm->levelmap->getMapSize().height - 1 - y);
	if (tileCoord.x > 0 && tileCoord.x < lvm->levelmap->getMapSize().width && tileCoord.y > 0 && tileCoord.y < lvm->levelmap->getMapSize().height)
	{
		if (blockage != NULL)
		{
			int bkTile = blockage->getTileGIDAt(tileCoord);
			if (bkTile)
			{
				auto tilemapvals = lvm->levelmap->getPropertiesForGID(bkTile).asValueMap();
				if (!tilemapvals.empty())
				{
					auto w = tilemapvals["Collidable"].asString();

					if ("true" == w) {
						return false;
					}
				}
			}
		}
	}
	else {
		return false;
	}
	return true;
}

std::vector<ServerMessage> ServerSam::getServerMessage()
{
	return queued_messages;
}

bool ServerSam::sendMap()
{
	return send_map;
}


bool ServerSam::testingBehavior()
{
	if (initialize_behavior) {
		current_phase = &ServerSam::testPath;
		initialize_behavior = false;
	}
	(this->*current_phase)();
	return timer();
}

void ServerSam::testPath()
{
	this->setPositionX(this->getPositionX()+1);
}

Vec2 ServerSam::coordinateToTile(int x, int y)
{
	
	int tilex = x / (lvm->levelmap->getTileSize().width);
	int tiley = y / (lvm->levelmap->getTileSize().height);
	
	return Vec2(tilex,tiley);
}
/*
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
*/
void ServerSam::attachLevel(LevelManager* levelmanager) {
	lvm = levelmanager;
	blockage = lvm->levelmap->getLayer("Collision");
}
/*
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
*/
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