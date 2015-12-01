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
	tileMap = cocos2d::experimental::TMXTiledMap::createWithXML(str->getCString(), "");

	addChild(tileMap, -1000);


	//blockage = tileMap->layerNamed("blockage1");
	//blockage->setVisible(false);

	//blueBucket = tileMap->layerNamed("blue");
	//blueBucket->setVisible(true);

	//redBucket = tileMap->layerNamed("red");
	//redBucket->setVisible(true);

	//yellowBucket = tileMap->layerNamed("yellow");
	//yellowBucket->setVisible(true);

	//orangeBucket = tileMap->layerNamed("orange");
	//orangeBucket->setVisible(true);

	//colorTiles = tileMap->layerNamed("paintTiles");

	bucketlayer = tileMap->getLayer("Paintbuckets");
	//orangeBucket->setVisible(true);


	player1 = Player::create(1);
	player1->setPlayernum(1);
	player1->getTexture()->setAliasTexParameters();
	player1->setPosition(Vec2(100, 100));
	player1->debugDraw(true);
	player1->setAnchorPoint(Vec2(0.5, 0.0));
	p1pos = player1->getPosition();
	addChild(player1,0);

	player2 = Player::create(2);
	player2->setPlayernum(2);
	player2->getTexture()->setAliasTexParameters();
	player2->setPosition(Vec2(200, 200));
	p2pos = player2->getPosition();
	player2->debugDraw(true);
	player2->setAnchorPoint(Vec2(0.5, 0.0));
	addChild(player2, 0);

	player3 = Player::create(3);
	player3->setPlayernum(3);
	player3->getTexture()->setAliasTexParameters();
	player3->setPosition(Vec2(300, 300));
	p3pos = player3->getPosition();
	player3->setAnchorPoint(Vec2(0.5, 0.0));
	addChild(player3, 0);

	player4 = Player::create(4);
	player4->setPlayernum(4);
	player4->getTexture()->setAliasTexParameters();
	player4->setPosition(Vec2(400, 400));
	player4->setAnchorPoint(Vec2(0.5, 0.0));
	p4pos = player4->getPosition();
	addChild(player4, 0);

	players.push_back(player1);
	players.push_back(player2);
	players.push_back(player3);
	players.push_back(player4);

	villain = Villain::create();
	villain->getTexture()->setAliasTexParameters();
	villain->setPosition(Vec2(500, 300));
	vpos = villain->getPosition();
	addChild(villain, 0);

	for (int i = 0; i <= 5; i++)
	{
		for (int j = 0; j <= 5; j++)
		{
			tileptrarray[i][j] = PaintTile::create();
			tileptrarray[i][j]->setPosition(24*2 * i + 264*2, 24 *2* j + 100);
			tileptrarray[i][j]->setScale(1);
			tileptrarray[i][j]->debugDraw(true);
			addChild(tileptrarray[i][j], -999);
		}
	}

	//Vector<SpriteFrame*> animFrames;
	//animFrames.reserve(4);

	//animFrames.pushBack(SpriteFrame::create("\\res\\man1_0.png", Rect(0, 0, 64, 128)));
	//animFrames.pushBack(SpriteFrame::create("\\res\\man1_1.png", Rect(0, 0, 64, 128)));
	//animFrames.pushBack(SpriteFrame::create("\\res\\man1_2.png", Rect(0, 0, 64, 128)));
	//animFrames.pushBack(SpriteFrame::create("\\res\\man1_1.png", Rect(0, 0, 64, 128)));

	//animFrames.at(0)->getTexture()->setAliasTexParameters();
	//animFrames.at(1)->getTexture()->setAliasTexParameters();
	//animFrames.at(2)->getTexture()->setAliasTexParameters();

	// create the animation out of the frames
	//Animation* animation = Animation::createWithSpriteFrames(animFrames, 0.2f);
	//walkanim = Animate::create(animation);
	//walkanim2 = Animate::create(animation);
	//walkanim3 = Animate::create(animation);
	//walkanim4 = Animate::create(animation);
	//player1->runAction(RepeatForever::create(walkanim));
	//player2->runAction(RepeatForever::create(walkanim2));
	//player3->runAction(RepeatForever::create(walkanim3));
	//player4->runAction(RepeatForever::create(walkanim4));

	std::ifstream is("config.json");
	cereal::JSONInputArchive configloader(is);
	setupdata = ConfigFileInput();
	configloader(setupdata);
	is.close();

	CCLOG("port is");
	CCLOG(std::to_string(setupdata.port).c_str());
	CCLOG("THIS WORKING DOG?");
	std::cout << "cout works dog" << std::endl;
	try
	{
		//boost::asio::io_service io_service;
		io_service_p = new boost::asio::io_service;
		myudpserverp = new UDPServer(*io_service_p, setupdata.port, this);
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
	std::cout << "polling";
	CCLOG("POLLING");


	//PlayerInputPacket p1 = myudpserverp->getPlayerPacket(1);
	//PlayerInputPacket p2 = myudpserverp->getPlayerPacket(2);
	//PlayerInputPacket p3 = myudpserverp->getPlayerPacket(3);
	//PlayerInputPacket p4 = myudpserverp->getPlayerPacket(4);
	//CCLOG("setting p1 postiion");
	//CCLOG(std::to_string(player1->getPositionX()+p1.dx).c_str());
	//CCLOG(std::to_string(p1.dx).c_str());

	player1->setPosition(p1pos);
	player2->setPosition(p2pos);
	player3->setPosition(p3pos);
	player4->setPosition(p4pos);
	villain->runAI(&players);
	
	ServerPositionPacket p(villain->getPositionX(), villain->getPositionY(), player1->getPositionX(), player1->getPositionY(), player2->getPositionX(), player2->getPositionY(), player3->getPositionX(), player3->getPositionY(), player4->getPositionX(), player4->getPositionY(),tilevalues);
	
	player1->setZOrder(-player1->getPositionY());
	player2->setZOrder(-player2->getPositionY());
	player3->setZOrder(-player3->getPositionY());
	player4->setZOrder(-player4->getPositionY());
	villain->setZOrder(-villain->getPositionY());
	myudpserverp->sendPacket(p);
	//myudpserverp->do_send();
}

ServerDemo::~ServerDemo()
{
	if (io_service_p)
		delete io_service_p;
	
	if (myudpserverp)
		delete myudpserverp;

}



void ServerDemo::processPlayerPacket(PlayerInputPacket p)
{

	if (p.playernum == 1)
	{
		
		auto playerPos = player1->getPosition();
		float x1move = p.dx;
		float y1move = p.dy;

		// Convert the players position into tile coordinates
		int x = playerPos.x / (tileMap->getTileSize().width * 2);
		//int y = (720 - playerPos.y) / (tileMap->getTileSize().height * 2);
		int y = (720 - playerPos.y) / (tileMap->getTileSize().height * 2);
		CCPoint tileCoord = CCPoint(x, y);

		// Seeing if the sprite collides with a blocked tile
		/*
		int tileBlock = blockage->getTileGIDAt(tileCoord);

		if (tileBlock) {
			auto properties = tileMap->getPropertiesForGID(tileBlock).asValueMap();

			if (!properties.empty()) {
				auto collision = properties["Blockage"].asString();

				if ("true" == collision) {
					x1move = -x1move;
					y1move = -y1move;
				}
			}
		}*/

		int bTile = bucketlayer->getTileGIDAt(tileCoord);

		if (bTile) {
			auto tilemapvals = tileMap->getPropertiesForGID(bTile).asValueMap();

			if (!tilemapvals.empty()) {
				auto r = tilemapvals["Red"].asString();
				auto b = tilemapvals["Blue"].asString();
				auto y = tilemapvals["Yellow"].asString();
				auto o = tilemapvals["Orange"].asString();

				if ("true" == r) 
				{
					x1move = -x1move * 2;
					y1move = -y1move * 2;
					player1->setColor("red");
				}
				if ("true" == b) 
				{
					x1move = -x1move * 2;
					y1move = -y1move * 2;
					player1->setColor("blue");
				}
				if ("true" == y) {
					x1move = -x1move * 2;
					y1move = -y1move * 2;
					player1->setColor("yellow");
				}
				if ("true" == o) {
					x1move = -x1move * 2;
					y1move = -y1move * 2;
					player1->setColor("orange");
				}


			}
	
		}

		//CCLOG("This is the player color: %s", player->getColor().c_str());
		player1->setPositionX(player1->getPositionX() + x1move);
		player1->setPositionY(player1->getPositionY() + y1move);
				
		p1pos += cocos2d::ccp(x1move, y1move);

		if(p.button1)
		{
			space(p.playernum);
		}

	}
	else if (p.playernum == 2)
	{
		auto playerPos = player2->getPosition();
		float x1move = p.dx;
		float y1move = p.dy;

		// Convert the players position into tile coordinates
		int x = playerPos.x / (tileMap->getTileSize().width * 2);
		//int y = (720 - playerPos.y) / (tileMap->getTileSize().height * 2);
		int y = (720 - playerPos.y) / (tileMap->getTileSize().height * 2);
		CCPoint tileCoord = CCPoint(x, y);

		// Seeing if the sprite collides with a blocked tile
		/*
		int tileBlock = blockage->getTileGIDAt(tileCoord);

		if (tileBlock) {
		auto properties = tileMap->getPropertiesForGID(tileBlock).asValueMap();

		if (!properties.empty()) {
		auto collision = properties["Blockage"].asString();

		if ("true" == collision) {
		x1move = -x1move;
		y1move = -y1move;
		}
		}
		}*/

		int bTile = bucketlayer->getTileGIDAt(tileCoord);

		if (bTile) {
			auto tilemapvals = tileMap->getPropertiesForGID(bTile).asValueMap();

			if (!tilemapvals.empty()) {
				auto r = tilemapvals["Red"].asString();
				auto b = tilemapvals["Blue"].asString();
				auto y = tilemapvals["Yellow"].asString();
				auto o = tilemapvals["Orange"].asString();

				if ("true" == r)
				{
					x1move = -x1move * 2;
					y1move = -y1move * 2;
					player2->setColor("red");
				}
				if ("true" == b)
				{
					x1move = -x1move * 2;
					y1move = -y1move * 2;
					player2->setColor("blue");
				}
				if ("true" == y) {
					x1move = -x1move * 2;
					y1move = -y1move * 2;
					player2->setColor("yellow");
				}
				if ("true" == o) {
					x1move = -x1move * 2;
					y1move = -y1move * 2;
					player2->setColor("orange");
				}


			}

		}

		//CCLOG("This is the player color: %s", player->getColor().c_str());
		player2->setPositionX(player2->getPositionX() + x1move);
		player2->setPositionY(player2->getPositionY() + y1move);

		p2pos += cocos2d::ccp(x1move, y1move);

		if (p.button1)
		{
			space(p.playernum);
		}

		
		//p2pos += cocos2d::ccp(p.dx, p.dy);
	}
	else if (p.playernum == 3)
	{
		auto playerPos = player3->getPosition();
		float x1move = p.dx;
		float y1move = p.dy;

		// Convert the players position into tile coordinates
		int x = playerPos.x / (tileMap->getTileSize().width * 2);
		//int y = (720 - playerPos.y) / (tileMap->getTileSize().height * 2);
		int y = (720 - playerPos.y) / (tileMap->getTileSize().height * 2);
		CCPoint tileCoord = CCPoint(x, y);

		// Seeing if the sprite collides with a blocked tile
		/*
		int tileBlock = blockage->getTileGIDAt(tileCoord);

		if (tileBlock) {
		auto properties = tileMap->getPropertiesForGID(tileBlock).asValueMap();

		if (!properties.empty()) {
		auto collision = properties["Blockage"].asString();

		if ("true" == collision) {
		x1move = -x1move;
		y1move = -y1move;
		}
		}
		}*/

		int bTile = bucketlayer->getTileGIDAt(tileCoord);

		if (bTile) {
			auto tilemapvals = tileMap->getPropertiesForGID(bTile).asValueMap();

			if (!tilemapvals.empty()) {
				auto r = tilemapvals["Red"].asString();
				auto b = tilemapvals["Blue"].asString();
				auto y = tilemapvals["Yellow"].asString();
				auto o = tilemapvals["Orange"].asString();

				if ("true" == r)
				{
					x1move = -x1move * 2;
					y1move = -y1move * 2;
					player3->setColor("red");
				}
				if ("true" == b)
				{
					x1move = -x1move * 2;
					y1move = -y1move * 2;
					player3->setColor("blue");
				}
				if ("true" == y) {
					x1move = -x1move * 2;
					y1move = -y1move * 2;
					player3->setColor("yellow");
				}
				if ("true" == o) {
					x1move = -x1move * 2;
					y1move = -y1move * 2;
					player3->setColor("orange");
				}


			}

		}

		//CCLOG("This is the player color: %s", player->getColor().c_str());
		player3->setPositionX(player3->getPositionX() + x1move);
		player3->setPositionY(player3->getPositionY() + y1move);

		p3pos += cocos2d::ccp(x1move, y1move);

		if (p.button1)
		{
			space(p.playernum);
		}
		//p3pos += cocos2d::ccp(p.dx, p.dy);
	}
	else if (p.playernum == 4)
	{
		auto playerPos = player4->getPosition();
		float x1move = p.dx;
		float y1move = p.dy;

		// Convert the players position into tile coordinates
		int x = playerPos.x / (tileMap->getTileSize().width * 2);
		//int y = (720 - playerPos.y) / (tileMap->getTileSize().height * 2);
		int y = (720 - playerPos.y) / (tileMap->getTileSize().height * 2);
		CCPoint tileCoord = CCPoint(x, y);

		// Seeing if the sprite collides with a blocked tile
		/*
		int tileBlock = blockage->getTileGIDAt(tileCoord);

		if (tileBlock) {
		auto properties = tileMap->getPropertiesForGID(tileBlock).asValueMap();

		if (!properties.empty()) {
		auto collision = properties["Blockage"].asString();

		if ("true" == collision) {
		x1move = -x1move;
		y1move = -y1move;
		}
		}
		}*/

		int bTile = bucketlayer->getTileGIDAt(tileCoord);

		if (bTile) {
			auto tilemapvals = tileMap->getPropertiesForGID(bTile).asValueMap();

			if (!tilemapvals.empty()) {
				auto r = tilemapvals["Red"].asString();
				auto b = tilemapvals["Blue"].asString();
				auto y = tilemapvals["Yellow"].asString();
				auto o = tilemapvals["Orange"].asString();

				if ("true" == r)
				{
					x1move = -x1move * 2;
					y1move = -y1move * 2;
					player4->setColor("red");
				}
				if ("true" == b)
				{
					x1move = -x1move * 2;
					y1move = -y1move * 2;
					player4->setColor("blue");
				}
				if ("true" == y) {
					x1move = -x1move * 2;
					y1move = -y1move * 2;
					player4->setColor("yellow");
				}
				if ("true" == o) {
					x1move = -x1move * 2;
					y1move = -y1move * 2;
					player4->setColor("orange");
				}


			}

		}

		//CCLOG("This is the player color: %s", player->getColor().c_str());
		player4->setPositionX(player4->getPositionX() + x1move);
		player4->setPositionY(player4->getPositionY() + y1move);

		p4pos += cocos2d::ccp(x1move, y1move);

		if (p.button1)
		{
			space(p.playernum);
		}
		//p4pos += cocos2d::ccp(p.dx, p.dy);
	}

}



void ServerDemo::space(int playernum) 
{

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
					tile->getTexture()->setAliasTexParameters();
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

				if (player1->getPositionX() > tileptrarray[i][j]->getPositionX() - 24 && player1->getPositionX() < tileptrarray[i][j]->getPositionX() + 24 && player1->getPositionY() > tileptrarray[i][j]->getPositionY() - 24 && player1->getPositionY() < tileptrarray[i][j]->getPositionY() + 24)
				{
					tileptrarray[i][j]->setColor(player1->getColor());
					tileptrarray[i][j]->refreshColor();
					if (player1->getColor() == "red")
					{
						tilevalues[i][j] = 1;
					}
					if (player1->getColor() == "blue")
					{
						tilevalues[i][j] = 2;
					}
					if (player1->getColor() == "yellow")
					{
						tilevalues[i][j] = 3;
					}
					if (player1->getColor() == "orange")
					{
						tilevalues[i][j] = 4;
					}
				}
			}
			else if (playernum == 2)
			{

				if (player2->getPositionX() > tileptrarray[i][j]->getPositionX() - 24 && player2->getPositionX() < tileptrarray[i][j]->getPositionX() + 24 && player2->getPositionY() > tileptrarray[i][j]->getPositionY() - 24 && player2->getPositionY() < tileptrarray[i][j]->getPositionY() + 24)
				{
					tileptrarray[i][j]->setColor(player2->getColor());
					tileptrarray[i][j]->refreshColor();
					if (player2->getColor() == "red")
					{
						tilevalues[i][j] = 1;
					}
					if (player2->getColor() == "blue")
					{
						tilevalues[i][j] = 2;
					}
					if (player2->getColor() == "yellow")
					{
						tilevalues[i][j] = 3;
					}
					if (player2->getColor() == "orange")
					{
						tilevalues[i][j] = 4;
					}
				}
			}
			else if (playernum == 3)
			{

				if (player3->getPositionX() > tileptrarray[i][j]->getPositionX() - 24 && player3->getPositionX() < tileptrarray[i][j]->getPositionX() + 24 && player3->getPositionY() > tileptrarray[i][j]->getPositionY() - 24 && player3->getPositionY() < tileptrarray[i][j]->getPositionY() + 24)
				{
					tileptrarray[i][j]->setColor(player1->getColor());
					tileptrarray[i][j]->refreshColor();
					if (player3->getColor() == "red")
					{
						tilevalues[i][j] = 1;
					}
					if (player3->getColor() == "blue")
					{
						tilevalues[i][j] = 2;
					}
					if (player3->getColor() == "yellow")
					{
						tilevalues[i][j] = 3;
					}
					if (player3->getColor() == "orange")
					{
						tilevalues[i][j] = 4;
					}
				}
			}
			if (playernum == 4)
			{

				if (player4->getPositionX() > tileptrarray[i][j]->getPositionX() - 24 && player4->getPositionX() < tileptrarray[i][j]->getPositionX() + 24 && player4->getPositionY() > tileptrarray[i][j]->getPositionY() - 24 && player4->getPositionY() < tileptrarray[i][j]->getPositionY() + 24)
				{
					tileptrarray[i][j]->setColor(player4->getColor());
					tileptrarray[i][j]->refreshColor();
					if (player4->getColor() == "red")
					{
						tilevalues[i][j] = 1;
					}
					if (player4->getColor() == "blue")
					{
						tilevalues[i][j] = 2;
					}
					if (player4->getColor() == "yellow")
					{
						tilevalues[i][j] = 3;
					}
					if (player4->getColor() == "orange")
					{
						tilevalues[i][j] = 4;
					}
				}
			}
		}
	}

}
