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
    


	

	std::string file = "res//maps//newroom//newroom.tmx";
	auto str = String::createWithContentsOfFile(FileUtils::getInstance()->fullPathForFilename(file.c_str()).c_str());
	tileMap = cocos2d::CCTMXTiledMap::createWithXML(str->getCString(), "");
	
	addChild(tileMap, -1000);


	blockage = tileMap->layerNamed("blockage1");
	blockage->setVisible(false);

	blueBucket = tileMap->layerNamed("blue");
	blueBucket->setVisible(true);

	redBucket = tileMap->layerNamed("red");
	redBucket->setVisible(true);

	yellowBucket = tileMap->layerNamed("yellow");
	yellowBucket->setVisible(true);

	orangeBucket = tileMap->layerNamed("orange");
	orangeBucket->setVisible(true);

	colorTiles = tileMap->layerNamed("paintTiles");


	player1 = Player::create(1);
	player1->setPlayernum(1);
	player1->getTexture()->setAliasTexParameters();
	player1->setPosition(Vec2(100, 100));
	p1pos = player1->getPosition();
	addChild(player1,0);

	player2 = Player::create(2);
	player2->setPlayernum(2);
	player2->getTexture()->setAliasTexParameters();
	player2->setPosition(Vec2(200, 200));
	p2pos = player2->getPosition();
	addChild(player2, 0);

	player3 = Player::create(3);
	player3->setPlayernum(3);
	player3->getTexture()->setAliasTexParameters();
	player3->setPosition(Vec2(300, 300));
	p3pos = player3->getPosition();
	addChild(player3, 0);

	player4 = Player::create(4);
	player4->setPlayernum(4);
	player4->getTexture()->setAliasTexParameters();
	player4->setPosition(Vec2(400, 400));
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
	
	ServerPositionPacket p(villain->getPositionX(), villain->getPositionY(), player1->getPositionX(), player1->getPositionY(), player2->getPositionX(), player2->getPositionY(), player3->getPositionX(), player3->getPositionY(), player4->getPositionX(), player4->getPositionY());

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


		// Seeing if the sprite collides with a blocked tile
		CCPoint tileCoord = CCPoint(x, y);
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
		}

		int bTile = blueBucket->getTileGIDAt(tileCoord);

		if (bTile) {
			auto bb = tileMap->getPropertiesForGID(bTile).asValueMap();

			if (!bb.empty()) {
				auto b = bb["Blue"].asString();

				if ("true" == b) {
					x1move = -x1move;
					y1move = -y1move;
					player1->setColor("blue");
				}
			}
		}


		int redTile = redBucket->getTileGIDAt(tileCoord);

		if (redTile) {
			auto rb = tileMap->getPropertiesForGID(redTile).asValueMap();

			if (!rb.empty()) {
				auto r = rb["Red"].asString();

				if ("true" == r) {
					x1move = -x1move*2;
					y1move = -y1move*2;
					player1->setColor("red");
				}
			}
		}


		int yelTile = yellowBucket->getTileGIDAt(tileCoord);

		if (yelTile) {
			auto yb = tileMap->getPropertiesForGID(yelTile).asValueMap();

			if (!yb.empty()) {
				auto y = yb["Yellow"].asString();

				if ("true" == y) {
					x1move = -x1move;
					y1move = -y1move;
					player1->setColor("yellow");
				}
			}
		}


		int oraTile = orangeBucket->getTileGIDAt(tileCoord);

		if (oraTile) {
			auto ob = tileMap->getPropertiesForGID(oraTile).asValueMap();

			if (!ob.empty()) {
				auto o = ob["Orange"].asString();

				if ("true" == o) {
					x1move = -x1move;
					y1move = -y1move;
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
			space();
		}

	}
	else if (p.playernum == 2)
	{
		p2pos += cocos2d::ccp(p.dx, p.dy);
	}
	else if (p.playernum == 3)
	{
		p3pos += cocos2d::ccp(p.dx, p.dy);
	}
	else if (p.playernum == 4)
	{
		p4pos += cocos2d::ccp(p.dx, p.dy);
	}

}



void ServerDemo::space() {

	auto playerPos = player1->getPosition();
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
}
