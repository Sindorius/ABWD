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




	std::string file = "res//maps//happy_sun_paint.tmx";
	auto str = String::createWithContentsOfFile(FileUtils::getInstance()->fullPathForFilename(file.c_str()).c_str());
	tileMap = cocos2d::experimental::TMXTiledMap::createWithXML(str->getCString(), "");
	
	addChild(tileMap, -1);


	player1 = Player::create(1);
	player1->setPlayernum(1);
	player1->getTexture()->setAliasTexParameters();
	player1->setPosition(Vec2(100, 100));
	addChild(player1,0);

	player2 = Player::create(2);
	player2->setPlayernum(2);
	player2->getTexture()->setAliasTexParameters();
	player2->setPosition(Vec2(200, 200));
	addChild(player2, 0);

	player3 = Player::create(3);
	player3->setPlayernum(3);
	player3->getTexture()->setAliasTexParameters();
	player3->setPosition(Vec2(300, 300));
	addChild(player3, 0);

	player4 = Player::create(4);
	player4->setPlayernum(4);
	player4->getTexture()->setAliasTexParameters();
	player4->setPosition(Vec2(400, 400));
	addChild(player4, 0);

	players.push_back(player1);
	players.push_back(player2);
	players.push_back(player3);
	players.push_back(player4);

	villain = Villain::create();
	villain->getTexture()->setAliasTexParameters();
	villain->setPosition(Vec2(500, 300));
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
	PlayerInputPacket p1 = myudpserverp->getPlayerPacket(1);
	PlayerInputPacket p2 = myudpserverp->getPlayerPacket(2);
	PlayerInputPacket p3 = myudpserverp->getPlayerPacket(3);
	PlayerInputPacket p4 = myudpserverp->getPlayerPacket(4);
	CCLOG("setting p1 postiion");
	CCLOG(std::to_string(player1->getPositionX()+p1.dx).c_str());
	CCLOG(std::to_string(p1.dx).c_str());
	player1->setPositionX(player1->getPositionX() + p1.dx);
	player1->setPositionY(player1->getPositionY() + p1.dy);
	player2->setPositionX(player2->getPositionX() + p2.dx);
	player2->setPositionY(player2->getPositionY() + p2.dy);
	player3->setPositionX(player3->getPositionX() + p3.dx);
	player3->setPositionY(player3->getPositionY() + p3.dy);
	player4->setPositionX(player4->getPositionX() + p4.dx);
	player4->setPositionY(player4->getPositionY() + p4.dy);


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

