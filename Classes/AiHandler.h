#ifndef AI_HANDLER_HPP
#define AI_HANDLER_HPP

#include "ServerSam.h"
#include "Pterodactyl.h"
#include "cocos2d.h"
#include "Player.h"
#include <array>
#include "Candy.h"
#include "LevelManager.hpp"

class ServerSam;
class Pterodactyl;

class AiHandler
{
public:

	AiHandler(std::vector<Player*>* players);
	~AiHandler();

	void runAI();

	ServerSam* getSam();
	Pterodactyl* getPtera();

private:
	ServerSam* sam;
	Pterodactyl* ptera;
};

#endif //AI_HANDLER_HPP