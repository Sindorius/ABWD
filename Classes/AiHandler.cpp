#include "AiHandler.h"

AiHandler::AiHandler(std::vector<Player*>* players)
{

	sam = ServerSam::create(players);
	ptera = Pterodactyl::create();
}

AiHandler::~AiHandler()
{}

void AiHandler::runAI() {
	sam->runAI();
}

ServerSam * AiHandler::getSam()
{
	return sam;
}

Pterodactyl * AiHandler::getPtera()
{
	return ptera;
}
