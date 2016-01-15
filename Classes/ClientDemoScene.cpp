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




	std::string file = "res//maps//happy_sun_paint.tmx";
	auto str = String::createWithContentsOfFile(FileUtils::getInstance()->fullPathForFilename(file.c_str()).c_str());
	tileMap = cocos2d::CCTMXTiledMap::createWithXML(str->getCString(), "");

	addChild(tileMap, -1000);

	player1 = Player::create(1);
	player1->setPlayernum(1);
	player1->getTexture()->setAliasTexParameters();
	player1->setAnchorPoint(Vec2(0.5, 0.0));
	player1->setPosition(Vec2(100, 100));
	addChild(player1, 0);

	player2 = Player::create(2);
	player2->setPlayernum(2);
	player2->getTexture()->setAliasTexParameters();
	player2->setAnchorPoint(Vec2(0.5, 0.0));
	player2->setPosition(Vec2(200, 200));
	addChild(player2, 0);

	player3 = Player::create(3);
	player3->setPlayernum(3);
	player3->getTexture()->setAliasTexParameters();
	player3->setAnchorPoint(Vec2(0.5, 0.0));
	player3->setPosition(Vec2(300, 300));
	addChild(player3, 0);

	player4 = Player::create(4);
	player4->setPlayernum(4);
	player4->getTexture()->setAliasTexParameters();
	player4->setAnchorPoint(Vec2(0.5, 0.0));
	player4->setPosition(Vec2(400, 400));
	addChild(player4, 0);

	players.push_back(player1);
	players.push_back(player2);
	players.push_back(player3);
	players.push_back(player4);

	villain = Villain::create();
	villain->getTexture()->setAliasTexParameters();
	villain->setAnchorPoint(Vec2(0.5, 0.0));
	villain->setPosition(Vec2(500, 300));
	addChild(villain, 0);

	Sprite* wallpainting = Sprite::create("sprites/tiny_sun_framed.png");
	wallpainting->getTexture()->setAliasTexParameters();
	wallpainting->setPosition(Vec2(640, 640));
	wallpainting->setScale(1.5);
	addChild(wallpainting, -999);

	for (int i = 0; i <= 5; i++)
	{
		for (int j = 0; j <= 5; j++)
		{
			tileptrarray[i][j] = PaintTile::create();
			tileptrarray[i][j]->setPosition(24 * 2 * i + 264 * 2, 24 * 2 * j + 180);
			tileptrarray[i][j]->setScale(1);
			//tileptrarray[i][j]->debugDraw(true);
			addChild(tileptrarray[i][j], -999);
		}
	}

	//player 1 animations
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	Vector<SpriteFrame*> walkupanimFrames;
	walkupanimFrames.reserve(4);
	Vector<SpriteFrame*> walkdownanimFrames;
	walkdownanimFrames.reserve(4);
	Vector<SpriteFrame*> walkleftanimFrames;
	walkleftanimFrames.reserve(4);
	Vector<SpriteFrame*> walkrightanimFrames;
	walkrightanimFrames.reserve(4);
	Vector<SpriteFrame*> paintFrames;
	paintFrames.reserve(1);
	//animFrames.reserve(4);

	walkupanimFrames.pushBack(SpriteFrame::create("\\sprites\\animations\\char_red_back_0.png", Rect(0, 0, 48, 96)));
	walkupanimFrames.pushBack(SpriteFrame::create("\\sprites\\animations\\char_red_back_1.png", Rect(0, 0, 48, 96)));
	walkupanimFrames.pushBack(SpriteFrame::create("\\sprites\\animations\\char_red_back_2.png", Rect(0, 0, 48, 96)));
	walkupanimFrames.pushBack(SpriteFrame::create("\\sprites\\animations\\char_red_back_3.png", Rect(0, 0, 48, 96)));
	walkupanimFrames.at(0)->getTexture()->setAliasTexParameters();
	walkupanimFrames.at(1)->getTexture()->setAliasTexParameters();
	walkupanimFrames.at(2)->getTexture()->setAliasTexParameters();
	walkupanimFrames.at(3)->getTexture()->setAliasTexParameters();

	walkdownanimFrames.pushBack(SpriteFrame::create("\\sprites\\animations\\char_red_front_0.png", Rect(0, 0, 48, 96)));
	walkdownanimFrames.pushBack(SpriteFrame::create("\\sprites\\animations\\char_red_front_1.png", Rect(0, 0, 48, 96)));
	walkdownanimFrames.pushBack(SpriteFrame::create("\\sprites\\animations\\char_red_front_2.png", Rect(0, 0, 48, 96)));
	walkdownanimFrames.pushBack(SpriteFrame::create("\\sprites\\animations\\char_red_front_3.png", Rect(0, 0, 48, 96)));
	walkdownanimFrames.at(0)->getTexture()->setAliasTexParameters();
	walkdownanimFrames.at(1)->getTexture()->setAliasTexParameters();
	walkdownanimFrames.at(2)->getTexture()->setAliasTexParameters();
	walkdownanimFrames.at(3)->getTexture()->setAliasTexParameters();

	walkleftanimFrames.pushBack(SpriteFrame::create("\\sprites\\animations\\char_red_left_0.png", Rect(0, 0, 48, 96)));
	walkleftanimFrames.pushBack(SpriteFrame::create("\\sprites\\animations\\char_red_left_1.png", Rect(0, 0, 48, 96)));
	walkleftanimFrames.pushBack(SpriteFrame::create("\\sprites\\animations\\char_red_left_2.png", Rect(0, 0, 48, 96)));
	walkleftanimFrames.pushBack(SpriteFrame::create("\\sprites\\animations\\char_red_left_3.png", Rect(0, 0, 48, 96)));
	walkleftanimFrames.at(0)->getTexture()->setAliasTexParameters();
	walkleftanimFrames.at(1)->getTexture()->setAliasTexParameters();
	walkleftanimFrames.at(2)->getTexture()->setAliasTexParameters();
	walkleftanimFrames.at(3)->getTexture()->setAliasTexParameters();

	walkrightanimFrames.pushBack(SpriteFrame::create("\\sprites\\animations\\char_red_right_0.png", Rect(0, 0, 48, 96)));
	walkrightanimFrames.pushBack(SpriteFrame::create("\\sprites\\animations\\char_red_right_1.png", Rect(0, 0, 48, 96)));
	walkrightanimFrames.pushBack(SpriteFrame::create("\\sprites\\animations\\char_red_right_2.png", Rect(0, 0, 48, 96)));
	walkrightanimFrames.pushBack(SpriteFrame::create("\\sprites\\animations\\char_red_right_3.png", Rect(0, 0, 48, 96)));
	walkrightanimFrames.at(0)->getTexture()->setAliasTexParameters();
	walkrightanimFrames.at(1)->getTexture()->setAliasTexParameters();
	walkrightanimFrames.at(2)->getTexture()->setAliasTexParameters();
	walkrightanimFrames.at(3)->getTexture()->setAliasTexParameters();

	paintFrames.pushBack(SpriteFrame::create("\\sprites\\animations\\char_red_right_0_paint.png", Rect(0, 0, 48, 96)));
	paintFrames.at(0)->getTexture()->setAliasTexParameters();

	// create the animation out of the frames
	Animation* upanimation = Animation::createWithSpriteFrames(walkupanimFrames, 0.1f);
	walkupanim = Animate::create(upanimation);
	walkupanim->retain();
	Animation* downanimation = Animation::createWithSpriteFrames(walkdownanimFrames, 0.1f);
	walkdownanim = Animate::create(downanimation);
	walkdownanim->retain();
	Animation* leftanimation = Animation::createWithSpriteFrames(walkleftanimFrames, 0.1f);
	walkleftanim = Animate::create(leftanimation);
	walkleftanim->retain();
	Animation* rightanimation = Animation::createWithSpriteFrames(walkrightanimFrames, 0.1f);
	walkrightanim = Animate::create(rightanimation);
	walkrightanim->retain();

	
	Animation* paintanimation = Animation::createWithSpriteFrames(paintFrames, 0.1f);
	paintanim = Animate::create(paintanimation);
	paintanim->retain();

	//walkanim2 = Animate::create(animation);
	//walkanim3 = Animate::create(animation);
	//walkanim4 = Animate::create(animation);
	//player1->runAction(RepeatForever::create(walkupanim));
	//player2->runAction(RepeatForever::create(walkanim2));
	//player3->runAction(RepeatForever::create(walkanim3));
	//player4->runAction(RepeatForever::create(walkanim4));


	//player2 animations
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	Vector<SpriteFrame*> walkupanimFrames1;
	walkupanimFrames1.reserve(4);
	Vector<SpriteFrame*> walkdownanimFrames1;
	walkdownanimFrames1.reserve(4);
	Vector<SpriteFrame*> walkleftanimFrames1;
	walkleftanimFrames1.reserve(4);
	Vector<SpriteFrame*> walkrightanimFrames1;
	walkrightanimFrames1.reserve(4);
	Vector<SpriteFrame*> paintFrames1;
	paintFrames1.reserve(1);
	//animFrames.reserve(4);

	walkupanimFrames1.pushBack(SpriteFrame::create("\\sprites\\animations\\char_blue_back_0.png", Rect(0, 0, 48, 96)));
	walkupanimFrames1.pushBack(SpriteFrame::create("\\sprites\\animations\\char_blue_back_1.png", Rect(0, 0, 48, 96)));
	walkupanimFrames1.pushBack(SpriteFrame::create("\\sprites\\animations\\char_blue_back_2.png", Rect(0, 0, 48, 96)));
	walkupanimFrames1.pushBack(SpriteFrame::create("\\sprites\\animations\\char_blue_back_3.png", Rect(0, 0, 48, 96)));
	walkupanimFrames1.at(0)->getTexture()->setAliasTexParameters();
	walkupanimFrames1.at(1)->getTexture()->setAliasTexParameters();
	walkupanimFrames1.at(2)->getTexture()->setAliasTexParameters();
	walkupanimFrames1.at(3)->getTexture()->setAliasTexParameters();

	walkdownanimFrames1.pushBack(SpriteFrame::create("\\sprites\\animations\\char_blue_front_0.png", Rect(0, 0, 48, 96)));
	walkdownanimFrames1.pushBack(SpriteFrame::create("\\sprites\\animations\\char_blue_front_1.png", Rect(0, 0, 48, 96)));
	walkdownanimFrames1.pushBack(SpriteFrame::create("\\sprites\\animations\\char_blue_front_2.png", Rect(0, 0, 48, 96)));
	walkdownanimFrames1.pushBack(SpriteFrame::create("\\sprites\\animations\\char_blue_front_3.png", Rect(0, 0, 48, 96)));
	walkdownanimFrames1.at(0)->getTexture()->setAliasTexParameters();
	walkdownanimFrames1.at(1)->getTexture()->setAliasTexParameters();
	walkdownanimFrames1.at(2)->getTexture()->setAliasTexParameters();
	walkdownanimFrames1.at(3)->getTexture()->setAliasTexParameters();

	walkleftanimFrames1.pushBack(SpriteFrame::create("\\sprites\\animations\\char_blue_left_0.png", Rect(0, 0, 48, 96)));
	walkleftanimFrames1.pushBack(SpriteFrame::create("\\sprites\\animations\\char_blue_left_1.png", Rect(0, 0, 48, 96)));
	walkleftanimFrames1.pushBack(SpriteFrame::create("\\sprites\\animations\\char_blue_left_2.png", Rect(0, 0, 48, 96)));
	walkleftanimFrames1.pushBack(SpriteFrame::create("\\sprites\\animations\\char_blue_left_3.png", Rect(0, 0, 48, 96)));
	walkleftanimFrames1.at(0)->getTexture()->setAliasTexParameters();
	walkleftanimFrames1.at(1)->getTexture()->setAliasTexParameters();
	walkleftanimFrames1.at(2)->getTexture()->setAliasTexParameters();
	walkleftanimFrames1.at(3)->getTexture()->setAliasTexParameters();

	walkrightanimFrames1.pushBack(SpriteFrame::create("\\sprites\\animations\\char_blue_right_0.png", Rect(0, 0, 48, 96)));
	walkrightanimFrames1.pushBack(SpriteFrame::create("\\sprites\\animations\\char_blue_right_1.png", Rect(0, 0, 48, 96)));
	walkrightanimFrames1.pushBack(SpriteFrame::create("\\sprites\\animations\\char_blue_right_2.png", Rect(0, 0, 48, 96)));
	walkrightanimFrames1.pushBack(SpriteFrame::create("\\sprites\\animations\\char_blue_right_3.png", Rect(0, 0, 48, 96)));
	walkrightanimFrames1.at(0)->getTexture()->setAliasTexParameters();
	walkrightanimFrames1.at(1)->getTexture()->setAliasTexParameters();
	walkrightanimFrames1.at(2)->getTexture()->setAliasTexParameters();
	walkrightanimFrames1.at(3)->getTexture()->setAliasTexParameters();

	paintFrames1.pushBack(SpriteFrame::create("\\sprites\\animations\\char_blue_right_0_paint.png", Rect(0, 0, 48, 96)));
	paintFrames1.at(0)->getTexture()->setAliasTexParameters();

	// create the animation out of the frames
	Animation* upanimation1 = Animation::createWithSpriteFrames(walkupanimFrames1, 0.1f);
	walkupanim1 = Animate::create(upanimation1);
	walkupanim1->retain();
	Animation* downanimation1 = Animation::createWithSpriteFrames(walkdownanimFrames1, 0.1f);
	walkdownanim1 = Animate::create(downanimation1);
	walkdownanim1->retain();
	Animation* leftanimation1 = Animation::createWithSpriteFrames(walkleftanimFrames1, 0.1f);
	walkleftanim1 = Animate::create(leftanimation1);
	walkleftanim1->retain();
	Animation* rightanimation1 = Animation::createWithSpriteFrames(walkrightanimFrames1, 0.1f);
	walkrightanim1 = Animate::create(rightanimation1);
	walkrightanim1->retain();


	Animation* paintanimation1 = Animation::createWithSpriteFrames(paintFrames1, 0.1f);
	paintanim1 = Animate::create(paintanimation1);
	paintanim1->retain();
	
	
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//sam animations
	Vector<SpriteFrame*> samupanimFrames;
	samupanimFrames.reserve(4);
	Vector<SpriteFrame*> samdownanimFrames;
	samdownanimFrames.reserve(4);
	Vector<SpriteFrame*> samleftanimFrames;
	samleftanimFrames.reserve(4);
	Vector<SpriteFrame*> samrightanimFrames;
	samrightanimFrames.reserve(4);
	//animFrames.reserve(4);

	samupanimFrames.pushBack(SpriteFrame::create("\\sprites\\animations\\sam_back_0.png", Rect(0, 0, 48, 96)));
	samupanimFrames.pushBack(SpriteFrame::create("\\sprites\\animations\\sam_back_1.png", Rect(0, 0, 48, 96)));
	samupanimFrames.pushBack(SpriteFrame::create("\\sprites\\animations\\sam_back_2.png", Rect(0, 0, 48, 96)));
	samupanimFrames.pushBack(SpriteFrame::create("\\sprites\\animations\\sam_back_3.png", Rect(0, 0, 48, 96)));
	samupanimFrames.at(0)->getTexture()->setAliasTexParameters();
	samupanimFrames.at(1)->getTexture()->setAliasTexParameters();
	samupanimFrames.at(2)->getTexture()->setAliasTexParameters();
	samupanimFrames.at(3)->getTexture()->setAliasTexParameters();

	samdownanimFrames.pushBack(SpriteFrame::create("\\sprites\\animations\\sam_front_0.png", Rect(0, 0, 48, 96)));
	samdownanimFrames.pushBack(SpriteFrame::create("\\sprites\\animations\\sam_front_1.png", Rect(0, 0, 48, 96)));
	samdownanimFrames.pushBack(SpriteFrame::create("\\sprites\\animations\\sam_front_2.png", Rect(0, 0, 48, 96)));
	samdownanimFrames.pushBack(SpriteFrame::create("\\sprites\\animations\\sam_front_3.png", Rect(0, 0, 48, 96)));
	samdownanimFrames.at(0)->getTexture()->setAliasTexParameters();
	samdownanimFrames.at(1)->getTexture()->setAliasTexParameters();
	samdownanimFrames.at(2)->getTexture()->setAliasTexParameters();
	samdownanimFrames.at(3)->getTexture()->setAliasTexParameters();

	samleftanimFrames.pushBack(SpriteFrame::create("\\sprites\\animations\\sam_left_0.png", Rect(0, 0, 48, 96)));
	samleftanimFrames.pushBack(SpriteFrame::create("\\sprites\\animations\\sam_left_1.png", Rect(0, 0, 48, 96)));
	samleftanimFrames.pushBack(SpriteFrame::create("\\sprites\\animations\\sam_left_2.png", Rect(0, 0, 48, 96)));
	samleftanimFrames.pushBack(SpriteFrame::create("\\sprites\\animations\\sam_left_3.png", Rect(0, 0, 48, 96)));
	samleftanimFrames.at(0)->getTexture()->setAliasTexParameters();
	samleftanimFrames.at(1)->getTexture()->setAliasTexParameters();
	samleftanimFrames.at(2)->getTexture()->setAliasTexParameters();
	samleftanimFrames.at(3)->getTexture()->setAliasTexParameters();

	samrightanimFrames.pushBack(SpriteFrame::create("\\sprites\\animations\\sam_right_0.png", Rect(0, 0, 48, 96)));
	samrightanimFrames.pushBack(SpriteFrame::create("\\sprites\\animations\\sam_right_1.png", Rect(0, 0, 48, 96)));
	samrightanimFrames.pushBack(SpriteFrame::create("\\sprites\\animations\\sam_right_2.png", Rect(0, 0, 48, 96)));
	samrightanimFrames.pushBack(SpriteFrame::create("\\sprites\\animations\\sam_right_3.png", Rect(0, 0, 48, 96)));
	samrightanimFrames.at(0)->getTexture()->setAliasTexParameters();
	samrightanimFrames.at(1)->getTexture()->setAliasTexParameters();
	samrightanimFrames.at(2)->getTexture()->setAliasTexParameters();
	samrightanimFrames.at(3)->getTexture()->setAliasTexParameters();

	// create the animation out of the frames
	Animation* samupanimation = Animation::createWithSpriteFrames(samupanimFrames, 0.1f);
	samupanim = Animate::create(samupanimation);
	samupanim->retain();
	Animation* samdownanimation = Animation::createWithSpriteFrames(samdownanimFrames, 0.1f);
	samdownanim = Animate::create(samdownanimation);
	samdownanim->retain();
	Animation* samleftanimation = Animation::createWithSpriteFrames(samleftanimFrames, 0.1f);
	samleftanim = Animate::create(samleftanimation);
	samleftanim->retain();
	Animation* samrightanimation = Animation::createWithSpriteFrames(samrightanimFrames, 0.1f);
	samrightanim = Animate::create(samrightanimation);
	samrightanim->retain();




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
		if (playernum == 1)
		{
			//player1->stopAllActions();
			//player1->runAction(RepeatForever::create(walkupanim));
		}
		break;
	case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
		if (playernum == 1)
		{
			//player1->stopAllActions();
			//player1->runAction(RepeatForever::create(walkdownanim));
		}
		ymove -= 2;
		break;
	case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
		if (playernum == 1)
		{
			//player1->stopAllActions();
			//player1->runAction(RepeatForever::create(walkleftanim));
		}
		xmove -= 2;
		break;
	case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
		if (playernum == 1)
		{
			//player1->stopAllActions();
			//player1->runAction(RepeatForever::create(walkrightanim));
		}
		xmove += 2;
		break;
	case EventKeyboard::KeyCode::KEY_SPACE:
		if (playernum == 1)
		{
			//player1->stopAllActions();
			//player1->runAction(RepeatForever::create(paintanim));
		}
		button1 = true;
		xmove = 0;
		ymove = 0;
		break;
	}
	event->stopPropagation();
}

void ClientDemo::KeyRelease(EventKeyboard::KeyCode keyCode, Event* event)
{

	switch (keyCode){
	case EventKeyboard::KeyCode::KEY_UP_ARROW:
		if (playernum == 1)
		{
			//player1->stopAllActions();
		}
		ymove = 0;
		break;
	case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
		if (playernum == 1)
		{
			//player1->stopAllActions();
		}
		ymove = 0;
		break;
	case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
		if (playernum == 1)
		{
			//player1->stopAllActions();
		}
		xmove = 0;
		break;
	case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
		if (playernum == 1)
		{
			//player1->stopAllActions();
		}
		xmove = 0;
		break;
	case EventKeyboard::KeyCode::KEY_SPACE:
		if (playernum == 1)
		{
		//	player1->stopAllActions();
		}
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
	Vec2 position1 = player1->getPosition();
	Vec2 position2 = player2->getPosition();
	Vec2 position3 = player3->getPosition();
	Vec2 position4 = player4->getPosition();
	Vec2 samPosition = villain->getPosition();
	player1->setPosition(Vec2(p.p1x, p.p1y));
	player2->setPosition(Vec2(p.p2x, p.p2y));
	player3->setPosition(Vec2(p.p3x, p.p3y));
	player4->setPosition(Vec2(p.p4x, p.p4y));
	villain->setPosition(Vec2(p.vx, p.vy));


	//player1 animations
	//////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////
	if (player1->getPosition().y > position1.y && anim1a) {
		player1->stopAllActions();
		player1->runAction(RepeatForever::create(walkupanim));
		anim1a = false;
		anim1b = true;
		anim1c = true;
		anim1d = true;
	}
	else if (player1->getPosition().y < position1.y && anim1b) {
		player1->stopAllActions();
		player1->runAction(RepeatForever::create(walkdownanim));
		anim1a = true;
		anim1b = false;
		anim1c = true;
		anim1d = true;
	}
	else if (player1->getPosition().x < position1.x && player1->getPosition().y == position1.y && anim1c) {
		player1->stopAllActions();
		player1->runAction(RepeatForever::create(walkleftanim));
		anim1a = true;
		anim1b = true;
		anim1c = false;
		anim1d = true;
	}
	else if (player1->getPosition().x > position1.x && player1->getPosition().y == position1.y && anim1d) {
		player1->stopAllActions();
		player1->runAction(RepeatForever::create(walkrightanim));
		anim1a = true;
		anim1b = true;
		anim1c = true;
		anim1d = false;
	}
	else
	{
		//player1->stopAllActions();
	}
	//player1->stopAllActions();
	//tilevalues = p.tilevalues;
	
	
	//player2 animations
	//////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////
	if (player2->getPosition().y > position2.y && anim2a) {
		player2->stopAllActions();
		player2->runAction(RepeatForever::create(walkupanim1));
		anim2a = false;
		anim2b = true;
		anim2c = true;
		anim2d = true;
	}
	else if (player2->getPosition().y < position2.y && anim2b) {
		player2->stopAllActions();
		player2->runAction(RepeatForever::create(walkdownanim1));
		anim2a = true;
		anim2b = false;
		anim2c = true;
		anim2d = true;
	}
	else if (player2->getPosition().x < position2.x && player2->getPosition().y == position2.y && anim2c) {
		player2->stopAllActions();
		player2->runAction(RepeatForever::create(walkleftanim1));
		anim2a = true;
		anim2b = true;
		anim2c = false;
		anim2d = true;
	}
	else if (player2->getPosition().x > position2.x && player2->getPosition().y == position2.y && anim2d) {
		player2->stopAllActions();
		player2->runAction(RepeatForever::create(walkrightanim1));
		anim2a = true;
		anim2b = true;
		anim2c = true;
		anim2d = false;
	}
	else
	{
		//player2->stopAllActions();
	}


	//sam animations
	//////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////

	if (villain->getPosition().y < samPosition.y && sam1b) {
		villain->stopAllActions();
		villain->runAction(RepeatForever::create(samdownanim));
		sam1a = true;
		sam1b = false;
		sam1c = true;
		sam1d = true;
	}
	else if (villain->getPosition().y > samPosition.y && sam1a) {
		villain->stopAllActions();
		villain->runAction(RepeatForever::create(samupanim));
		sam1a = false;
		sam1b = true;
		sam1c = true;
		sam1d = true;
	}
	else if (villain->getPosition().x < samPosition.x && villain->getPosition().y == samPosition.y && sam1c) {
		villain->stopAllActions();
		villain->runAction(RepeatForever::create(samleftanim));
		sam1a = true;
		sam1b = true;
		sam1c = false;
		sam1d = true;
	}
	else if (villain->getPosition().x > samPosition.x && villain->getPosition().y == samPosition.y && sam1d) {
		villain->stopAllActions();
		villain->runAction(RepeatForever::create(samrightanim));
		sam1a = true;
		sam1b = true;
		sam1c = true;
		sam1d = false;
	}



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
				if (tilevalues[i][j] == 5)
				{
					tileptrarray[i][j]->setColor("black");
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