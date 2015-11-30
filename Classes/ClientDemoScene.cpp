#include "ClientDemoScene.h"

USING_NS_CC;
using boost::asio::ip::udp;


Scene* ClientDemo::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = ClientDemo::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool ClientDemo::init()
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

	char mycp1[32];
	char mycp2[32];
	strncpy(mycp1, setupdata.ipaddress.c_str(), 32);
	strncpy(mycp2, std::to_string(setupdata.port).c_str(), 32);

	try
	{
		CCLOG("setting up udp interface");
		CCLOG(mycp1);
		CCLOG(mycp2);
		//boost::asio::io_service io_service;
		io_service_p = new boost::asio::io_service;
	
		//udp::socket myudpsocket2(*io_service_p, udp::endpoint(udp::v4(), 0));
		myudpsocketp = new udp::socket(*io_service_p, udp::endpoint(udp::v4(), 0));
		udp::resolver resolver(*io_service_p);

		playernum = setupdata.level;
		myendpoint = *resolver.resolve({ udp::v4(), mycp1, mycp2 });
		//myudpinterfacep = new UDPInterface(*io_service_p, endpoint);
		doReceive();
		
	}
	catch (std::exception& e)
	{
		std::cerr << "Exception: " << e.what() << "\n";
		CCLOG("exception");
		CCLOG(e.what());
	}




	std::string file = "res//maps//newroom//newroom.tmx";
	auto str = String::createWithContentsOfFile(FileUtils::getInstance()->fullPathForFilename(file.c_str()).c_str());
	tileMap = cocos2d::CCTMXTiledMap::createWithXML(str->getCString(), "");

	addChild(tileMap, -1000);

	player1 = Player::create(1);
	player1->setPlayernum(1);
	player1->getTexture()->setAliasTexParameters();
	player1->setPosition(Vec2(100, 100));
	player1->setAnchorPoint(Vec2(0.5, 0.0));
	addChild(player1, 0);

	player2 = Player::create(2);
	player2->setPlayernum(2);
	player2->getTexture()->setAliasTexParameters();
	player2->setPosition(Vec2(200, 200));
	player2->setAnchorPoint(Vec2(0.5, 0.0));
	addChild(player2, 0);

	player3 = Player::create(3);
	player3->setPlayernum(3);
	player3->getTexture()->setAliasTexParameters();
	player3->setPosition(Vec2(300, 300));
	player3->setAnchorPoint(Vec2(0.5, 0.0));
	addChild(player3, 0);

	player4 = Player::create(4);
	player4->setPlayernum(4);
	player4->getTexture()->setAliasTexParameters();
	player4->setPosition(Vec2(400, 400));
	player4->setAnchorPoint(Vec2(0.5, 0.0));
	addChild(player4, 0);

	players.push_back(player1);
	players.push_back(player2);
	players.push_back(player3);
	players.push_back(player4);

	villain = Villain::create();
	villain->getTexture()->setAliasTexParameters();
	villain->setPosition(Vec2(500, 300));
	addChild(villain, 0);

	for (int i = 0; i <= 5; i++)
	{
		for (int j = 0; j <= 5; j++)
		{
			tileptrarray[i][j] = PaintTile::create();
			tileptrarray[i][j]->setPosition(24 * 2 * i + 264 * 2, 24 * 2 * j + 100);
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



	auto keyListener = EventListenerKeyboard::create();
	keyListener->onKeyPressed = CC_CALLBACK_2(ClientDemo::KeyDown, this);
	keyListener->onKeyReleased = CC_CALLBACK_2(ClientDemo::KeyRelease, this);

	_eventDispatcher->addEventListenerWithFixedPriority(keyListener, 2);

	this->scheduleUpdate();
    return true;
}


void ClientDemo::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}


void ClientDemo::update(float dt)
{

	io_service_p->poll();

	//CCLOG("POLLING");



	
	if (xmove || ymove || button1)
	{
		PlayerInputPacket p2 = PlayerInputPacket(playernum, xmove, ymove, button1);
		std::ostringstream os2;
		cereal::BinaryOutputArchive outar(os2);
		outar(p2);
		outstringbuffer = os2.str();
		//CCLOG("Sending packet");
		myudpsocketp->async_send_to(boost::asio::buffer(outstringbuffer), myendpoint, [this](boost::system::error_code /*ec*/, std::size_t /*bytes_sent*/)
		{
			//CCLOG("Sent packet");
			
		});
		//CCLOG("sentplayerpacket");
		//CCLOG(std::to_string(xmove).c_str());
		//CCLOG(std::to_string(ymove).c_str());
	}

	player1->setZOrder(-player1->getPositionY());
	player2->setZOrder(-player2->getPositionY());
	player3->setZOrder(-player3->getPositionY());
	player4->setZOrder(-player4->getPositionY());
	villain->setZOrder(-villain->getPositionY());

}

ClientDemo::~ClientDemo()
{
	if (io_service_p)
		delete io_service_p;
	
	//if (myudpinterfacep)
	//	delete myudpinterfacep;
	
}


void ClientDemo::KeyDown(EventKeyboard::KeyCode keyCode, Event* event)
{

	switch (keyCode){
	case EventKeyboard::KeyCode::KEY_UP_ARROW:
		ymove += 2;
		break;
	case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
		ymove -= 2;
		break;
	case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
		xmove -= 2;
		break;
	case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
		xmove += 2;
		break;
	case EventKeyboard::KeyCode::KEY_SPACE:
		button1 = true;
		break;
	}
	event->stopPropagation();
}

void ClientDemo::KeyRelease(EventKeyboard::KeyCode keyCode, Event* event)
{

	switch (keyCode){
	case EventKeyboard::KeyCode::KEY_UP_ARROW:
		ymove = 0;
		break;
	case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
		ymove = 0;
		break;
	case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
		xmove = 0;
		break;
	case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
		xmove = 0;
		break;
	case EventKeyboard::KeyCode::KEY_SPACE:
		button1 = false;
		break;
	}
	event->stopPropagation();

}

void ClientDemo::processPacket(ServerPositionPacket p)
{
	CCLOG("updatedserverpacket");
	//CCLOG(std::to_string(p.p1x).c_str());
	//CCLOG(std::to_string(p.p2x).c_str());
	//CCLOG(std::to_string(p.p3x).c_str());
	//CCLOG(std::to_string(p.p4x).c_str());
	//CCLOG(std::to_string(p.vx).c_str());
	CCLOG(std::to_string(tilevalues[0][0]).c_str());
	CCLOG(std::to_string(p.tilevalues[0][0]).c_str());
	player1->setPosition(Vec2(p.p1x, p.p1y));
	player2->setPosition(Vec2(p.p2x, p.p2y));
	player3->setPosition(Vec2(p.p3x, p.p3y));
	player4->setPosition(Vec2(p.p4x, p.p4y));
	villain->setPosition(Vec2(p.vx, p.vy));
	//tilevalues = p.tilevalues;

	for (int i = 0; i <= 5; i++)
	{
		for (int j = 0; j <= 5; j++)
		{
			if (tilevalues[i][j] != p.tilevalues[i][j])
			{
				tilevalues[i][j] = p.tilevalues[i][j];
				if (tilevalues[i][j] == 1)
				{
					tileptrarray[i][j]->setColor("red");
					tileptrarray[i][j]->refreshColor();
				}
				if (tilevalues[i][j] == 2)
				{
					tileptrarray[i][j]->setColor("blue");
					tileptrarray[i][j]->refreshColor();
					CCLOG(std::to_string(tilevalues[0][0]).c_str());
					CCLOG(std::to_string(p.tilevalues[0][0]).c_str());
				}
				if (tilevalues[i][j] == 3)
				{
					tileptrarray[i][j]->setColor("yellow");
					tileptrarray[i][j]->refreshColor();
				}
				if (tilevalues[i][j] == 4)
				{
					tileptrarray[i][j]->setColor("orange");
					tileptrarray[i][j]->refreshColor();
				}
			}
		}
	}

}

void ClientDemo::doReceive()
{
	myudpsocketp->async_receive_from(
		boost::asio::buffer(indata, max_length), myendpoint,
		[this](boost::system::error_code ec, std::size_t bytes_recvd)
	{
		if (!ec && bytes_recvd > 0)
		{
			CCLOG("received data");
			std::stringstream is2;
			cereal::BinaryInputArchive inar(is2);
			for (size_t i = 0; i < bytes_recvd; i++)
			{
				// there has to be a better way vectorized? than using for loop!!!
				is2 << indata[i];
			}
			//		
			ServerPositionPacket inpack;
			inar(inpack);
			CCLOG(is2.str().c_str());
			CCLOG("input from server");
			CCLOG(std::to_string(inpack.vx).c_str());
			processPacket(inpack);
			//s.send_to(boost::asio::buffer(os2.str()), endpoint);
			doReceive();
		}
		else
		{
			doReceive();
		}
	});
}