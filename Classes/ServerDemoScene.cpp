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
	CCLOG("from animint");
	CCLOG(std::to_string(animint).c_str());
	int refreshrate = glview->getRunningRefreshRate();
	if(refreshrate == 59)
	{
		refreshrate = 60;
	}
	if (refreshrate == 119)
	{
		refreshrate = 120;
	}
	CCLOG("from get refresh rate");
	CCLOG(std::to_string(refreshrate).c_str());
	int newswapinterval = refreshrate*animint;
	if(newswapinterval < 1)
	{
		newswapinterval = 1;
	}
	swapframes = newswapinterval;
	swapframecounter = newswapinterval;

	CCLOG("from newswapinterval");
	CCLOG(std::to_string(newswapinterval).c_str());
	*/

	levelmanager.changeLevel(1);
	// Check to see if there is an object layer 
	spawnObjs = levelmanager.levelmap->objectGroupNamed("SpawnObjects");

	if (spawnObjs == NULL) {
		CCLOG("TMX map has SpawnObjects layer");
	}

	// Player spawn coordinates depend on tiled map
	ValueMap playerOneSP = spawnObjs->objectNamed("P1spawnPoint");
	ValueMap playerTwoSP = spawnObjs->objectNamed("P2spawnPoint");
	ValueMap playerThreeSP = spawnObjs->objectNamed("P3spawnPoint");
	ValueMap playerFourSP = spawnObjs->objectNamed("P4spawnPoint");
		
	player1 = Player::create(1);
	player1->setPlayernum(1);
	player1->getTexture()->setAliasTexParameters();
	player1->setPosition(Vec2(playerOneSP["x"].asInt(), playerOneSP["y"].asInt()));
	player1->debugDraw(true);
	player1->setAnchorPoint(Vec2(0.5, 0.0));
	addChild(player1, 0);

	player2 = Player::create(2);
	player2->setPlayernum(2);
	player2->getTexture()->setAliasTexParameters();
	player2->setPosition(Vec2(playerTwoSP["x"].asInt(), playerTwoSP["y"].asInt()));
	player2->debugDraw(true);
	player2->setAnchorPoint(Vec2(0.5, 0.0));
	addChild(player2, 0);

	player3 = Player::create(3);
	player3->setPlayernum(3);
	player3->getTexture()->setAliasTexParameters();
	player3->setPosition(Vec2(playerThreeSP["x"].asInt(), playerThreeSP["y"].asInt()));
	player3->setAnchorPoint(Vec2(0.5, 0.0));
	addChild(player3, 0);

	player4 = Player::create(4);
	player4->setPlayernum(4);
	player4->getTexture()->setAliasTexParameters();
	player4->setPosition(Vec2(playerFourSP["x"].asInt(), playerFourSP["y"].asInt()));
	player4->setAnchorPoint(Vec2(0.5, 0.0));
	addChild(player4, 0);

	players.push_back(player1);
	players.push_back(player2);
	players.push_back(player3);
	players.push_back(player4);

	//player1->setVisible(false);
	//player2->setVisible(false);
	//player3->setVisible(false);
	//player4->setVisible(false);

	serversam = ServerSam::create(this);
	serversam->getTexture()->setAliasTexParameters();
	serversam->setPosition(Vec2(-250, -150));
	serversam->setAnchorPoint(Vec2(0.5, 0.0));
	addChild(serversam, 0);

	pterodactyl = Pterodactyl::create();
	pterodactyl->getTexture()->setAliasTexParameters();
	pterodactyl->setPosition(Vec2(50, 50));
	pterodactyl->setAnchorPoint(Vec2(0.5, 0.0));
	addChild(pterodactyl, 0);

	candy = Candy::create();
	candy->getTexture()->setAliasTexParameters();
	candy->setPosition(Vec2(-1000, -1000));
	candy->setAnchorPoint(Vec2(0.5, 0.0));
	addChild(candy, 0);
	
	serversam->linkPtera(pterodactyl);
	serversam->linkCandy(candy);

	loadLevel(1);

	std::ifstream is("config.json");
	cereal::JSONInputArchive configloader(is);
	setupdata = ConfigFileInput();
	configloader(setupdata);
	is.close();

	CCLOG("port is");
	CCLOG(std::to_string(setupdata.port).c_str());

	try
	{
		CCLOG("intry");
		//boost::asio::io_service io_service;
		io_service_p = new boost::asio::io_service;
		CCLOG("madepastioservice");
		mytcpserverp = new TCPServer(*io_service_p, setupdata.port, this);
		CCLOG("madepastserver");
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
	//CCLOG("UPDATE DT");
	//CCLOG(std::to_string(dt).c_str());
	io_service_p->poll();
	
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
	//player1->setPosition(p1pos);
	//player2->setPosition(p2pos);
	//player3->setPosition(p3pos);
	//player4->setPosition(p4pos);

	if (levelmanager.currentlevel != 1) 
	{
		serversam->setPriority(levelmanager.puzzle.whichplayertilesvector, levelmanager.puzzle.drytilevector);
		serversam->runAI(&players);
	}

	player1->setZOrder(-player1->getPositionY());
	player2->setZOrder(-player2->getPositionY());
	player3->setZOrder(-player3->getPositionY());
	player4->setZOrder(-player4->getPositionY());
	serversam->setZOrder(-serversam->getPositionY());
	pterodactyl->setZOrder(-pterodactyl->getPositionY());

	if (levelmanager.currentlevel != 1) {
		if (dry_time < 15) {
			dry_time++;
		}
		else {
			int a = (rand() % levelmanager.puzzle.drytilevector.size());
			int b = (rand() % levelmanager.puzzle.drytilevector[0].size());
			levelmanager.puzzle.drytilevector[a][b] = 1;
			dry_time = 0;
		}
		for (Player* p : players)
		{
			if (abs(serversam->getPositionX() - p->getPositionX()) < 5 && abs(serversam->getPositionY() - p->getPositionY()) < 5)
			{
				sendmap = true;
				enqueueMessage(ServerMessage(13, 0, 0, p->getPlayernum())); //SFX triger for sam hitting player
				for (int i = 0; i < levelmanager.puzzle.currenttilevector.size(); i++)
				{
					for (int j = 0; j < levelmanager.puzzle.currenttilevector[i].size(); j++)
					{
						if (levelmanager.puzzle.whichplayertilesvector[i][j] == p->getPlayernum() && levelmanager.puzzle.drytilevector[i][j] != 1)
						{
							levelmanager.puzzle.whichplayertilesvector[i][j] = 0;
							levelmanager.puzzle.currenttilevector[i][j] = 1;
							tilespritevector[i][j]->setColor("clear");
							tilespritevector[i][j]->refreshColor();

						}
					}
				}

			}

			if (pterodactyl->isHostile() && abs(pterodactyl->getPositionX() + 12 - p->getPositionX()) < 10 && abs(pterodactyl->getPositionY() - p->getPositionY()) < 10 )
			{
				sendmap = true;
				enqueueMessage(ServerMessage(14, 0, 0, p->getPlayernum())); //SFX triger for pterodactyl hitting player
				for (int i = 0; i < levelmanager.puzzle.currenttilevector.size(); i++)
				{
					for (int j = 0; j < levelmanager.puzzle.currenttilevector[i].size(); j++)
					{
						if (levelmanager.puzzle.whichplayertilesvector[i][j] == p->getPlayernum() && levelmanager.puzzle.drytilevector[i][j] != 1)
						{
							levelmanager.puzzle.whichplayertilesvector[i][j] = 0;
							levelmanager.puzzle.currenttilevector[i][j] = 1;
							tilespritevector[i][j]->setColor("clear");
							tilespritevector[i][j]->refreshColor();

						}
					}
				}

			}
		}
	}

	/*
	// serversam checks if she's on a player, messes everything up if she's on them
	for (Player* p : players)
	{
		if (abs(serversam->getPositionX() - p->getPositionX()) < 5 && abs(serversam->getPositionY() - p->getPositionY()) < 5)
		{
			sendmap = true;
			for (int i = 0; i < levelmanager.puzzle.currenttilevector.size(); i++)
			{
				for (int j = 0; j < levelmanager.puzzle.currenttilevector[i].size(); j++)
				{
					if (levelmanager.puzzle.whichplayertilesvector[i][j] == p->getPlayernum())
					{
						levelmanager.puzzle.whichplayertilesvector[i][j] = 0;
						levelmanager.puzzle.currenttilevector[i][j] = 1;
						tilespritevector[i][j]->setColor("clear");
						tilespritevector[i][j]->refreshColor();
						
					}
				}
			}

		}

		if (pterodactyl->isHostile() && abs(pterodactyl->getPositionX() + 12 - p->getPositionX()) < 10 && abs(pterodactyl->getPositionY() - p->getPositionY()) < 10)
		{
			sendmap = true;
			for (int i = 0; i < levelmanager.puzzle.currenttilevector.size(); i++)
			{
				for (int j = 0; j < levelmanager.puzzle.currenttilevector[i].size(); j++)
				{
					if (levelmanager.puzzle.whichplayertilesvector[i][j] == p->getPlayernum())
					{
						levelmanager.puzzle.whichplayertilesvector[i][j] = 0;
						levelmanager.puzzle.currenttilevector[i][j] = 1;
						tilespritevector[i][j]->setColor("clear");
						tilespritevector[i][j]->refreshColor();
						
					}
				}
			}

		}
	}
	*/


	if (levelmanager.puzzle.isSolved())
	{
		if (levelmanager.currentlevel == 1)
		{
			loadLevel(2);
		}
		else if (levelmanager.currentlevel == 2)
		{
			loadLevel(3);
		}
		else if (levelmanager.currentlevel == 3)
		{
			loadLevel(4);
		}
		else if (levelmanager.currentlevel == 4)
		{
			servermessagequeue.emplace_back(ServerMessage(15, 0, 0, 0));
			loadLevel(1);
		}

		sendmap = true;
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
	}
	if (sessionmapped[2])
	{
		returnchar = returnchar | p2mask;
	}if (sessionmapped[3])
	{
		returnchar = returnchar | p3mask;
	}if (sessionmapped[4])
	{
		returnchar = returnchar | p4mask;
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
	CCPoint tileCoord = CCPoint(testx, testy);
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



void ServerDemo::space(int playernum, cocos2d::CCPoint tileCoord, float dxmove, float dymove)
{

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// NEW CODE ADDED
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

				// ADDED THIS
				auto w = tilemapvals["White"].asString();
				auto gy1 = tilemapvals["Grey1"].asString();
				auto gy2 = tilemapvals["Grey2"].asString();
				auto r2 = tilemapvals["Red2"].asString();
				auto p = tilemapvals["Purple1"].asString();
				auto r1 = tilemapvals["Red1"].asString();
				////////////////////

				if ("true" == r)
				{
					dxmove = -dxmove * 2;
					dymove = -dymove * 2;
					newcolor = "red";
					servermessagequeue.emplace_back(ServerMessage(16, playernum, 0, 2));
				}
				if ("true" == b)
				{
					dxmove = -dxmove * 2;
					dymove = -dymove * 2;
					newcolor = "blue";
					servermessagequeue.emplace_back(ServerMessage(16, playernum, 0, 3));
				}
				if ("true" == y) {
					dxmove = -dxmove * 2;
					dymove = -dymove * 2;
					newcolor = "yellow";
					servermessagequeue.emplace_back(ServerMessage(16, playernum, 0, 4));
				}
				if ("true" == o) {
					dxmove = -dxmove * 2;
					dymove = -dymove * 2;
					newcolor = "orange";
					servermessagequeue.emplace_back(ServerMessage(16, playernum, 0, 5));
				}
				if ("true" == blk) {
					dxmove = -dxmove * 2;
					dymove = -dymove * 2;
					newcolor = "black";
					servermessagequeue.emplace_back(ServerMessage(16, playernum, 0, 6));
				}

				if ("true" == b2) {
					dxmove = -dxmove * 2;
					dymove = -dymove * 2;
					newcolor = "blue2";
					servermessagequeue.emplace_back(ServerMessage(16, playernum, 0, 7));
				}
				if ("true" == b3) {
					dxmove = -dxmove * 2;
					dymove = -dymove * 2;
					newcolor = "blue3";
					servermessagequeue.emplace_back(ServerMessage(16, playernum, 0, 8));
				}
				if ("true" == g1) {
					dxmove = -dxmove * 2;
					dymove = -dymove * 2;
					newcolor = "green1";
					servermessagequeue.emplace_back(ServerMessage(16, playernum, 0, 9));
				}
				if ("true" == g2) {
					dxmove = -dxmove * 2;
					dymove = -dymove * 2;
					newcolor = "green2";
					servermessagequeue.emplace_back(ServerMessage(16, playernum, 0, 10));
				}
				if ("true" == g3) {
					dxmove = -dxmove * 2;
					dymove = -dymove * 2;
					newcolor = "green3";
					servermessagequeue.emplace_back(ServerMessage(16, playernum, 0, 11));
				}
				///// ADDED THIS
				if ("true" == w) {
					dxmove = -dxmove * 2;
					dymove = -dymove * 2;
					newcolor = "white";
					servermessagequeue.emplace_back(ServerMessage(16, playernum, 0, 12));
				}
				if ("true" == gy1) {
					dxmove = -dxmove * 2;
					dymove = -dymove * 2;
					newcolor = "grey1";
					servermessagequeue.emplace_back(ServerMessage(16, playernum, 0, 13));
				}
				if ("true" == gy2) {
					dxmove = -dxmove * 2;
					dymove = -dymove * 2;
					newcolor = "grey2";
					servermessagequeue.emplace_back(ServerMessage(16, playernum, 0, 14));
				}
				if ("true" == r2) {
					dxmove = -dxmove * 2;
					dymove = -dymove * 2;
					newcolor = "red2";
					servermessagequeue.emplace_back(ServerMessage(16, playernum, 0, 15));
				}
				if ("true" == p) {
					dxmove = -dxmove * 2;
					dymove = -dymove * 2;
					newcolor = "purple1";
					servermessagequeue.emplace_back(ServerMessage(16, playernum, 0, 16));
				}
				if ("true" == r1) {
					dxmove = -dxmove * 2;
					dymove = -dymove * 2;
					newcolor = "red1";
					servermessagequeue.emplace_back(ServerMessage(16, playernum, 0, 17));
				}
				//// ADDED THIS
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
	if (level == 5)
	{
		servermessagequeue.emplace_back(ServerMessage(15, 0, 0, 0));
		loadLevel(1);
		return;
	}
	else if (level == 1) {
		serversam->pteraOff();
		serversam->candyOff();
	}
	else if (level == 2) {
		serversam->pteraOff();
		serversam->candyOff();
	}
	else if (level == 3) {
		serversam->pteraOff();
		serversam->candyOn();
	}
	else if (level == 4) {
		serversam->pteraOn();
		serversam->candyOn();
	}

	
	
	servermessagequeue.emplace_back(ServerMessage(10, 0, 0, level));

	for (Sprite* s : levelmanager.levelsprites)
	{
		removeChild(s);
	}

	for (int i = 0; i < tilespritevector.size(); i++)
	{
		for (int j = 0; j < tilespritevector[i].size(); j++)
		{
			removeChild(tilespritevector[i][j]);
		}
	}
		
	removeChild(levelmanager.levelmap);
	
	levelmanager.changeLevel(level);

	addChild(levelmanager.levelmap, -1000);

	// Check to see if there is an object layer 
	spawnObjs = levelmanager.levelmap->objectGroupNamed("SpawnObjects");

	blockage = levelmanager.levelmap->getLayer("Collision");
	if (blockage != NULL)
	{
		blockage->setVisible(false);
	}
	bucketlayer = levelmanager.levelmap->getLayer("Paintbuckets");
	serversam->setPosition(Vec2(250, 150));
	

	if (spawnObjs == NULL) {
		CCLOG("TMX map has no SpawnObjects layer");
	}
	else
	{
		ValueMap playerOneSP = spawnObjs->objectNamed("P1spawnPoint");
		ValueMap playerTwoSP = spawnObjs->objectNamed("P2spawnPoint");
		ValueMap playerThreeSP = spawnObjs->objectNamed("P3spawnPoint");
		ValueMap playerFourSP = spawnObjs->objectNamed("P4spawnPoint");
		player1->setPosition(Vec2(playerOneSP["x"].asInt(), playerOneSP["y"].asInt()));
		player2->setPosition(Vec2(playerTwoSP["x"].asInt(), playerTwoSP["y"].asInt()));
		player3->setPosition(Vec2(playerThreeSP["x"].asInt(), playerThreeSP["y"].asInt()));
		player4->setPosition(Vec2(playerFourSP["x"].asInt(), playerFourSP["y"].asInt()));

	}

	for (Sprite* s : levelmanager.levelsprites)
	{
		addChild(s, -999);
	}

	setupPaintTiles();

	if (level == 3 || level == 4)
	{
		this->setScale(.6f);
	}
	else
	{
		this->setScale(1.0f);
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
		loadLevel(5);
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

	tilespritevector.resize(levelmanager.puzzle.currenttilevector.size());
	for (int i = 0; i < tilespritevector.size(); i++)
	{
		tilespritevector[i].resize(levelmanager.puzzle.currenttilevector[i].size());
	}
	
	for (int i = 0; i < tilespritevector.size(); i++)
	{
		for (int j = 0; j < tilespritevector[i].size(); j++)
		{
			tilespritevector[i][j] = PaintTile::create();
			tilespritevector[i][j]->setPosition(24 * j + levelmanager.tilestartpoint.x, 24 * i + levelmanager.tilestartpoint.y);
			//tilespritevector[i][j]->setScale(1);
			tilespritevector[i][j]->debugDraw(true);
			addChild(tilespritevector[i][j], -999);
		}
	}

}

void ServerDemo::updatePaintTiles(int playernum)
{
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// optimize this, might not need to go through each tile here.
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	for (int i = 0; i < levelmanager.puzzle.currenttilevector.size(); i++)
	{
		for (int j = 0; j < levelmanager.puzzle.currenttilevector[i].size(); j++)
		{
			if (players[playernum - 1]->getPositionX() > tilespritevector[i][j]->getPositionX() - 12 && players[playernum - 1]->getPositionX() < tilespritevector[i][j]->getPositionX() + 12 && players[playernum - 1]->getPositionY() > tilespritevector[i][j]->getPositionY() - 12 && players[playernum - 1]->getPositionY() < tilespritevector[i][j]->getPositionY() + 12)
			{
				tilespritevector[i][j]->setColor(players[playernum - 1]->getColor());
				tilespritevector[i][j]->refreshColor();
				levelmanager.puzzle.drytilevector[i][j] = 0;
				if (players[playernum - 1]->getColor() == "red")
				{
					if (levelmanager.puzzle.compareTile(i, j, 2))
					{
						levelmanager.puzzle.currenttilevector[i][j] = 2;
					}
					else {
						levelmanager.puzzle.currenttilevector[i][j] = 20;
					}
				}
				if (players[playernum - 1]->getColor() == "blue")
				{
					if (levelmanager.puzzle.compareTile(i, j, 3))
					{
						levelmanager.puzzle.currenttilevector[i][j] = 3;
					}
					else {
						levelmanager.puzzle.currenttilevector[i][j] = 30;
					}
				}
				if (players[playernum - 1]->getColor() == "yellow")
				{
					if (levelmanager.puzzle.compareTile(i, j, 4))
					{
						levelmanager.puzzle.currenttilevector[i][j] = 4;
					}
					else {
						levelmanager.puzzle.currenttilevector[i][j] = 40;
					}
				}
				if (players[playernum - 1]->getColor() == "orange")
				{
					if (levelmanager.puzzle.compareTile(i, j, 5))
					{
						levelmanager.puzzle.currenttilevector[i][j] = 5;
					}
					else {
						levelmanager.puzzle.currenttilevector[i][j] = 50;
					}
				}
				if (players[playernum - 1]->getColor() == "black")
				{
					if (levelmanager.puzzle.compareTile(i, j, 6))
					{
						levelmanager.puzzle.currenttilevector[i][j] = 6;
					}
					else {
						levelmanager.puzzle.currenttilevector[i][j] = 60;
					}
				}
				////////////////////////////// NEW CODE HERE
				if (players[playernum - 1]->getColor() == "blue2")
				{
					if (levelmanager.puzzle.compareTile(i, j, 7))
					{
						levelmanager.puzzle.currenttilevector[i][j] = 7;
					}
					else {
						levelmanager.puzzle.currenttilevector[i][j] = 70;
					}
				}
				if (players[playernum - 1]->getColor() == "blue3")
				{
					if (levelmanager.puzzle.compareTile(i, j, 8))
					{
						levelmanager.puzzle.currenttilevector[i][j] = 8;
					}
					else {
						levelmanager.puzzle.currenttilevector[i][j] = 71;
					}
				}
				if (players[playernum - 1]->getColor() == "green1")
				{
					if (levelmanager.puzzle.compareTile(i, j, 9))
					{
						levelmanager.puzzle.currenttilevector[i][j] = 9;
					}
					else {
						levelmanager.puzzle.currenttilevector[i][j] = 72;
					}
				}
				if (players[playernum - 1]->getColor() == "green2")
				{
					if (levelmanager.puzzle.compareTile(i, j, 10))
					{
						levelmanager.puzzle.currenttilevector[i][j] = 10;
					}
					else {
						levelmanager.puzzle.currenttilevector[i][j] = 73;
					}
				}
				if (players[playernum - 1]->getColor() == "green3")
				{
					if (levelmanager.puzzle.compareTile(i, j, 11))
					{
						levelmanager.puzzle.currenttilevector[i][j] = 11;
					}
					else {
						levelmanager.puzzle.currenttilevector[i][j] = 74;
					}
				}
				if (players[playernum - 1]->getColor() == "white")
				{
					if (levelmanager.puzzle.compareTile(i, j, 12))
					{
						levelmanager.puzzle.currenttilevector[i][j] = 12;
					}
					else {
						levelmanager.puzzle.currenttilevector[i][j] = 75;
					}
				}
				if (players[playernum - 1]->getColor() == "grey1")
				{
					if (levelmanager.puzzle.compareTile(i, j, 13))
					{
						levelmanager.puzzle.currenttilevector[i][j] = 13;
					}
					else {
						levelmanager.puzzle.currenttilevector[i][j] = 76;
					}
				}
				if (players[playernum - 1]->getColor() == "grey2")
				{
					if (levelmanager.puzzle.compareTile(i, j, 14))
					{
						levelmanager.puzzle.currenttilevector[i][j] = 14;
					}
					else {
						levelmanager.puzzle.currenttilevector[i][j] = 77;
					}
				}
				if (players[playernum - 1]->getColor() == "red2")
				{
					if (levelmanager.puzzle.compareTile(i, j, 15))
					{
						levelmanager.puzzle.currenttilevector[i][j] = 15;
					}
					else {
						levelmanager.puzzle.currenttilevector[i][j] = 78;
					}
				}
				if (players[playernum - 1]->getColor() == "purple1")
				{
					if (levelmanager.puzzle.compareTile(i, j, 16))
					{
						levelmanager.puzzle.currenttilevector[i][j] = 16;
					}
					else {
						levelmanager.puzzle.currenttilevector[i][j] = 79;
					}
				}
				if (players[playernum - 1]->getColor() == "red1")
				{
					if (levelmanager.puzzle.compareTile(i, j, 17))
					{
						levelmanager.puzzle.currenttilevector[i][j] = 17;
					}
					else {
						levelmanager.puzzle.currenttilevector[i][j] = 80;
					}
				}
				/////////////////////
				sendmap = true;
				levelmanager.puzzle.whichplayertilesvector[i][j] = playernum;
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
			player4->getPositionX(), player4->getPositionY(), animationmanager.charFromString(player4->getAnim()), levelmanager.puzzle.currenttilevector, servermessagequeue);
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

void ServerDemo::addPlayerToGame(int playernum)
{
	/*
	if (playernum == 1)
	{
		player1->setVisible(true);
		players.push_back(player1);
	}
	else if (playernum == 2) 
	{
		player2->setVisible(true);
		players.push_back(player2);
	}
	else if (playernum == 3)
	{
		player3->setVisible(true);
		players.push_back(player3);
	}
	else if (playernum == 4)
	{
		player4->setVisible(true);
		players.push_back(player4);
	}
	*/
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


ServerDemo::~ServerDemo()
{
	CCLOG("ServerDemoDeconstructor");

	if (mytcpserverp)
	{
		delete mytcpserverp;
	}

	if (io_service_p)
	{
		delete io_service_p;
	}

}