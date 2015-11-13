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
    
	std::ifstream is("config.json");
	cereal::JSONInputArchive configloader(is);
	setupdata = ConfigFileInput();
	configloader(setupdata);
	is.close();

	CCLOG("port is" );
	CCLOG(std::to_string(setupdata.port).c_str());
	CCLOG("THIS WORKING DOG?");
	std::cout << "cout works dog" << std::endl;
	try
	{
		//boost::asio::io_service io_service;
		io_service_p = new boost::asio::io_service;
		myudpserverp = new UDPServer (*io_service_p, setupdata.port);
	}
	catch (std::exception& e)
	{
		std::cerr << "Exception: " << e.what() << "\n";
	}




	std::string file = "res//demoroom.tmx";
	auto str = String::createWithContentsOfFile(FileUtils::getInstance()->fullPathForFilename(file.c_str()).c_str());
	tileMap = cocos2d::experimental::TMXTiledMap::createWithXML(str->getCString(), "");
	
	addChild(tileMap, -1);


	player1 = Player::create();
	player1->setPlayernum(1);
	player1->getTexture()->setAliasTexParameters();
	player1->setPosition(Vec2(100, 100));
	player1->setScale(1.5);
	addChild(player1,0);

	player2 = Player::create();
	player2->setPlayernum(2);
	player2->getTexture()->setAliasTexParameters();
	player2->setPosition(Vec2(200, 300));
	player2->setScale(1.5);
	addChild(player2, 0);

	players.push_back(player1);
	players.push_back(player2);

	villain = Villain::create();
	villain->getTexture()->setAliasTexParameters();
	villain->setPosition(Vec2(500, 300));
	villain->setScale(1.5);
	addChild(villain, 0);


	Vector<SpriteFrame*> animFrames;
	animFrames.reserve(4);

	animFrames.pushBack(SpriteFrame::create("\\res\\man1_0.png", Rect(0, 0, 64, 128)));
	animFrames.pushBack(SpriteFrame::create("\\res\\man1_1.png", Rect(0, 0, 64, 128)));
	animFrames.pushBack(SpriteFrame::create("\\res\\man1_2.png", Rect(0, 0, 64, 128)));
	animFrames.pushBack(SpriteFrame::create("\\res\\man1_1.png", Rect(0, 0, 64, 128)));

	animFrames.at(0)->getTexture()->setAliasTexParameters();
	animFrames.at(1)->getTexture()->setAliasTexParameters();
	animFrames.at(2)->getTexture()->setAliasTexParameters();

	// create the animation out of the frames
	Animation* animation = Animation::createWithSpriteFrames(animFrames, 0.2f);
	walkanim = Animate::create(animation);
	walkanim2 = Animate::create(animation);
	player1->runAction(RepeatForever::create(walkanim));
	player2->runAction(RepeatForever::create(walkanim2));


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


	villain->runAI(&players);
	PlayerInputPacket p1 = myudpserverp->getPlayer1Packet();
	PlayerInputPacket p2 = myudpserverp->getPlayer2Packet();
	CCLOG("setting p1 postiion");
	CCLOG(std::to_string(player1->getPositionX()+p1.dx).c_str());
	CCLOG(std::to_string(p1.dx).c_str());
	player1->setPositionX(player1->getPositionX() + p1.dx);
	player1->setPositionY(player1->getPositionY() + p1.dy);
	player2->setPositionX(player2->getPositionX() + p2.dx);
	player2->setPositionY(player2->getPositionY() + p2.dy);


	ServerPositionPacket p(villain->getPositionX(), villain->getPositionY(), player1->getPositionX(), player1->getPositionY(), player2->getPositionX(), player2->getPositionY());

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

