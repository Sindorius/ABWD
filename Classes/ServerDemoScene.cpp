#include "ServerDemoScene.h"

USING_NS_CC;



Scene* ServerDemo::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = ServerDemo::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool ServerDemo::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}
	/*
	auto director = Director::getInstance();
	auto glview = director->getOpenGLView();
	float animint = director->getAnimationInterval();
	log("from animint");
	log(std::to_string(animint).c_str());
	int refreshrate = glview->getRunningRefreshRate();
	if(refreshrate == 59)
	{
		refreshrate = 60;
	}
	if (refreshrate == 119)
	{
		refreshrate = 120;
	}
	log("from get refresh rate");
	log(std::to_string(refreshrate).c_str());
	int newswapinterval = refreshrate*animint;
	if(newswapinterval < 1)
	{
		newswapinterval = 1;
	}
	swapframes = newswapinterval;
	swapframecounter = newswapinterval;

	log("from newswapinterval");
	log(std::to_string(newswapinterval).c_str());
	*/
		
	player1 = Player::create(1, 0);
	player1->debugDraw(true);
	addChild(player1, 0);

	player2 = Player::create(2, 0);
	player2->debugDraw(true);
	addChild(player2, 0);

	player3 = Player::create(3, 0);
	player3->debugDraw(true);
	addChild(player3, 0);

	player4 = Player::create(4, 0);
	player4->debugDraw(true);
	addChild(player4, 0);

	players.push_back(player1);
	players.push_back(player2);
	players.push_back(player3);
	players.push_back(player4);

	Ai = new AiHandler(&players);

	serversam = Ai->getSam();
	addChild(serversam, 0);

	pterodactyl = Ai->getPtera();
	addChild(pterodactyl, 0);

	candy = Candy::create();
	addChild(candy, 0);

	loadLevel(1);

	serversam->attachLevel(&levelmanager);

	std::ifstream is("config.json");
	cereal::JSONInputArchive configloader(is);
	setupdata = ConfigFileInput();
	configloader(setupdata);
	is.close();

	srand(time(NULL)); //for better randomness from rand()

	log("port is");
	log(std::to_string(setupdata.port).c_str());

	try
	{
		log("intry");
		//boost::asio::io_service io_service;
		io_service_p = new boost::asio::io_service;
		log("madepastioservice");
		mytcpserverp = new TCPServer(*io_service_p, setupdata.port, this);
		log("madepastserver");
	}
	catch (std::exception& e)
	{
		std::cerr << "Exception: " << e.what() << "\n";
	}



	auto keyListener = EventListenerKeyboard::create();
	keyListener->onKeyPressed = CC_CALLBACK_2(ServerDemo::KeyDown, this);

	_eventDispatcher->addEventListenerWithFixedPriority(keyListener, 2);

	this->scheduleUpdate();
	return true;
}


void ServerDemo::update(float dt)
{
	if (!alternate && dt < 0.03f)
	{
		alternate = true;
		io_service_p->poll();
		return;
	}
	else
	{
		alternate = false;
	}
	/*
	if (--swapframecounter <= 0)
	{
		swapframecounter = swapframes;
	}
	else 
	{
		io_service_p->poll();
		return; 
	}
	*/
	//log("UPDATE DT");
	//log(std::to_string(dt).c_str());
	io_service_p->poll();

	if (eventActive == false)
	{
		//update and check if any players are idle, update anims
		updateIdleAnims();

		if (levelmanager.currentlevel != 1 && solved_timer_start == false)
		{
			serversam->setPriority(PLAYER_GRID, DRY_GRID, dried);
			Ai->runAI();
			for (int i = 0; i < serversam->getServerMessage().size(); i++) {
				enqueueMessage(serversam->getServerMessage()[i]);
				sendmap = Ai->getSam()->sendMap();
			}
		}

		//set local z-order
		player1->setLocalZOrder(-player1->getPositionY());
		player2->setLocalZOrder(-player2->getPositionY());
		player3->setLocalZOrder(-player3->getPositionY());
		player4->setLocalZOrder(-player4->getPositionY());
		serversam->setLocalZOrder(-serversam->getPositionY());
		pterodactyl->setLocalZOrder(-pterodactyl->getPositionY());

		//check if any tiles need to be dried and 'dries' them
		dryTiles();

		//check if a player collides with sam/ptero and erase tiles
		//checkEnemyCollision();

		//check is puzzle solved, then let players admire their finished puzzles for a few seconds
		checkSolved();
	}
	else
	{
		if (transitionTimer == 0) //wait till transition is over to start event
		{
			runEvent(1); //1 is when sam paints on new level
		}
		else
		{
			transitionTimer--;
		}
	}
	mytcpserverp->sendPacket(createPacket());

	io_service_p->poll();

}



char ServerDemo::getActiveChars()
{
	char p1mask = 1;
	char p2mask = 2; 
	char p3mask = 4; 
	char p4mask = 8;
	char returnchar = 0;
	if (sessionmapped[1])
	{
		returnchar = returnchar | p1mask;
		player1->setVisible(true);
	}
	else
	{
		player1->setVisible(false);
	}
	if (sessionmapped[2])
	{
		returnchar = returnchar | p2mask;
		player2->setVisible(true);
	}
	else
	{
		player2->setVisible(false);
	}
	if (sessionmapped[3])
	{
		returnchar = returnchar | p3mask;
		player3->setVisible(true);
	}
	else
	{
		player3->setVisible(false);
	}
	if (sessionmapped[4])
	{
		returnchar = returnchar | p4mask;
		player4->setVisible(true);
	}
	else
	{
		player4->setVisible(false);
	}
	return returnchar;
}

void ServerDemo::processPlayerPacket(PlayerInputPacket p, TCPSSession* sessionptr)
{
	if (!sessionmapped[p.playernum])
	{
		//sessionmap.emplace(sessionptr, p.playernum);
		sessionmap.insert(boost::bimap<TCPSSession*, int>::value_type(sessionptr, p.playernum));
		sessionmapped[p.playernum] = true;
		players[p.playernum - 1]->setVisible(true);
		sendmap = true; // hack fix until game-in-progress check made
		servermessagequeue.emplace_back(ServerMessage(12, 0, 0, p.playernum));
	}
	else
	{
		if (sessionmap.right.at(p.playernum) != sessionptr)
		{
			//send message to client of the players list;
			std::vector<ServerMessage> tempservermessagequeue;
			tempservermessagequeue.emplace_back(ServerMessage(17, 0, 0, p.playernum));
			mytcpserverp->sendPacket(ServerPositionPacket (getActiveChars(), levelmanager.currentlevel,
				candy->getPositionX(), candy->getPositionY(),
				pterodactyl->getPositionX(), pterodactyl->getPositionY(), animationmanager.charFromString(pterodactyl->getAnim()),
				serversam->getPositionX(), serversam->getPositionY(), animationmanager.charFromString(serversam->getAnim()),
				player1->getPositionX(), player1->getPositionY(), animationmanager.charFromString(player1->getAnim()),
				player2->getPositionX(), player2->getPositionY(), animationmanager.charFromString(player2->getAnim()),
				player3->getPositionX(), player3->getPositionY(), animationmanager.charFromString(player3->getAnim()),
				player4->getPositionX(), player4->getPositionY(), animationmanager.charFromString(player4->getAnim()), blankvector, tempservermessagequeue)
			,sessionptr);
		}
	}


	float dxmove = p.dx;
	float dymove = p.dy;

	if (candy->active() && p.playernum - 1 == candy->getOwner()) {
		dxmove = dxmove * 2;
		dymove = dymove * 2;

	}
	auto playerPos = players[p.playernum - 1]->getPosition();
	std::string newcolor = "none";


	// Convert the players position into tile coordinates
	int testx = (playerPos.x + p.dx) / (levelmanager.levelmap->getTileSize().width);
	int testy = ((levelmanager.levelmap->getMapSize().height * levelmanager.levelmap->getTileSize().height) - playerPos.y - p.dy) / (levelmanager.levelmap->getTileSize().height);
	Vec2 tileCoord = Vec2(testx, testy);
	if (blockage != NULL)
	{
		int bkTile = blockage->getTileGIDAt(tileCoord);
		if (bkTile)
		{
			auto tilemapvals = levelmanager.levelmap->getPropertiesForGID(bkTile).asValueMap();
			if (!tilemapvals.empty())
			{
				auto w = tilemapvals["Collidable"].asString();

				if ("true" == w) {
					//dxmove = -dxmove * 2;
					//dymove = -dymove * 2;
					dxmove = 0;
					dymove = 0;
				}
			}
		}
	}

	players[p.playernum - 1]->setPositionX(playerPos.x + dxmove);
	players[p.playernum - 1]->setPositionY(playerPos.y + dymove);
	std::string playerstring = "p";
	playerstring += std::to_string(p.playernum).c_str();
	if (p.playernum == 1){
		idle1 = 3;
	}
	else if (p.playernum == 2) {
		idle2 = 3;
	}
	else if (p.playernum == 3) {
		idle3 = 3;
	}
	else if (p.playernum == 4) {
		idle4 = 3;
	}
	//players[p.playernum - 1]->setAnim(playerstring + "idle");
	if (players[p.playernum - 1]->getPosition().y > playerPos.y) {
		players[p.playernum - 1]->setAnim(playerstring + "up");
		
	}
	else if (players[p.playernum - 1]->getPosition().y < playerPos.y) {
		players[p.playernum - 1]->setAnim(playerstring + "down");
		
	}
	else if (players[p.playernum - 1]->getPosition().x > playerPos.x) {
		players[p.playernum - 1]->setAnim(playerstring + "right");
		
	}
	else if (players[p.playernum - 1]->getPosition().x < playerPos.x) {
		players[p.playernum - 1]->setAnim(playerstring + "left");
		
	}


	if (p.button1)
	{

		players[p.playernum - 1]->setAnim(playerstring + "paint");
		space(p.playernum, tileCoord, dxmove, dymove);
	}


}



void ServerDemo::space(int playernum, Point tileCoord, float dxmove, float dymove)
{


	// Check to see if their position is where there is a bucket and assign that color
	std::string newcolor = "none";


	if (tileCoord.x >= 0 && tileCoord.x <= levelmanager.levelmap->getMapSize().width && tileCoord.y >= 0 && tileCoord.y <= levelmanager.levelmap->getMapSize().height)
	{
		int bTile = bucketlayer->getTileGIDAt(tileCoord);

		if (bTile)
		{
			auto tilemapvals = levelmanager.levelmap->getPropertiesForGID(bTile).asValueMap();

			if (!tilemapvals.empty())
			{
				auto r = tilemapvals["Red"].asString();
				auto b = tilemapvals["Blue"].asString();
				auto y = tilemapvals["Yellow1"].asString();
				auto o = tilemapvals["Orange"].asString();
				auto blk = tilemapvals["Black"].asString();
				
				auto b2 = tilemapvals["Blue2"].asString();
				auto b3 = tilemapvals["Blue3"].asString();
				auto g1 = tilemapvals["Green1"].asString();
				auto g2 = tilemapvals["Green2"].asString();
				auto g3 = tilemapvals["Green3"].asString();

				auto w = tilemapvals["White"].asString();
				auto gy1 = tilemapvals["Grey1"].asString();
				auto gy2 = tilemapvals["Grey2"].asString();
				auto r2 = tilemapvals["Red2"].asString();
				auto p = tilemapvals["Purple1"].asString();
				auto r1 = tilemapvals["Red1"].asString();

				if ("true" == r)
				{
					dxmove = -dxmove * 2;
					dymove = -dymove * 2;
					newcolor = "red";
					servermessagequeue.emplace_back(ServerMessage(16, playernum, 0, 2));
				}
				else if ("true" == b)
				{
					dxmove = -dxmove * 2;
					dymove = -dymove * 2;
					newcolor = "blue";
					servermessagequeue.emplace_back(ServerMessage(16, playernum, 0, 3));
				}
				else if ("true" == y) {
					dxmove = -dxmove * 2;
					dymove = -dymove * 2;
					newcolor = "yellow";
					servermessagequeue.emplace_back(ServerMessage(16, playernum, 0, 4));
				}
				else if ("true" == o) {
					dxmove = -dxmove * 2;
					dymove = -dymove * 2;
					newcolor = "orange";
					servermessagequeue.emplace_back(ServerMessage(16, playernum, 0, 5));
				}
				else if ("true" == blk) {
					dxmove = -dxmove * 2;
					dymove = -dymove * 2;
					newcolor = "black";
					servermessagequeue.emplace_back(ServerMessage(16, playernum, 0, 6));
				}

				else if ("true" == b2) {
					dxmove = -dxmove * 2;
					dymove = -dymove * 2;
					newcolor = "blue2";
					servermessagequeue.emplace_back(ServerMessage(16, playernum, 0, 7));
				}
				else if ("true" == b3) {
					dxmove = -dxmove * 2;
					dymove = -dymove * 2;
					newcolor = "blue3";
					servermessagequeue.emplace_back(ServerMessage(16, playernum, 0, 8));
				}
				else if ("true" == g1) {
					dxmove = -dxmove * 2;
					dymove = -dymove * 2;
					newcolor = "green1";
					servermessagequeue.emplace_back(ServerMessage(16, playernum, 0, 9));
				}
				else if ("true" == g2) {
					dxmove = -dxmove * 2;
					dymove = -dymove * 2;
					newcolor = "green2";
					servermessagequeue.emplace_back(ServerMessage(16, playernum, 0, 10));
				}
				else if ("true" == g3) {
					dxmove = -dxmove * 2;
					dymove = -dymove * 2;
					newcolor = "green3";
					servermessagequeue.emplace_back(ServerMessage(16, playernum, 0, 11));
				}
				///// ADDED THIS
				else if ("true" == w) {
					dxmove = -dxmove * 2;
					dymove = -dymove * 2;
					newcolor = "white";
					servermessagequeue.emplace_back(ServerMessage(16, playernum, 0, 12));
				}
				else if ("true" == gy1) {
					dxmove = -dxmove * 2;
					dymove = -dymove * 2;
					newcolor = "grey1";
					servermessagequeue.emplace_back(ServerMessage(16, playernum, 0, 13));
				}
				else if ("true" == gy2) {
					dxmove = -dxmove * 2;
					dymove = -dymove * 2;
					newcolor = "grey2";
					servermessagequeue.emplace_back(ServerMessage(16, playernum, 0, 14));
				}
				else if ("true" == r2) {
					dxmove = -dxmove * 2;
					dymove = -dymove * 2;
					newcolor = "red2";
					servermessagequeue.emplace_back(ServerMessage(16, playernum, 0, 15));
				}
				else if ("true" == p) {
					dxmove = -dxmove * 2;
					dymove = -dymove * 2;
					newcolor = "purple1";
					servermessagequeue.emplace_back(ServerMessage(16, playernum, 0, 16));
				}
				else if ("true" == r1) {
					dxmove = -dxmove * 2;
					dymove = -dymove * 2;
					newcolor = "red1";
					servermessagequeue.emplace_back(ServerMessage(16, playernum, 0, 17));
				}
			}
		}

		if (newcolor != "none")
		{
			players[playernum - 1]->setColor(newcolor);
		}


	}
	// end Check to see if their position is where there is a bucket and assign that color

	updatePaintTiles(playernum);
}

void ServerDemo::loadLevel(int level)
{

	//tell client to load new level
	servermessagequeue.emplace_back(ServerMessage(10, 0, 0, level));

	//code that should be run only after game start (removing previous assets)
	if (levelmanager.currentlevel != 0) //at game start currentlevel = 0
	{
		for (unsigned int i = 0; i < SPRITE_GRID.size(); i++)
		{
			for (unsigned int j = 0; j < SPRITE_GRID[i].size(); j++)
			{
				removeChild(SPRITE_GRID[i][j]);
			}
		}

		//remove old map
		removeChild(levelmanager.levelmap);

		//reset player color+label on new level
		for (unsigned int i = 0; i < players.size(); i++)
		{
			players[i]->setColor("");
			players[i]->setAnim("");

		}
		pterodactyl->setAnim("");
		serversam->setAnim("");
		serversam->setVisible(true);

	}

	levelmanager.setLevel(level);

	addChild(levelmanager.levelmap, -1000);

	//resizes grid, add new paint grid to game scene
	setupPaintTiles();

	serversam->attachLevel(&levelmanager); //needs to update blockage, should find better way...

	// Check to see if there is an object layer 
	spawnObjs = levelmanager.levelmap->getObjectGroup("SpawnObjects");

	if (spawnObjs == NULL) {
		log("TMX map has no SpawnObjects layer");
	}
	else
	{
		ValueMap playerOneSP = spawnObjs->getObject("P1spawnPoint");
		ValueMap playerTwoSP = spawnObjs->getObject("P2spawnPoint");
		ValueMap playerThreeSP = spawnObjs->getObject("P3spawnPoint");
		ValueMap playerFourSP = spawnObjs->getObject("P4spawnPoint");
		player1->setPosition(Vec2(playerOneSP["x"].asInt(), playerOneSP["y"].asInt()));
		player2->setPosition(Vec2(playerTwoSP["x"].asInt(), playerTwoSP["y"].asInt()));
		player3->setPosition(Vec2(playerThreeSP["x"].asInt(), playerThreeSP["y"].asInt()));
		player4->setPosition(Vec2(playerFourSP["x"].asInt(), playerFourSP["y"].asInt()));

	}

	blockage = levelmanager.levelmap->getLayer("Collision");
	if (blockage != NULL)
	{
		blockage->setVisible(false);
	}
	bucketlayer = levelmanager.levelmap->getLayer("Paintbuckets");
	blankCanvas = levelmanager.levelmap->getLayer("BlankCanvas");

	if (blankCanvas != NULL)
	{
		blankCanvas->setCascadeOpacityEnabled(true);
	}

	if (level == 1) 
	{
		serversam->setVisible(false);
		pterodactyl->setVisible(false);
		serversam->pteraOff();
		serversam->candyOff();
		serversam->setPosition(-1000, -1000);
		dried = 10;
		eventActive = paintEvent.phase1 = false;
		this->setScale(1.0f);
	}
	else if (level == 2) {
		serversam->teleportOn();
		serversam->walkOn();
		serversam->pteraOff();
		serversam->candyOff();
		samInitPos.set(Vec2(238, 150));
		serversam->setPosition(samInitPos);
		dried = 8;
		wallYCoord = 302;
		if (EVENTS_ON == 1)
		{
			eventActive = paintEvent.phase1 = true;
		}
		else
		{
			blankCanvas->setVisible(false);
		}
		transitionTimer = 90; //little more than transition time in clientdemoscene
		this->setScale(1.0f);
		enqueueMessage(ServerMessage(19, 1, 0, 5)); //tells client to start sam painting event
	}
	else if (level == 3) {
		serversam->teleportOn();
		serversam->walkOn();
		serversam->pteraOff();
		serversam->candyOn();
		samInitPos.set(Vec2(300, 150));
		serversam->setPosition(samInitPos);
		dried = 8;
		wallYCoord = 278;
		if (EVENTS_ON == 1)
		{
			eventActive = paintEvent.phase1 = true;
		}
		else
		{
			blankCanvas->setVisible(false);
		}
		transitionTimer = 90;
		this->setScale(.6f);
		enqueueMessage(ServerMessage(19, 1, 0, 5)); //tells client to start sam painting event
	}
	else if (level == 4) {
		pterodactyl->setVisible(true);
		serversam->pteraOn();
		serversam->candyOn();
		serversam->teleportOn();
		serversam->walkOn();
		samInitPos.set(Vec2(370, 320));
		serversam->setPosition(samInitPos);
		dried = 7;
		wallYCoord = 496;
		if (EVENTS_ON == 1)
		{
			eventActive = paintEvent.phase1 = true;
		}
		else
		{
			blankCanvas->setVisible(false);
		}
		transitionTimer = 90;
		this->setScale(.6f);
		enqueueMessage(ServerMessage(19, 1, 0, 5)); //tells client to start sam painting event
	}

}


void ServerDemo::KeyDown(EventKeyboard::KeyCode keyCode, Event* event)
{
	switch (keyCode)
	{
	
	case EventKeyboard::KeyCode::KEY_CAPITAL_K:
	case EventKeyboard::KeyCode::KEY_K:
		loadLevel(-1);
	break;
	case EventKeyboard::KeyCode::KEY_CAPITAL_S:
	case EventKeyboard::KeyCode::KEY_S:
		loadLevel(1);
	break;
	case EventKeyboard::KeyCode::KEY_CAPITAL_C:
	case EventKeyboard::KeyCode::KEY_C:
		loadLevel(2);
		break;
	case EventKeyboard::KeyCode::KEY_CAPITAL_P:
	case EventKeyboard::KeyCode::KEY_P:
		loadLevel(3);
	break;
	case EventKeyboard::KeyCode::KEY_CAPITAL_O:
	case EventKeyboard::KeyCode::KEY_O:
		loadLevel(4);
		break;
	case EventKeyboard::KeyCode::KEY_CAPITAL_E:
	case EventKeyboard::KeyCode::KEY_E:
		enqueueMessage(ServerMessage(15, 0, 0, 0)); //gameover
		loadLevel(1);
		break;
	case EventKeyboard::KeyCode::KEY_1:
		Director::getInstance()->getOpenGLView()->setFrameZoomFactor(1.0f);
		break;
	case EventKeyboard::KeyCode::KEY_2:
		Director::getInstance()->getOpenGLView()->setFrameZoomFactor(2.0f);
		break;
	case EventKeyboard::KeyCode::KEY_3:
		Director::getInstance()->getOpenGLView()->setFrameZoomFactor(3.0f);
		break;

	}

	event->stopPropagation();
}



void ServerDemo::setupPaintTiles()
{
	//resize game grid to fit level's grid size
	SPRITE_GRID.resize(CURRENT_GRID.size());
	for (unsigned int i = 0; i < SPRITE_GRID.size(); i++)
	{
		SPRITE_GRID[i].resize(CURRENT_GRID[i].size());
	}

	//add new grid to game scene
	for (unsigned int i = 0; i < SPRITE_GRID.size(); i++)
	{
		for (unsigned int j = 0; j < SPRITE_GRID[i].size(); j++)
		{
			SPRITE_GRID[i][j] = PaintTile::create();
			SPRITE_GRID[i][j]->setPosition(24 * j + levelmanager.tilestartpoint.x, 24 * i + levelmanager.tilestartpoint.y);
			SPRITE_GRID[i][j]->debugDraw(true);
			addChild(SPRITE_GRID[i][j], -999);
		}
	}
}

void ServerDemo::updatePaintTiles(int playernum)
{
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// optimize this, might not need to go through each tile here.
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	for (unsigned int i = 0; i < CURRENT_GRID.size(); i++)
	{
		for (unsigned int j = 0; j < CURRENT_GRID[i].size(); j++)
		{
			if (players[playernum - 1]->getColor() != "" //check if player has paint
			 &&	players[playernum - 1]->getPositionX() > SPRITE_GRID[i][j]->getPositionX() - 12 
			 && players[playernum - 1]->getPositionX() < SPRITE_GRID[i][j]->getPositionX() + 12 
			 && players[playernum - 1]->getPositionY() > SPRITE_GRID[i][j]->getPositionY() - 12 
			 && players[playernum - 1]->getPositionY() < SPRITE_GRID[i][j]->getPositionY() + 12)
			{
				SPRITE_GRID[i][j]->setColor(players[playernum - 1]->getColor());
				SPRITE_GRID[i][j]->setDry(false); //when dry tile repainted it is wet again
				//enqueueMessage(ServerMessage(18, (float)i, (float)j, 1)); //tells client a tile needs to be wet again
				SPRITE_GRID[i][j]->refreshColor();
				DRY_GRID[i][j] = 0;

				std::pair<int, int> coords;
				coords.first = i;
				coords.second = j;

				if (PLAYER_GRID[i][j] != 0)
				{
					if (PLAYER_GRID[i][j] != playernum)
					{
						if (DRY_GRID[i][j] != dried)
						{
							std::vector<std::pair<int, int>>::iterator it;
							it = std::find(players[PLAYER_GRID[i][j] - 1]->paintedTiles.begin(), players[PLAYER_GRID[i][j] - 1]->paintedTiles.end(), coords);
							if (it != players[PLAYER_GRID[i][j] - 1]->paintedTiles.end()) //if dried tile found in player's paintedTiles vector
							{
								players[PLAYER_GRID[i][j] - 1]->paintedTiles.erase(it);
							}
							else
							{
								std::string str = "Error - cannot update tile at " + std::to_string(i) + " " + std::to_string(j) + " not found in players[" + std::to_string(PLAYER_GRID[i][j] - 1) + "]->paintedTiles";
								log(str.c_str());
							}
						}
						players[playernum - 1]->paintedTiles.push_back(coords);
					}
				}
				else
				{
					players[playernum - 1]->paintedTiles.push_back(coords);
				}

				if (players[playernum - 1]->getColor() == "red")
				{
					if (levelmanager.puzzle.checkTile(i, j, 2)) //if the right color for that tile is red
					{
						if (CURRENT_GRID[i][j] != 2) //if its not already painted red
						{
							CURRENT_GRID[i][j] = 2;
							levelmanager.puzzle.tileCompleted();
						}
					}
					else { //if correct color for tile is NOT red
						if (CURRENT_GRID[i][j] == SOLUTION_GRID[i][j]) //if the tile was right before re-painting
						{
							levelmanager.puzzle.tileErased();
						}
						CURRENT_GRID[i][j] = 20;
					}
				}
				if (players[playernum - 1]->getColor() == "blue")
				{
					if (levelmanager.puzzle.checkTile(i, j, 3))
					{
						if (CURRENT_GRID[i][j] != 3)
						{
							CURRENT_GRID[i][j] = 3;
							levelmanager.puzzle.tileCompleted();
						}
					}
					else {
						if (CURRENT_GRID[i][j] == SOLUTION_GRID[i][j])
						{
							levelmanager.puzzle.tileErased();
						}
						CURRENT_GRID[i][j] = 30;
					}
				}
				if (players[playernum - 1]->getColor() == "yellow")
				{
					if (levelmanager.puzzle.checkTile(i, j, 4))
					{
						if (CURRENT_GRID[i][j] != 4)
						{
							CURRENT_GRID[i][j] = 4;
							levelmanager.puzzle.tileCompleted();
						}
					}
					else {
						if (CURRENT_GRID[i][j] == SOLUTION_GRID[i][j])
						{
							levelmanager.puzzle.tileErased();
						}
						CURRENT_GRID[i][j] = 40;
					}
				}
				if (players[playernum - 1]->getColor() == "orange")
				{
					if (levelmanager.puzzle.checkTile(i, j, 5))
					{
						if (CURRENT_GRID[i][j] != 5)
						{
							CURRENT_GRID[i][j] = 5;
							levelmanager.puzzle.tileCompleted();
						}
					}
					else {
						if (CURRENT_GRID[i][j] == SOLUTION_GRID[i][j])
						{
							levelmanager.puzzle.tileErased();
						}
						CURRENT_GRID[i][j] = 50;
					}
				}
				if (players[playernum - 1]->getColor() == "black")
				{
					if (levelmanager.puzzle.checkTile(i, j, 6))
					{
						if (CURRENT_GRID[i][j] != 6)
						{
							CURRENT_GRID[i][j] = 6;
							levelmanager.puzzle.tileCompleted();
						}
					}
					else {
						if (CURRENT_GRID[i][j] == SOLUTION_GRID[i][j])
						{
							levelmanager.puzzle.tileErased();
						}
						CURRENT_GRID[i][j] = 60;
					}
				}
				if (players[playernum - 1]->getColor() == "blue2")
				{
					if (levelmanager.puzzle.checkTile(i, j, 7))
					{
						if (CURRENT_GRID[i][j] != 7)
						{
							CURRENT_GRID[i][j] = 7;
							levelmanager.puzzle.tileCompleted();
						}
					}
					else {
						if (CURRENT_GRID[i][j] == SOLUTION_GRID[i][j])
						{
							levelmanager.puzzle.tileErased();
						}
						CURRENT_GRID[i][j] = 70;
					}
				}
				if (players[playernum - 1]->getColor() == "blue3")
				{
					if (levelmanager.puzzle.checkTile(i, j, 8))
					{
						if (CURRENT_GRID[i][j] != 8)
						{
							CURRENT_GRID[i][j] = 8;
							levelmanager.puzzle.tileCompleted();
						}
					}
					else {
						if (CURRENT_GRID[i][j] == SOLUTION_GRID[i][j])
						{
							levelmanager.puzzle.tileErased();
						}
						CURRENT_GRID[i][j] = 71;
					}
				}
				if (players[playernum - 1]->getColor() == "green1")
				{
					if (levelmanager.puzzle.checkTile(i, j, 9))
					{
						if (CURRENT_GRID[i][j] != 9)
						{
							CURRENT_GRID[i][j] = 9;
							levelmanager.puzzle.tileCompleted();
						}
					}
					else {
						if (CURRENT_GRID[i][j] == SOLUTION_GRID[i][j])
						{
							levelmanager.puzzle.tileErased();
						}
						CURRENT_GRID[i][j] = 72;
					}
				}
				if (players[playernum - 1]->getColor() == "green2")
				{
					if (levelmanager.puzzle.checkTile(i, j, 10))
					{
						if (CURRENT_GRID[i][j] != 10)
						{
							CURRENT_GRID[i][j] = 10;
							levelmanager.puzzle.tileCompleted();
						}
					}
					else {
						if (CURRENT_GRID[i][j] == SOLUTION_GRID[i][j])
						{
							levelmanager.puzzle.tileErased();
						}
						CURRENT_GRID[i][j] = 73;
					}
				}
				if (players[playernum - 1]->getColor() == "green3")
				{
					if (levelmanager.puzzle.checkTile(i, j, 11))
					{
						if (CURRENT_GRID[i][j] != 11)
						{
							CURRENT_GRID[i][j] = 11;
							levelmanager.puzzle.tileCompleted();
						}
					}
					else {
						if (CURRENT_GRID[i][j] == SOLUTION_GRID[i][j])
						{
							levelmanager.puzzle.tileErased();
						}
						CURRENT_GRID[i][j] = 74;
					}
				}
				if (players[playernum - 1]->getColor() == "white")
				{
					if (levelmanager.puzzle.checkTile(i, j, 12))
					{
						if (CURRENT_GRID[i][j] != 12)
						{
							CURRENT_GRID[i][j] = 12;
							levelmanager.puzzle.tileCompleted();
						}
					}
					else {
						if (CURRENT_GRID[i][j] == SOLUTION_GRID[i][j])
						{
							levelmanager.puzzle.tileErased();
						}
						CURRENT_GRID[i][j] = 75;
					}
				}
				if (players[playernum - 1]->getColor() == "grey1")
				{
					if (levelmanager.puzzle.checkTile(i, j, 13))
					{
						if (CURRENT_GRID[i][j] != 13)
						{
							CURRENT_GRID[i][j] = 13;
							levelmanager.puzzle.tileCompleted();
						}
					}
					else {
						if (CURRENT_GRID[i][j] == SOLUTION_GRID[i][j])
						{
							levelmanager.puzzle.tileErased();
						}
						CURRENT_GRID[i][j] = 76;
					}
				}
				if (players[playernum - 1]->getColor() == "grey2")
				{
					if (levelmanager.puzzle.checkTile(i, j, 14))
					{
						if (CURRENT_GRID[i][j] != 14)
						{
							CURRENT_GRID[i][j] = 14;
							levelmanager.puzzle.tileCompleted();
						}
					}
					else {
						if (CURRENT_GRID[i][j] == SOLUTION_GRID[i][j])
						{
							levelmanager.puzzle.tileErased();
						}
						CURRENT_GRID[i][j] = 77;
					}
				}
				if (players[playernum - 1]->getColor() == "red2")
				{
					if (levelmanager.puzzle.checkTile(i, j, 15))
					{
						if (CURRENT_GRID[i][j] != 15)
						{
							CURRENT_GRID[i][j] = 15;
							levelmanager.puzzle.tileCompleted();
						}
					}
					else {
						if (CURRENT_GRID[i][j] == SOLUTION_GRID[i][j])
						{
							levelmanager.puzzle.tileErased();
						}
						CURRENT_GRID[i][j] = 78;
					}
				}
				if (players[playernum - 1]->getColor() == "purple1")
				{
					if (levelmanager.puzzle.checkTile(i, j, 16))
					{
						if (CURRENT_GRID[i][j] != 16)
						{
							CURRENT_GRID[i][j] = 16;
							levelmanager.puzzle.tileCompleted();
						}
					}
					else {
						if (CURRENT_GRID[i][j] == SOLUTION_GRID[i][j])
						{
							levelmanager.puzzle.tileErased();
						}
						CURRENT_GRID[i][j] = 79;
					}
				}
				if (players[playernum - 1]->getColor() == "red1")
				{
					if (levelmanager.puzzle.checkTile(i, j, 17))
					{
						if (CURRENT_GRID[i][j] != 17)
						{
							CURRENT_GRID[i][j] = 17;
							levelmanager.puzzle.tileCompleted();
						}
					}
					else {
						if (CURRENT_GRID[i][j] == SOLUTION_GRID[i][j])
						{
							levelmanager.puzzle.tileErased();
						}
						CURRENT_GRID[i][j] = 80;
					}
				}
				sendmap = true;
				PLAYER_GRID[i][j] = playernum;
			}
		}
	}


}


ServerPositionPacket ServerDemo::createPacket()
{

	if (sendmap)
	{
		ServerPositionPacket p(getActiveChars(),levelmanager.currentlevel,
			candy->getPositionX(), candy->getPositionY(),
			pterodactyl->getPositionX(), pterodactyl->getPositionY(), animationmanager.charFromString(pterodactyl->getAnim()),
			serversam->getPositionX(), serversam->getPositionY(), animationmanager.charFromString(serversam->getAnim()),
			player1->getPositionX(), player1->getPositionY(), animationmanager.charFromString(player1->getAnim()),
			player2->getPositionX(), player2->getPositionY(), animationmanager.charFromString(player2->getAnim()),
			player3->getPositionX(), player3->getPositionY(), animationmanager.charFromString(player3->getAnim()),
			player4->getPositionX(), player4->getPositionY(), animationmanager.charFromString(player4->getAnim()), CURRENT_GRID, servermessagequeue);
		//		player4->getPositionX(), player4->getPositionY(), animationmanager.charFromString(player4->getAnim()), std::vector<std::vector<char>>());
		sendmap = false;
		servermessagequeue.clear();
		return p;
	}
	else
	{
		ServerPositionPacket p(getActiveChars(),levelmanager.currentlevel,
			candy->getPositionX(), candy->getPositionY(),
			pterodactyl->getPositionX(), pterodactyl->getPositionY(), animationmanager.charFromString(pterodactyl->getAnim()),
			serversam->getPositionX(), serversam->getPositionY(), animationmanager.charFromString(serversam->getAnim()),
			player1->getPositionX(), player1->getPositionY(), animationmanager.charFromString(player1->getAnim()),
			player2->getPositionX(), player2->getPositionY(), animationmanager.charFromString(player2->getAnim()),
			player3->getPositionX(), player3->getPositionY(), animationmanager.charFromString(player3->getAnim()),
			player4->getPositionX(), player4->getPositionY(), animationmanager.charFromString(player4->getAnim()), blankvector, servermessagequeue);
		//		player4->getPositionX(), player4->getPositionY(), animationmanager.charFromString(player4->getAnim()), std::vector<std::vector<char>>());
		servermessagequeue.clear();
		return p;
		//mytcpserverp->sendPacket(p);
	}
		
}

//UNUSED
void ServerDemo::addPlayerToGame(int playernum)
{
	players[playernum - 1]->setVisible(true);
	enqueueMessage(ServerMessage(12, 0, 0, playernum));

}
void ServerDemo::removePlayerFromGame(TCPSSession* sessionptr)
{
	int theplayernum = -1;
	//auto it = sessionmap.find(sessionptr);
	//if (it != sessionmap.end())
	//{
	//	theplayernum = it->second;
	//	sessionmap.erase(it);
	//	sessionmapped[theplayernum] = false;
	//}
	//else { return; }
	
	try {
		theplayernum = sessionmap.left.at(sessionptr);
		sessionmap.left.erase(sessionptr);
	}
	catch(std::out_of_range & e){
		return;
	}
	sessionmapped[theplayernum] = false;
	players[theplayernum - 1]->setVisible(false);
	
	enqueueMessage(ServerMessage(11, 0, 0, theplayernum));

}

void ServerDemo::enqueueMessage(ServerMessage msg)
{
	servermessagequeue.emplace_back(msg);
}

void ServerDemo::runEvent(int e)
{
	//e = 1: new level sam painting event
	//e = 2: ...

	if (e == 1)
	{
		//run paint event, if it returns false event is over
		if (false == runPaintEvent())
		{
			eventActive = false;
			enqueueMessage(ServerMessage(19, e, 0, 4)); //tell client event is over
		}
	}
}

//event for sam making painting on each new level
bool ServerDemo::runPaintEvent(void)
{
	if (paintEvent.eventTimer == 0)
	{
		
		/*// Convert sam's position into tile coordinates
		int samTileX = (serversam->getPositionX()) / (levelmanager.levelmap->getTileSize().width);
		int samTileY = ((levelmanager.levelmap->getMapSize().height * levelmanager.levelmap->getTileSize().height) - serversam->getPositionY()) / (levelmanager.levelmap->getTileSize().height);
		samTile = Vec2(samTileX, samTileY);
		if (blockage != NULL)
		{
			int bkTile = blockage->getTileGIDAt(samTile);
			if (bkTile)
			{
				auto tilemapvals = levelmanager.levelmap->getPropertiesForGID(bkTile).asValueMap();
				if (!tilemapvals.empty())
				{
					samHitWall = tilemapvals["Collidable"].asString();
				}
			}
		}*/

		//phase1:sam walks to painting + paints it
		if (paintEvent.phase1 == true)
		{
			//if sam has not yet reached painting
			if (serversam->getPositionY() < wallYCoord) //see if i can remove hardcoding of pos
			//if ("true" != samHitWall)
			{
				if (paintEvent.init == false) //if phase1 initilization hasnt happened yet
				{
					//enqueueMessage(ServerMessage(19, 1, 0, 1)); //tell client event started
					serversam->setAnim("samup");
					paintEvent.init = true;
				}
				serversam->setPositionY(serversam->getPositionY() + 2.0f);
				//paintEvent.eventTimer = 15;
			}
			else //sam has reached painting
			{
				paintEvent.phase1 = false;
				paintEvent.phase2 = true;
				paintEvent.init = false;
				enqueueMessage(ServerMessage(19, 1, 0, 2)); //tell client to play painting sound
				//paintEvent.eventTimer = 90;
			}
		}
		//phase2:painting gradually comes into view
		else if (paintEvent.phase2 == true)
		{
			if (paintEvent.init == false) //if phase2 initilization hasnt happened yet
			{
				//find better way to do below
				//possibly get all tiles in a layer somehow
				//tmxlayer->getTiles() and tmxlayer->setopacity() dont work...
				//should also move event code to client-side, but have it be triggered server-side

				enqueueMessage(ServerMessage(19, 1, 2, 1)); //tell client to gradually remove blankcanvas layer

				if (levelmanager.currentlevel == 2)
				{
					pSprites.push_back(blankCanvas->getTileAt(Vec2(9, 0)));
					pSprites.push_back(blankCanvas->getTileAt(Vec2(9, 1)));
					pSprites.push_back(blankCanvas->getTileAt(Vec2(9, 2)));
					pSprites.push_back(blankCanvas->getTileAt(Vec2(10, 0)));
					pSprites.push_back(blankCanvas->getTileAt(Vec2(10, 1)));
					pSprites.push_back(blankCanvas->getTileAt(Vec2(10, 2)));
				}
				else if (levelmanager.currentlevel == 3)
				{
					//top painting
					pSprites.push_back(blankCanvas->getTileAt(Vec2(11, 0)));
					pSprites.push_back(blankCanvas->getTileAt(Vec2(11, 1)));
					pSprites.push_back(blankCanvas->getTileAt(Vec2(11, 2)));
					pSprites.push_back(blankCanvas->getTileAt(Vec2(12, 0)));
					pSprites.push_back(blankCanvas->getTileAt(Vec2(12, 1)));
					pSprites.push_back(blankCanvas->getTileAt(Vec2(12, 2)));
					pSprites.push_back(blankCanvas->getTileAt(Vec2(13, 0)));
					pSprites.push_back(blankCanvas->getTileAt(Vec2(13, 1)));
					pSprites.push_back(blankCanvas->getTileAt(Vec2(13, 2)));

					//left painting
					pSprites.push_back(blankCanvas->getTileAt(Vec2(1, 7)));
					pSprites.push_back(blankCanvas->getTileAt(Vec2(1, 8)));
					pSprites.push_back(blankCanvas->getTileAt(Vec2(1, 9)));
					pSprites.push_back(blankCanvas->getTileAt(Vec2(2, 7)));
					pSprites.push_back(blankCanvas->getTileAt(Vec2(2, 8)));
					pSprites.push_back(blankCanvas->getTileAt(Vec2(2, 9)));
					pSprites.push_back(blankCanvas->getTileAt(Vec2(3, 7)));
					pSprites.push_back(blankCanvas->getTileAt(Vec2(3, 8)));
					pSprites.push_back(blankCanvas->getTileAt(Vec2(3, 9)));

					//right painting
					pSprites.push_back(blankCanvas->getTileAt(Vec2(21, 7)));
					pSprites.push_back(blankCanvas->getTileAt(Vec2(21, 8)));
					pSprites.push_back(blankCanvas->getTileAt(Vec2(21, 9)));
					pSprites.push_back(blankCanvas->getTileAt(Vec2(22, 7)));
					pSprites.push_back(blankCanvas->getTileAt(Vec2(22, 8)));
					pSprites.push_back(blankCanvas->getTileAt(Vec2(22, 9)));
					pSprites.push_back(blankCanvas->getTileAt(Vec2(23, 7)));
					pSprites.push_back(blankCanvas->getTileAt(Vec2(23, 8)));
					pSprites.push_back(blankCanvas->getTileAt(Vec2(23, 9)));
				}
				else if (levelmanager.currentlevel == 4)
				{
					//top painting
					pSprites.push_back(blankCanvas->getTileAt(Vec2(14, 0)));
					pSprites.push_back(blankCanvas->getTileAt(Vec2(14, 1)));
					pSprites.push_back(blankCanvas->getTileAt(Vec2(14, 2)));
					pSprites.push_back(blankCanvas->getTileAt(Vec2(15, 0)));
					pSprites.push_back(blankCanvas->getTileAt(Vec2(15, 1)));
					pSprites.push_back(blankCanvas->getTileAt(Vec2(15, 2)));
					pSprites.push_back(blankCanvas->getTileAt(Vec2(16, 0)));
					pSprites.push_back(blankCanvas->getTileAt(Vec2(16, 1)));
					pSprites.push_back(blankCanvas->getTileAt(Vec2(16, 2)));

					//left painting
					pSprites.push_back(blankCanvas->getTileAt(Vec2(3, 8)));
					pSprites.push_back(blankCanvas->getTileAt(Vec2(3, 9)));
					pSprites.push_back(blankCanvas->getTileAt(Vec2(3, 10)));
					pSprites.push_back(blankCanvas->getTileAt(Vec2(4, 8)));
					pSprites.push_back(blankCanvas->getTileAt(Vec2(4, 9)));
					pSprites.push_back(blankCanvas->getTileAt(Vec2(4, 10)));
					pSprites.push_back(blankCanvas->getTileAt(Vec2(5, 8)));
					pSprites.push_back(blankCanvas->getTileAt(Vec2(5, 9)));
					pSprites.push_back(blankCanvas->getTileAt(Vec2(5, 10)));

					//right painting
					pSprites.push_back(blankCanvas->getTileAt(Vec2(25, 8)));
					pSprites.push_back(blankCanvas->getTileAt(Vec2(25, 9)));
					pSprites.push_back(blankCanvas->getTileAt(Vec2(25, 10)));
					pSprites.push_back(blankCanvas->getTileAt(Vec2(26, 8)));
					pSprites.push_back(blankCanvas->getTileAt(Vec2(26, 9)));
					pSprites.push_back(blankCanvas->getTileAt(Vec2(26, 10)));
					pSprites.push_back(blankCanvas->getTileAt(Vec2(27, 8)));
					pSprites.push_back(blankCanvas->getTileAt(Vec2(27, 9)));
					pSprites.push_back(blankCanvas->getTileAt(Vec2(27, 10)));

					//bottom painting
					pSprites.push_back(blankCanvas->getTileAt(Vec2(14, 18)));
					pSprites.push_back(blankCanvas->getTileAt(Vec2(14, 19)));
					pSprites.push_back(blankCanvas->getTileAt(Vec2(14, 20)));
					pSprites.push_back(blankCanvas->getTileAt(Vec2(15, 18)));
					pSprites.push_back(blankCanvas->getTileAt(Vec2(15, 19)));
					pSprites.push_back(blankCanvas->getTileAt(Vec2(15, 20)));
					pSprites.push_back(blankCanvas->getTileAt(Vec2(16, 18)));
					pSprites.push_back(blankCanvas->getTileAt(Vec2(16, 19)));
					pSprites.push_back(blankCanvas->getTileAt(Vec2(16, 20)));
				}
				opacity = 252;
				paintEvent.init = true;
			}
			if (pSprites[0]->getDisplayedOpacity() > 0)
			{
				for (unsigned int i = 0; i < pSprites.size(); i++)
				{
					pSprites[i]->setOpacity(opacity);
				}
				opacity -= 4;
			}
			else
			{
				pSprites.clear();
				paintEvent.phase2 = false;
				paintEvent.phase3 = true;
				paintEvent.init = false;
			}
		}
		else if (paintEvent.phase3 == true)
		{
			if (paintEvent.init == false) //if phase3 initilization hasnt happened yet
			{
				blankCanvas->setVisible(false); //only needed for visual-based server
				enqueueMessage(ServerMessage(19, 1, 0, 3)); //tell client to stop playing brushing sound
				enqueueMessage(ServerMessage(19, 1, 0, 1)); //client needs to hide blank canvas layer too
				serversam->setAnim("samdown");
				paintEvent.init = true;
			}
			//if sam has not yet reached spawn point
			if (serversam->getPositionY() > samInitPos.y)
			{
				serversam->setPositionY(serversam->getPositionY() - 2.0f);
				//paintEvent.eventTimer = 15;
			}
			else
			{
				paintEvent.phase3 = false;
				paintEvent.init = false;
				paintEvent.isActive = false;
				return false; //event is over
			}
		}
	}
	else
	{
		paintEvent.eventTimer--;
	}
	return true;
}

void ServerDemo::checkEnemyCollision(void)
{
	if (levelmanager.currentlevel != 1) {
		for (Player* p : players)
		{
			bool samHit = false;
			bool pteroHit = false;

			if (abs(serversam->getPositionX() - p->getPositionX()) < 5
				&& abs(serversam->getPositionY() - p->getPositionY()) < 5)
			{
				samHit = true;
			}
			if (pterodactyl->isHostile()
			 && p->getPositionX() > pterodactyl->getPositionX() - 12.5f
			 && p->getPositionX() < pterodactyl->getPositionX() + 12.5f
			 && p->getPositionY() > pterodactyl->getPositionY() - 55
			 && p->getPositionY() < pterodactyl->getPositionY() + 10)
			{
				pteroHit = true;
			}
			if (samHit == true || pteroHit == true)
			{
				//parse through player's wet tiles and erase
				for (unsigned int i = 0; i < p->paintedTiles.size();)
				{
					int a = p->paintedTiles[i].first;
					int b = p->paintedTiles[i].second;

					if (DRY_GRID[a][b] != dried)
					{
						PLAYER_GRID[a][b] = 0;
						//check if erased tile at [a][b] was correct, decrement tilescompleted if it was
						if (levelmanager.puzzle.checkTile(a, b))
						{
							levelmanager.puzzle.tileErased();
						}
						CURRENT_GRID[a][b] = 1;
						SPRITE_GRID[a][b]->setColor("clear");
						SPRITE_GRID[a][b]->refreshColor();

						//set player to inverted 'hit' animation
						std::string str = p->getAnim();
						log(str.c_str());
						//check if current animation is already a hit animation
						std::size_t found = str.find("hit");
						if (found == std::string::npos) //if NOT found
						{
							str.erase(1, 1);
							str.append("hit");
						}
						p->setAnim(str);
						log(str.c_str());

						p->paintedTiles.erase(p->paintedTiles.begin() + i);
						if (samHit == true)
						{
							enqueueMessage(ServerMessage(13, 0, 0, p->getPlayernum())); //tell client sam hit player
							samHit = false;
							sendmap = true;
						}
						else if (pteroHit == true)
						{
							enqueueMessage(ServerMessage(14, 0, 0, p->getPlayernum())); //tell client pterodactyl hit player
							pteroHit = false;
							sendmap = true;
						}
					}
					else
					{
						i++;
					}
				}
			}
		}
	}
}


void ServerDemo::dryTiles(void)
{
	//if (dry_y == CURRENT_GRID[0].size() - 1 && dry_x == CURRENT_GRID.size() - 1) {
	//	dry_y = 0;
	//	dry_x = 0;
	//}
	if (dry_x == CURRENT_GRID.size()) {
		dry_x = 0;
		dry_y++;
	}
	if (dry_y == CURRENT_GRID[0].size())
	{
		dry_y = 0;
	}
	if (dry_x <= DRY_GRID.size() && dry_y <= DRY_GRID[0].size()) //prevents out of bounds vector subscript
	{
		if (DRY_GRID[dry_x][dry_y] < dried) {
			DRY_GRID[dry_x][dry_y]++;
		}
		if (DRY_GRID[dry_x][dry_y] == dried && SPRITE_GRID[dry_x][dry_y]->isDry() == false) {
			if (SPRITE_GRID[dry_x][dry_y]->getColor() != "clear")
			{
				SPRITE_GRID[dry_x][dry_y]->setDry(true);
				SPRITE_GRID[dry_x][dry_y]->refreshColor(); //only useful for visual-based server
				//enqueueMessage(ServerMessage(18, (float)dry_x, (float)dry_y, 0)); //tells client a tile has dried

				std::pair<int, int> coords;
				coords.first = dry_x;
				coords.second = dry_y;
				std::vector<std::pair<int, int>>::iterator it;
				it = std::find(players[PLAYER_GRID[dry_x][dry_y] - 1]->paintedTiles.begin(), players[PLAYER_GRID[dry_x][dry_y] - 1]->paintedTiles.end(), coords);
				if (it != players[PLAYER_GRID[dry_x][dry_y] - 1]->paintedTiles.end()) //if dried tile found in player's paintedTiles vector
				{
					players[PLAYER_GRID[dry_x][dry_y] - 1]->paintedTiles.erase(it);
				}
				else
				{
					std::string str = "Error - dried tile at " + std::to_string(dry_x) + " " + std::to_string(dry_y) + " not found in players[" + std::to_string(PLAYER_GRID[dry_x][dry_y] - 1) + "]->paintedTiles";
					log(str.c_str());
				}
			}
		}
	}
	dry_x++;

	/*
	if (dry_time < 15) {
	dry_time++;
	}
	else {
	int a = (rand() % DRY_GRID.size());
	int b = (rand() % DRY_GRID[0].size());
	if (SPRITE_GRID[a][b]->getColor() != "clear")
	{
	DRY_GRID[a][b] = 1;
	SPRITE_GRID[a][b]->setDry(true); //only useful for visual-based server
	SPRITE_GRID[a][b]->refreshColor(); //only useful for visual-based server
	//enqueueMessage(ServerMessage(18, (float)a, (float)b, 0)); //tells client a tile has dried
	dry_time = 0;
	}
	} //end of drying code
	*/
}

void ServerDemo::checkSolved(void)
{
	if (solved_timer_start == true)
	{
		if (solved_timer <= 0)
		{
			if (levelmanager.isLastLevel())
			{
				enqueueMessage(ServerMessage(15, 0, 0, 0)); //gameover
				loadLevel(1);
			}
			else
			{
				loadLevel(levelmanager.currentlevel + 1);
			}
			solved_timer_start = false;
			sendmap = true;
		}
		else
		{
			solved_timer--;
		}
	}
	if (solved_timer_start == false && levelmanager.puzzle.isSolved())
	{
		solved_timer_start = true;
		solved_timer = 180;
		for (unsigned int i = 0; i < players.size(); i++)
		{
			players[i]->setColor("");
			players[i]->setAnim("");

		}
		pterodactyl->setAnim("");
		serversam->setAnim("");
		enqueueMessage(ServerMessage(18,0,0,0)); //tell client to start victory event
	}
}

void ServerDemo::updateIdleAnims(void)
{
	idle1--;
	idle2--;
	idle3--;
	idle4--;
	if (idle1 < 0) {
		player1->setAnim("p1idle");
		idle1++;
	}
	if (idle2 < 0) {
		idle2++;
		player2->setAnim("p2idle");
	}
	if (idle3 < 0) {
		player3->setAnim("p3idle");
		idle3++;
	}
	if (idle4 < 0) {
		player4->setAnim("p4idle");
		idle4++;
	}
}

ServerDemo::~ServerDemo()
{
	log("ServerDemoDeconstructor");

	if (mytcpserverp)
	{
		delete mytcpserverp;
	}

	if (io_service_p)
	{
		delete io_service_p;
	}

}