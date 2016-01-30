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
    if ( !Layer::init() )
    {
        return false;
    }
    
	std::string file = "res//maps//happy_sun_paint.tmx";
	auto str = String::createWithContentsOfFile(FileUtils::getInstance()->fullPathForFilename(file.c_str()).c_str());
	//tileMap = cocos2d::CCTMXTiledMap::createWithXML(str->getCString(), "");

	//tileMap = cocos2d::experimental::TMXTiledMap::createWithXML(str->getCString(), "");
	////////////////////////////////////////////////////////////////////////////////////////////////// NEW ADDED CODE
	tileMap = cocos2d::TMXTiledMap::createWithXML(str->getCString(), "");
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	addChild(tileMap, -1000);

	////////////////////////////////////////////////////////////////////////////////////////////////// NEW ADDED CODE
	blockage = tileMap->getLayer("Collision");
	blockage->setVisible(false);

	// Check to see if there is an object layer 
	spawnObjs = tileMap->objectGroupNamed("SpawnObjects");

	if (spawnObjs == NULL) {
		CCLOG("TMX map has SpawnObjects layer");
	}

	// Player spawn coordinates depend on tiled map
	ValueMap playerOneSP = spawnObjs->objectNamed("P1spawnPoint");
	int p1X = playerOneSP["x"].asInt();
	int p1Y = playerOneSP["y"].asInt();

	ValueMap playerTwoSP = spawnObjs->objectNamed("P2spawnPoint");
	int p2X = playerTwoSP["x"].asInt();
	int p2Y = playerTwoSP["y"].asInt();

	ValueMap playerThreeSP = spawnObjs->objectNamed("P3spawnPoint");
	int p3X = playerThreeSP["x"].asInt();
	int p3Y = playerThreeSP["y"].asInt();

	ValueMap playerFourSP = spawnObjs->objectNamed("P4spawnPoint");
	int p4X = playerFourSP["x"].asInt();
	int p4Y = playerFourSP["y"].asInt();

	bucketlayer = tileMap->getLayer("Paintbuckets");

	player1 = Player::create(1);
	player1->setPlayernum(1);
	player1->getTexture()->setAliasTexParameters();
	player1->setPosition(Vec2(p1X, p1Y));
	player1->debugDraw(true);
	player1->setAnchorPoint(Vec2(0.5, 0.0));
	p1pos = player1->getPosition();
	addChild(player1,0);

	player2 = Player::create(2);
	player2->setPlayernum(2);
	player2->getTexture()->setAliasTexParameters();
	player2->setPosition(Vec2(p2X, p2Y));
	p2pos = player2->getPosition();
	player2->debugDraw(true);
	player2->setAnchorPoint(Vec2(0.5, 0.0));
	addChild(player2, 0);

	player3 = Player::create(3);
	player3->setPlayernum(3);
	player3->getTexture()->setAliasTexParameters();
	//player3->setPosition(Vec2(300, 300));
	////////////////////////////////////////////////////////////////////////////////////////////////// NEW ADDED CODE
	player3->setPosition(Vec2(p3X, p3Y));
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	p3pos = player3->getPosition();
	player3->setAnchorPoint(Vec2(0.5, 0.0));
	addChild(player3, 0);

	player4 = Player::create(4);
	player4->setPlayernum(4);
	player4->getTexture()->setAliasTexParameters();
	//player4->setPosition(Vec2(400, 400));
	////////////////////////////////////////////////////////////////////////////////////////////////// NEW ADDED CODE
	player4->setPosition(Vec2(p4X, p4Y));
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
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

	// Should also be part of SpawnObject layer if possible
	Sprite* wallpainting = Sprite::create("res/sprites/objects/tiny_sun_framed.png");
	wallpainting->getTexture()->setAliasTexParameters();
	wallpainting->setPosition(Vec2(320, 320));
	wallpainting->setScale(1.5);
	addChild(wallpainting,-999);

	
	// Initialize painting area 
	for (int i = 0; i <= 5; i++)
	{
		for (int j = 0; j <= 5; j++)
		{
			tileptrarray[i][j] = PaintTile::create();
			tileptrarray[i][j]->setPosition(24 * i + 264, 24 * j + 90);
			tileptrarray[i][j]->setScale(1);
			tileptrarray[i][j]->debugDraw(true);
			addChild(tileptrarray[i][j], -999);
		}
	}

	std::ifstream is("config.json");
	cereal::JSONInputArchive configloader(is);
	setupdata = ConfigFileInput();
	configloader(setupdata);
	is.close();

	CCLOG("port is");
	CCLOG(std::to_string(setupdata.port).c_str());
	CCLOG("THIS WORKING DOG?");

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

	io_service_p->poll();

	player1->setPosition(p1pos);
	player2->setPosition(p2pos);
	player3->setPosition(p3pos);
	player4->setPosition(p4pos);
	villain->setPriority(whichplayertiles);
	villain->runAI(&players);
	
	ServerPositionPacket p(villain->getPositionX(), villain->getPositionY(), player1->getPositionX(), player1->getPositionY(), player2->getPositionX(), player2->getPositionY(), player3->getPositionX(), player3->getPositionY(), player4->getPositionX(), player4->getPositionY(),tilevalues);
	
	player1->setZOrder(-player1->getPositionY());
	player2->setZOrder(-player2->getPositionY());
	player3->setZOrder(-player3->getPositionY());
	player4->setZOrder(-player4->getPositionY());
	villain->setZOrder(-villain->getPositionY());
	mytcpserverp->sendPacket(p);

	// Villain checks if she's on a player, messes everything up if she's on them
	for(Player* p : players)
	{ 
		if (abs(villain->getPositionX() - p->getPositionX()) < 5 && abs(villain->getPositionY() - p->getPositionY()) < 5)
		{
			for (int i = 0; i <= 5; i++)
			{
				for (int j = 0; j <= 5; j++)
				{
					if (whichplayertiles[i][j] == p->getPlayernum())
					{
						whichplayertiles[i][j] = 0;
						tilevalues[i][j] = 6;
						tileptrarray[i][j]->setColor("black");
						tileptrarray[i][j]->refreshColor();
					}
				}
			}
						
		}
	}

	// Move them all to the top if they've won
	if (checkSolution())
	{
		villain->setPosition(0, 0);
		vpos = cocos2d::ccp(0,0);
		player1->setPosition(50, 320);
		p1pos = cocos2d::ccp(50, 320);
		player2->setPosition(100, 320);
		p2pos = cocos2d::ccp(100, 320);
		player3->setPosition(150, 320);
		p3pos = cocos2d::ccp(150, 320);
		player4->setPosition(200, 320);
		p4pos = cocos2d::ccp(200, 320);
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
	auto playerPos = CCPoint(0, 0);
	std::string newcolor = "none";

	if (p.playernum == 1)
	{
		playerPos = player1->getPosition();
	}
	else if (p.playernum == 2)
	{
		playerPos = player2->getPosition();
	}
	else if (p.playernum == 3)
	{
		playerPos = player3->getPosition();
	}
	else if (p.playernum == 4)
	{
		playerPos = player4->getPosition();
	}

	// Convert the players position into tile coordinates
	int testx = (playerPos.x + p.dx) / (tileMap->getTileSize().width);
	int testy = ((tileMap->getMapSize().height * tileMap->getTileSize().height) - playerPos.y - p.dy) / (tileMap->getTileSize().height);
	CCPoint tileCoord = CCPoint(testx, testy);
	// This will check if the player has hit a wall
	// So far it does not do this correctly 
	//auto winSize = CCDirector::getInstance()->getWinSize();
	int mapWidth = tileMap->getMapSize().width;
	int mapHeight = tileMap->getMapSize().height;

//	if (tileCoord.x >= 0 && tileCoord.x <= 25 && tileCoord.y >= 0 && tileCoord.y <= 14) {
		int bkTile = blockage->getTileGIDAt(tileCoord);

		if (bkTile) {

			auto tilemapvals = tileMap->getPropertiesForGID(bkTile).asValueMap();

			if (!tilemapvals.empty())
			{
				auto w = tilemapvals["Collidable"].asString();

				if ("true" == w) {
					dxmove = -dxmove/2; //* 2;
					dymove = -dymove/2; //* 2;
				}
			}

	//	}
	
	}
	
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	/*
	if (tileCoord.x >= 0 && tileCoord.x <= 25 && tileCoord.y >= 0 && tileCoord.y <=14)
	{
		int bTile = bucketlayer->getTileGIDAt(tileCoord);

		if (bTile) 
		{
			auto tilemapvals = tileMap->getPropertiesForGID(bTile).asValueMap();

			if (!tilemapvals.empty()) 
			{
				auto r = tilemapvals["Red"].asString();
				auto b = tilemapvals["Blue"].asString();
				auto y = tilemapvals["Yellow"].asString();
				auto o = tilemapvals["Orange"].asString();
				
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
			}
		}
	}
	*/
	
	if (p.playernum == 1)
	{
		player1->setPositionX(player1->getPositionX() + dxmove);
		player1->setPositionY(player1->getPositionY() + dymove);
		p1pos += cocos2d::ccp(dxmove, dymove);
		//if (newcolor != "none")
		//{player1->setColor(newcolor);}
	}
	else if (p.playernum == 2)
	{
		player2->setPositionX(player2->getPositionX() + dxmove);
		player2->setPositionY(player2->getPositionY() + dymove);
		p2pos += cocos2d::ccp(dxmove, dymove);
		//if (newcolor != "none") 
		//{player2->setColor(newcolor);}
	}
	else if (p.playernum == 3)
	{
		player3->setPositionX(player3->getPositionX() + dxmove);
		player3->setPositionY(player3->getPositionY() + dymove);
		p3pos += cocos2d::ccp(dxmove, dymove);
		//if (newcolor != "none")
		//{player3->setColor(newcolor);}
	}
	else if (p.playernum == 4)
	{
		player4->setPositionX(player4->getPositionX() + dxmove);
		player4->setPositionY(player4->getPositionY() + dymove);
		p4pos += cocos2d::ccp(dxmove, dymove);
		//if (newcolor != "none")
		//{player4->setColor(newcolor);}
	}

	//if(p.button1)
	//{
	//	space(p.playernum);
	//}
	// So button1 is true only if the player has pressed the space button
	/////////////////////////////////////////////////////////////////////////////////////////////////////// NEW CODE ADDED
	if (p.button1)
	{
		space(p.playernum, tileCoord, dxmove, dymove);
	}
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


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
			auto tilemapvals = tileMap->getPropertiesForGID(bTile).asValueMap();

			if (!tilemapvals.empty())
			{
				auto r = tilemapvals["Red"].asString();
				auto b = tilemapvals["Blue"].asString();
				auto y = tilemapvals["Yellow"].asString();
				auto o = tilemapvals["Orange"].asString();

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
			}
		}

		if (playernum == 1)
		{
			player1->setPositionX(player1->getPositionX() + dxmove);
			player1->setPositionY(player1->getPositionY() + dymove);
			p1pos += cocos2d::ccp(dxmove, dymove);
			if (newcolor != "none")
			{
				player1->setColor(newcolor);
			}

		}
		else if (playernum == 2)
		{
			player2->setPositionX(player2->getPositionX() + dxmove);
			player2->setPositionY(player2->getPositionY() + dymove);
			p2pos += cocos2d::ccp(dxmove, dymove);
			if (newcolor != "none")
			{
				player2->setColor(newcolor);
			}
		}
		else if (playernum == 3)
		{
			player3->setPositionX(player3->getPositionX() + dxmove);
			player3->setPositionY(player3->getPositionY() + dymove);
			p3pos += cocos2d::ccp(dxmove, dymove);
			if (newcolor != "none")
			{
				player3->setColor(newcolor);
			}
		}
		else if (playernum == 4)
		{
			player4->setPositionX(player4->getPositionX() + dxmove);
			player4->setPositionY(player4->getPositionY() + dymove);
			p4pos += cocos2d::ccp(dxmove, dymove);
			if (newcolor != "none")
			{
				player4->setColor(newcolor);
			}
		}
	}

		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*	auto playerPos = player1->getPosition();
	int x = playerPos.x / (tileMap->getTileSize().width * 2);
	int y = (720 - playerPos.y) / (tileMap->getTileSize().height * 2);
	CCPoint tileCoord = CCPoint(x, y);
	int tileBlock = colorTiles->getTileGIDAt(tileCoord);

	if (tileBlock) {
		auto properties = tileMap->getPropertiesForGID(tileBlock).asValueMap();

		if (!properties.empty()) {
			auto paint = properties["toPaint"].asString();

			if ("true" == paint) 
			{
							
					PaintTile* tile = PaintTile::create(player1->getColor());
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// NEW CODE ADDED
	// Check to see if their position is where there is a bucket and assign that color
	std::string newcolor = "none";
	
	
	if (tileCoord.x >= 0 && tileCoord.x <= 25 && tileCoord.y >= 0 && tileCoord.y <= 14)
	{
		int bTile = bucketlayer->getTileGIDAt(tileCoord);

		if (bTile)
		{
			auto tilemapvals = tileMap->getPropertiesForGID(bTile).asValueMap();

			if (!tilemapvals.empty())
			{
				auto r = tilemapvals["Red"].asString();
				auto b = tilemapvals["Blue"].asString();
				auto y = tilemapvals["Yellow"].asString();
				auto o = tilemapvals["Orange"].asString();

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
			}
		}

		if (playernum == 1)
		{
			player1->setPositionX(player1->getPositionX() + dxmove);
			player1->setPositionY(player1->getPositionY() + dymove);
			p1pos += cocos2d::ccp(dxmove, dymove);
			if (newcolor != "none")
			{
				player1->setColor(newcolor);
			}

		}
		else if (playernum == 2)
		{
			player2->setPositionX(player2->getPositionX() + dxmove);
			player2->setPositionY(player2->getPositionY() + dymove);
			p2pos += cocos2d::ccp(dxmove, dymove);
			if (newcolor != "none")
			{
				player2->setColor(newcolor);
			}
		}
		else if (playernum == 3)
		{
			player3->setPositionX(player3->getPositionX() + dxmove);
			player3->setPositionY(player3->getPositionY() + dymove);
			p3pos += cocos2d::ccp(dxmove, dymove);
			if (newcolor != "none")
			{
				player3->setColor(newcolor);
			}
		}
		else if (playernum == 4)
		{
			player4->setPositionX(player4->getPositionX() + dxmove);
			player4->setPositionY(player4->getPositionY() + dymove);
			p4pos += cocos2d::ccp(dxmove, dymove);
			if (newcolor != "none")
			{
				player4->setColor(newcolor);
			}
		}
		
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////				tile->getTexture()->setAliasTexParameters();
					tile->setPosition(player1->getPositionX(), player1->getPositionY());
					tile->setScale(1.0);
					addChild(tile, 0);
			}

				
			
		}
	}
	*/

	for (int i = 0; i <= 5; i++)
	{
		for (int j = 0; j <= 5; j++)
		{
			
			if(playernum == 1)
			{

				if (player1->getPositionX() > tileptrarray[i][j]->getPositionX() - 12 && player1->getPositionX() < tileptrarray[i][j]->getPositionX() + 12 && player1->getPositionY() > tileptrarray[i][j]->getPositionY() - 12 && player1->getPositionY() < tileptrarray[i][j]->getPositionY() + 12)
				{
					tileptrarray[i][j]->setColor(player1->getColor());
					tileptrarray[i][j]->refreshColor();
					if (player1->getColor() == "red")
					{
						tilevalues[i][j] = 2;
					}
					if (player1->getColor() == "blue")
					{
						tilevalues[i][j] = 3;
					}
					if (player1->getColor() == "yellow")
					{
						tilevalues[i][j] = 4;
					}
					if (player1->getColor() == "orange")
					{
						tilevalues[i][j] = 5;
					}
					whichplayertiles[i][j] = 1;
				}
			}
			else if (playernum == 2)
			{

				if (player2->getPositionX() > tileptrarray[i][j]->getPositionX() - 12 && player2->getPositionX() < tileptrarray[i][j]->getPositionX() + 12 && player2->getPositionY() > tileptrarray[i][j]->getPositionY() - 12 && player2->getPositionY() < tileptrarray[i][j]->getPositionY() + 12)
				{
					tileptrarray[i][j]->setColor(player2->getColor());
					tileptrarray[i][j]->refreshColor();
					if (player2->getColor() == "red")
					{
						tilevalues[i][j] = 2;
					}
					if (player2->getColor() == "blue")
					{
						tilevalues[i][j] = 3;
					}
					if (player2->getColor() == "yellow")
					{
						tilevalues[i][j] = 4;
					}
					if (player2->getColor() == "orange")
					{
						tilevalues[i][j] = 5;
					}
					whichplayertiles[i][j] = 2;
				}
			}
			else if (playernum == 3)
			{

				if (player3->getPositionX() > tileptrarray[i][j]->getPositionX() - 12 && player3->getPositionX() < tileptrarray[i][j]->getPositionX() + 12 && player3->getPositionY() > tileptrarray[i][j]->getPositionY() - 12 && player3->getPositionY() < tileptrarray[i][j]->getPositionY() + 12)
				{
					tileptrarray[i][j]->setColor(player3->getColor());
					tileptrarray[i][j]->refreshColor();
					if (player3->getColor() == "red")
					{
						tilevalues[i][j] = 2;
					}
					if (player3->getColor() == "blue")
					{
						tilevalues[i][j] = 3;
					}
					if (player3->getColor() == "yellow")
					{
						tilevalues[i][j] = 4;
					}
					if (player3->getColor() == "orange")
					{
						tilevalues[i][j] = 5;
					}
					whichplayertiles[i][j] = 3;
				}
			}
			if (playernum == 4)
			{

				if (player4->getPositionX() > tileptrarray[i][j]->getPositionX() - 12 && player4->getPositionX() < tileptrarray[i][j]->getPositionX() + 12 && player4->getPositionY() > tileptrarray[i][j]->getPositionY() - 12 && player4->getPositionY() < tileptrarray[i][j]->getPositionY() + 12)
				{
					tileptrarray[i][j]->setColor(player4->getColor());
					tileptrarray[i][j]->refreshColor();
					if (player4->getColor() == "red")
					{
						tilevalues[i][j] = 2;
					}
					if (player4->getColor() == "blue")
					{
						tilevalues[i][j] = 3;
					}
					if (player4->getColor() == "yellow")
					{
						tilevalues[i][j] = 4;
					}
					if (player4->getColor() == "orange")
					{
						tilevalues[i][j] = 5;
					}
					whichplayertiles[i][j] = 4;
				}
			}
		}
	}
}

bool ServerDemo::checkSolution()
{


	for (int i = 0; i <= 5; i++)
	{
		for (int j = 0; j <= 5; j++)
		{
			if(tilevalues[i][j] != solution[i][j])
			{
				//CCLOG(std::to_string(i).c_str());
				//CCLOG(std::to_string(j).c_str());
				//CCLOG("solution not equal");
				//CCLOG(std::to_string(tilevalues[i][j]).c_str());
				//CCLOG(std::to_string(solution[i][j]).c_str());
				return false;
			}
		}

	}
	return true;

}