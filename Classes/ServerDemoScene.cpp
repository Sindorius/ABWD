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

	levelmanager.changeLevel(1);
	addChild(levelmanager.levelmap, -1000);

	blockage = levelmanager.levelmap->getLayer("Collision");
	blockage->setVisible(false);

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

	bucketlayer = levelmanager.levelmap->getLayer("Paintbuckets");

	player1 = Player::create(1);
	player1->setPlayernum(1);
	player1->getTexture()->setAliasTexParameters();
	player1->setPosition(Vec2(playerOneSP["x"].asInt(), playerOneSP["y"].asInt()));
	player1->debugDraw(true);
	player1->setAnchorPoint(Vec2(0.5, 0.0));
	p1pos = player1->getPosition();
	addChild(player1, 0);

	player2 = Player::create(2);
	player2->setPlayernum(2);
	player2->getTexture()->setAliasTexParameters();
	player2->setPosition(Vec2(playerTwoSP["x"].asInt(), playerTwoSP["y"].asInt()));
	p2pos = player2->getPosition();
	player2->debugDraw(true);
	player2->setAnchorPoint(Vec2(0.5, 0.0));
	addChild(player2, 0);

	player3 = Player::create(3);
	player3->setPlayernum(3);
	player3->getTexture()->setAliasTexParameters();
	player3->setPosition(Vec2(playerThreeSP["x"].asInt(), playerThreeSP["y"].asInt()));
	p3pos = player3->getPosition();
	player3->setAnchorPoint(Vec2(0.5, 0.0));
	addChild(player3, 0);

	player4 = Player::create(4);
	player4->setPlayernum(4);
	player4->getTexture()->setAliasTexParameters();
	player4->setPosition(Vec2(playerFourSP["x"].asInt(), playerFourSP["y"].asInt()));
	player4->setAnchorPoint(Vec2(0.5, 0.0));
	p4pos = player4->getPosition();
	addChild(player4, 0);

	players.push_back(player1);
	players.push_back(player2);
	players.push_back(player3);
	players.push_back(player4);

	villain = Villain::create();
	villain->getTexture()->setAliasTexParameters();
	villain->setPosition(Vec2(250, 150));
	villain->setAnchorPoint(Vec2(0.5, 0.0));
	vpos = villain->getPosition();
	addChild(villain, 0);

	pterodactyl = Pterodactyl::create();
	pterodactyl->getTexture()->setAliasTexParameters();
	pterodactyl->setPosition(Vec2(50, 50));
	pterodactyl->setAnchorPoint(Vec2(0.5, 0.0));
	ppos = pterodactyl->getPosition();
	addChild(pterodactyl, 0);

	villain->linkPtera(pterodactyl);

	for (Sprite* s : levelmanager.levelsprites)
	{
		addChild(s, -999);
	}

	// Should also be part of SpawnObject layer if possible
	//Sprite* wallpainting = Sprite::create("res/sprites/objects/key_framed.png");
	//wallpainting->getTexture()->setAliasTexParameters();
	//wallpainting->setPosition(Vec2(320, 320));
	//wallpainting->setScale(1.0f);
	//addChild(wallpainting, -999);


	// Initialize painting area 
	setupPaintTiles();

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


void ServerDemo::menuCloseCallback(Ref* pSender)
{
	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}


void ServerDemo::update(float dt)
{
	CCLOG("UPDATE DT");
	CCLOG(std::to_string(dt).c_str());

	io_service_p->poll();
	idle1--;
	idle2--;
	idle3--;
	idle4--;
	if (idle1 < 0) {
		players[0]->setAnim("p1idle");
		idle1++;
	}
	if (idle2 < 0) {
		idle2++;
		players[1]->setAnim("p2idle");
	}
	if (idle3 < 0) {
		players[2]->setAnim("p3idle");
		idle3++;
	}
	if (idle4 < 0) {
		players[3]->setAnim("p4idle");
		idle4++;
	}
	//player1->setPosition(p1pos);
	//player2->setPosition(p2pos);
	//player3->setPosition(p3pos);
	//player4->setPosition(p4pos);
	villain->setPriority(levelmanager.puzzle.whichplayertilesvector);
	villain->runAI(&players);
	

	ServerPositionPacket p(
		pterodactyl->getPositionX(), pterodactyl->getPositionY(), animationmanager.charFromString(pterodactyl->getAnim()),
		villain->getPositionX(), villain->getPositionY(), animationmanager.charFromString(villain->getAnim()),
		player1->getPositionX(), player1->getPositionY(), animationmanager.charFromString(player1->getAnim()),
		player2->getPositionX(), player2->getPositionY(), animationmanager.charFromString(player2->getAnim()),
		player3->getPositionX(), player3->getPositionY(), animationmanager.charFromString(player3->getAnim()),
		player4->getPositionX(), player4->getPositionY(), animationmanager.charFromString(player4->getAnim()), levelmanager.puzzle.currenttilevector);

	player1->setZOrder(-player1->getPositionY());
	player2->setZOrder(-player2->getPositionY());
	player3->setZOrder(-player3->getPositionY());
	player4->setZOrder(-player4->getPositionY());
	villain->setZOrder(-villain->getPositionY());

	mytcpserverp->sendPacket(p);

	// Villain checks if she's on a player, messes everything up if she's on them
	for (Player* p : players)
	{
		if (abs(villain->getPositionX() - p->getPositionX()) < 5 && abs(villain->getPositionY() - p->getPositionY()) < 5)
		{
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

		if (pterodactyl->isHostile() && abs(pterodactyl->getPositionX() - p->getPositionX()) < 5 && abs(pterodactyl->getPositionY() - p->getPositionY()) < 5)
		{
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

	// Move them all to the top if they've won
	if (levelmanager.puzzle.isSolved())
	{
		loadLevel(2);
	}


}

ServerDemo::~ServerDemo()
{
	CCLOG("ServerDemoDeconstructor");
	if (io_service_p)
	{
		delete io_service_p;
	}

	if (mytcpserverp)
	{
		delete mytcpserverp;
	}

}



void ServerDemo::processPlayerPacket(PlayerInputPacket p)
{
	float dxmove = p.dx;
	float dymove = p.dy;
	auto playerPos = players[p.playernum - 1]->getPosition();
	std::string newcolor = "none";


	// Convert the players position into tile coordinates
	int testx = (playerPos.x + p.dx) / (levelmanager.levelmap->getTileSize().width);
	int testy = ((levelmanager.levelmap->getMapSize().height * levelmanager.levelmap->getTileSize().height) - playerPos.y - p.dy) / (levelmanager.levelmap->getTileSize().height);
	CCPoint tileCoord = CCPoint(testx, testy);

	int bkTile = blockage->getTileGIDAt(tileCoord);

	if (bkTile)
	{

		auto tilemapvals = levelmanager.levelmap->getPropertiesForGID(bkTile).asValueMap();

		if (!tilemapvals.empty())
		{
			auto w = tilemapvals["Collidable"].asString();

			if ("true" == w) {
				dxmove = -dxmove * 2;
				dymove = -dymove * 2;
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
		;
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



//void ServerDemo::space(int playernum) 
void ServerDemo::space(int playernum, cocos2d::CCPoint tileCoord, float dxmove, float dymove)
{

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// NEW CODE ADDED
	// Check to see if their position is where there is a bucket and assign that color
	std::string newcolor = "none";


	if (tileCoord.x >= 0 && tileCoord.x <= 25 && tileCoord.y >= 0 && tileCoord.y <= 14)
	{
		int bTile = bucketlayer->getTileGIDAt(tileCoord);

		if (bTile)
		{
			auto tilemapvals = levelmanager.levelmap->getPropertiesForGID(bTile).asValueMap();

			if (!tilemapvals.empty())
			{
				auto r = tilemapvals["Red"].asString();
				auto b = tilemapvals["Blue"].asString();
				auto y = tilemapvals["Yellow"].asString();
				auto o = tilemapvals["Orange"].asString();
				auto blk = tilemapvals["Black"].asString();

				if ("true" == r)
				{
					dxmove = -dxmove * 2;
					dymove = -dymove * 2;
					newcolor = "red";
				}
				if ("true" == b)
				{
					dxmove = -dxmove * 2;
					dymove = -dymove * 2;
					newcolor = "blue";
				}
				if ("true" == y) {
					dxmove = -dxmove * 2;
					dymove = -dymove * 2;
					newcolor = "yellow";
				}
				if ("true" == o) {
					dxmove = -dxmove * 2;
					dymove = -dymove * 2;
					newcolor = "orange";
				}
				if ("true" == blk) {
					dxmove = -dxmove * 2;
					dymove = -dymove * 2;
					newcolor = "black";
				}
			}
		}

		if (newcolor != "none")
		{
			players[playernum - 1]->setColor(newcolor);
		}


	}
	// end Check to see if their position is where there is a bucket and assign that color

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

				levelmanager.puzzle.whichplayertilesvector[i][j] = playernum;
			}
		}
	}
}

void ServerDemo::loadLevel(int level)
{
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
	blockage->setVisible(false);
	bucketlayer = levelmanager.levelmap->getLayer("Paintbuckets");
	

	if (spawnObjs == NULL) {
		CCLOG("TMX map has SpawnObjects layer");
	}

	for (Sprite* s : levelmanager.levelsprites)
	{
		addChild(s, -999);
	}

	setupPaintTiles();

	if (level == 3)
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
		loadLevel(1);
	break;
	case EventKeyboard::KeyCode::KEY_CAPITAL_S:
	case EventKeyboard::KeyCode::KEY_S:
		loadLevel(2);
	break;
	case EventKeyboard::KeyCode::KEY_CAPITAL_P:
	case EventKeyboard::KeyCode::KEY_P:
		loadLevel(3);
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