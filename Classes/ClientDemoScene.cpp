#include "ClientDemoScene.h"

USING_NS_CC;
//using boost::asio::ip::udp;
using boost::asio::ip::tcp;

#define AUDIO_ON 1 //toggles all audio on/off
#define MUSIC_ON 1 //toggles whether background music is on/off


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
	if (!Layer::init())
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
	playernum = setupdata.level;
	//myendpoint = resolver.resolve({ tcp::v4(), mycp1, mycp2 });
	CCLOG("setting player number");
	CCLOG(std::to_string(playernum).c_str());
	try
	{
		CCLOG("setting up tcp interface");
		CCLOG(mycp1);
		CCLOG(mycp2);
		//boost::asio::io_service io_service;
		io_service_p = new boost::asio::io_service;

		//udp::socket myudpsocket2(*io_service_p, udp::endpoint(udp::v4(), 0));
		//myudpsocketp = new udp::socket(*io_service_p, udp::endpoint(udp::v4(), 0));
		//udp::resolver resolver(*io_service_p);
		tcp::resolver resolver(*io_service_p);
		tcp::resolver::query query{ mycp1,mycp2 };
		tcp::resolver::iterator endpoint_iterator = resolver.resolve(query);

		mytcpsocketp = std::make_shared<tcp::socket>(*io_service_p);
		boost::asio::connect(*mytcpsocketp, endpoint_iterator);
		mytcpsocketp->set_option(tcp::no_delay(true));
		tcpsessionptr = new TCPCSession(mytcpsocketp, this);
		tcpsessionptr->do_read_header();
		//myudpinterfacep = new UDPInterface(*io_service_p, endpoint);
		//		doReceive();

	}
	catch (std::exception& e)
	{
		std::cerr << "Exception: " << e.what() << "\n";
		CCLOG("exception");
		CCLOG(e.what());
	}

	
	levelmanager.changeLevel(1);
	addChild(levelmanager.levelmap, -1000);
	bucketlayer = levelmanager.levelmap->getLayer("Paintbuckets");
	blockage = levelmanager.levelmap->getLayer("Collision");
	blockage->setVisible(false);
	

	player1 = Player::create(1);
	player1->setPlayernum(1);
	player1->getTexture()->setAliasTexParameters();
	player1->setAnchorPoint(Vec2(0.5, 0.0));
	player1->setPosition(Vec2(-50, 50));
	addChild(player1, 0);

	player2 = Player::create(2);
	player2->setPlayernum(2);
	player2->getTexture()->setAliasTexParameters();
	player2->setAnchorPoint(Vec2(0.5, 0.0));
	player2->setPosition(Vec2(-50, 100));
	addChild(player2, 0);

	player3 = Player::create(3);
	player3->setPlayernum(3);
	player3->getTexture()->setAliasTexParameters();
	player3->setAnchorPoint(Vec2(0.5, 0.0));
	player3->setPosition(Vec2(-50, 150));
	addChild(player3, 0);

	player4 = Player::create(4);
	player4->setPlayernum(4);
	player4->getTexture()->setAliasTexParameters();
	player4->setAnchorPoint(Vec2(0.5, 0.0));
	player4->setPosition(Vec2(-50, 200));
	addChild(player4, 0);

	players.push_back(player1);
	players.push_back(player2);
	players.push_back(player3);
	players.push_back(player4);

	villain = Villain::create();
	villain->getTexture()->setAliasTexParameters();
	villain->setAnchorPoint(Vec2(0.5, 0.0));
	villain->setPosition(Vec2(-250, -150));

	villain->setOpacity(0); ///////////////// NEW CODE
	addChild(villain, 0);

	pterodactyl = Pterodactyl::create();
	pterodactyl->getTexture()->setAliasTexParameters();
	pterodactyl->setAnchorPoint(Vec2(0.5, 0.0));
	pterodactyl->setPosition(Vec2(50, 50));
	pterodactyl->setOpacity(0);
	addChild(pterodactyl, 0);

	candy = Candy::create();
	candy->getTexture()->setAliasTexParameters();
	candy->setPosition(Vec2(-1000, -1000));
	candy->setAnchorPoint(Vec2(0.5, 0.0));
	addChild(candy, 0);

	// Player Label Creation
	p1CLabel = CCLabelTTF::create("P1", "fonts/Marker Felt.ttf", 9);
	//p1CLabel->enableStroke(ccColor3B(255,0,0),20.0, true);
	//p1CLabel->enableShadow(CCSize(1,0), 50.0, 0.0, true);
	p1CLabel->setPosition(Vec2(player1->getPositionX()+64, player1->getPositionY()+1));
	player1->addChild(p1CLabel,100);

	p2CLabel = CCLabelTTF::create("P2", "fonts/Marker Felt.ttf", 9);
	//p2CLabel->enableShadow(CCSize(1, 0), 50.0, 50.0, true);
	p2CLabel->setPosition(Vec2(player2->getPositionX()+64, player2->getPositionY()-48));
	player2->addChild(p2CLabel, 100);

	p3CLabel = CCLabelTTF::create("P3", "fonts/Marker Felt.ttf", 9);
	//p3CLabel->enableShadow(CCSize(1, 0), 50.0, 50.0, true);
	p3CLabel->setPosition(Vec2(player3->getPositionX()+64, player3->getPositionY()-104));
	p3CLabel->setAnchorPoint(Vec2(0.5, 0.0));
	player3->addChild(p3CLabel, 100);

	p4CLabel = CCLabelTTF::create("P4", "fonts/Marker Felt.ttf", 9);
	//p4CLabel->enableShadow(CCSize(1, 0), 50.0, 50.0, true);
	p4CLabel->setPosition(Vec2(player4->getPositionX()+64, player4->getPositionY()-154));
	p4CLabel->setAnchorPoint(Vec2(0.5, 0.0));
	player4->addChild(p4CLabel, 100);


	//Sprite* wallpainting = Sprite::create("res/sprites/objects/key_framed.png");
	//wallpainting->getTexture()->setAliasTexParameters();
	//wallpainting->setPosition(Vec2(320, 320));
	//wallpainting->setScale(1);
	//addChild(wallpainting, -999);

	tileHighlight = Sprite::create("res//sprites//select_tile.png");
	tileHighlight->setPosition(0, 0);
	addChild(tileHighlight, -900);

	for (Sprite* s : levelmanager.levelsprites)
	{
		addChild(s, -999);
	}

	// Initialize painting area 
	setupPaintTiles();
	
	if (AUDIO_ON)
	{
		//soundIDList index values are significant:
		// soundIDList[0] = paint
		// soundIDList[1] = player_hit
		// soundIDList[2] = sam_teleport
		// soundIDList[3] = sam_reappear
		// soundIDList[4] = sam_whistle
		// soundIDList[5] = ptero_swoop
		// soundIDList[6] = get_paint
		// soundIDList[7] = player_candy_pickup

		for (int i = 0; i < 3; i++)
		{
			pSFXTrigs[i].onBucket = false;
			pSFXTrigs[i].onGrid = false; //no grid-detection, yet.
		}

		experimental::AudioEngine::preload("\\res\\sound\\sfx\\paint.mp3");
		experimental::AudioEngine::preload("\\res\\sound\\sfx\\player_hit.mp3");
		experimental::AudioEngine::preload("\\res\\sound\\sfx\\sam_teleport.mp3");
		experimental::AudioEngine::preload("\\res\\sound\\sfx\\sam_reappear.mp3");
		experimental::AudioEngine::preload("\\res\\sound\\sfx\\sam_whistle.mp3");
		experimental::AudioEngine::preload("\\res\\sound\\sfx\\ptero_swoop.mp3");
		experimental::AudioEngine::preload("\\res\\sound\\sfx\\get_paint.mp3");
		experimental::AudioEngine::preload("\\res\\sound\\sfx\\player_candy_pickup.mp3");


		//can probably remove code chunk below by initialzing soundIDList to AudioEngine::INVALID_AUDIO_ID
		//then checking for that in audio sound checks in processSound()
		soundIDList.push_back(experimental::AudioEngine::play2d("\\res\\sound\\sfx\\paint.mp3", false, 0.0));
		soundIDList.push_back(experimental::AudioEngine::play2d("\\res\\sound\\sfx\\player_hit.mp3", false, 0.0));
		soundIDList.push_back(experimental::AudioEngine::play2d("\\res\\sound\\sfx\\sam_teleport.mp3", false, 0.0));
		soundIDList.push_back(experimental::AudioEngine::play2d("\\res\\sound\\sfx\\sam_reappear.mp3", false, 0.0));
		soundIDList.push_back(experimental::AudioEngine::play2d("\\res\\sound\\sfx\\sam_whistle.mp3", false, 0.0));
		soundIDList.push_back(experimental::AudioEngine::play2d("\\res\\sound\\sfx\\ptero_swoop.mp3", false, 0.0));
		soundIDList.push_back(experimental::AudioEngine::play2d("\\res\\sound\\sfx\\get_paint.mp3", false, 0.0));
		soundIDList.push_back(experimental::AudioEngine::play2d("\\res\\sound\\sfx\\player_candy_pickup.mp3", false, 0.0));

		for (int i = 0; i < soundIDList.size(); i++)
		{
			isSFXPlaying.push_back(false);
		}

		if (MUSIC_ON)
		{
			//run background music
			experimental::AudioEngine::preload("\\res\\sound\\music\\music_1.mp3");
			experimental::AudioEngine::play2d("\\res\\sound\\music\\music_1.mp3", true, 0.5);

		}
	}

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
	CCLOG("UPDATE DT");
	CCLOG(std::to_string(dt).c_str());

	io_service_p->poll();
	//CCLOG("POLLING");
	

	if (xmove || ymove || button1)
	{

		PlayerInputPacket p2 = PlayerInputPacket(playernum, xmove, ymove, button1);
		std::ostringstream os2;
		cereal::BinaryOutputArchive outar(os2);
		outar(p2);
		outstringbuffer = os2.str();
		CCLOG("outstringbuffer length");
		CCLOG(std::to_string(outstringbuffer.length()).c_str());
		/*
		std::memcpy(tcpsplitter.body(), outstringbuffer.c_str(), outstringbuffer.length());
		tcpsplitter.body_length(outstringbuffer.length());
		//tcpsplitter.decode_header();
		CCLOG("splitterlength");
		CCLOG(std::to_string(tcpsplitter.length()).c_str());
		CCLOG("outstringbuvver");
		CCLOG(outstringbuffer.c_str());
		CCLOG("bodylength");
		CCLOG(std::to_string(tcpsplitter.body_length()).c_str());
		CCLOG("body");
		CCLOG(tcpsplitter.body());
		std::string bodystring = std::string(tcpsplitter.body());
		CCLOG(bodystring.c_str());
		CCLOG("Sending packet");
		OutputDebugStringW(L"My output string.");
		OutputDebugStringA(bodystring.c_str());
		OutputDebugStringA(outstringbuffer.c_str());

		std::ofstream file("out.json");
		cereal::JSONOutputArchive archive(file);
		archive(p2);
		std::stringstream is2;
		cereal::BinaryInputArchive inar(is2);
		for (size_t i = 0; i < tcpsplitter.body_length(); i++)
		{
		// there has to be a better way vectorized? than using for loop!!!
		is2 << tcpsplitter.body()[i];
		}
		PlayerInputPacket inpacket(0, 0.0f, 0.0f, false);
		inar(inpacket);
		std::ofstream file2("out2.json");
		cereal::JSONOutputArchive archive2(file2);
		archive2(inpacket);

		////myudpsocketp->async_send_to(boost::asio::buffer(outstringbuffer), myendpoint, [this](boost::system::error_code /*ec*/
		//, std::size_t /*bytes_sent*/)
		//{
		//CCLOG("Sent packet");

		//});
		//mytcpsocketp->async_write_some(boost::asio::buffer(tcpsplitter.data(),tcpsplitter.length()), [this](boost::system::error_code /*ec*/, std::size_t /*bytes_sent*/)
		//	{
		//		CCLOG("Sent packet");

		//});
		//CCLOG("sentplayerpacket");
		//CCLOG(std::to_string(xmove).c_str());
		//CCLOG(std::to_string(ymove).c_str());

		CCLOG("sending packet");
		tcpsessionptr->writewithstringbuffer(outstringbuffer);
		io_service_p->poll();
	}


	tileHighlight->setOpacity(0);

	for (int i = 0; i < tilespritevector.size(); i++)
	{
		for (int j = 0; j < tilespritevector[i].size(); j++)
		{
			if (players[playernum - 1]->getPositionX() > tilespritevector[i][j]->getPositionX() - 12 && players[playernum - 1]->getPositionX() < tilespritevector[i][j]->getPositionX() + 12 && players[playernum - 1]->getPositionY() > tilespritevector[i][j]->getPositionY() - 12 && players[playernum - 1]->getPositionY() < tilespritevector[i][j]->getPositionY() + 12)
			{
				tileHighlight->setOpacity(255);
				tileHighlight->setPosition(tilespritevector[i][j]->getPositionX(), tilespritevector[i][j]->getPositionY());
			}
		}
	}


	for (Player* p : players)
	{
		p->setZOrder(-p->getPositionY());
	}

	if (levelmanager.currentlevel != 1) {
		villain->setOpacity(255);
		villain->setZOrder(-villain->getPositionY());
		pterodactyl->setOpacity(255);
		pterodactyl->setZOrder(-pterodactyl->getPositionY());
	}

	centerCamera();
}



void ClientDemo::KeyDown(EventKeyboard::KeyCode keyCode, Event* event)
{
	//std::string playerstring = "p";
	//playerstring += std::to_string(playernum).c_str();
	switch (keyCode) {
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
		xmove = 0;
		ymove = 0;
		space();
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

void ClientDemo::KeyRelease(EventKeyboard::KeyCode keyCode, Event* event)
{

	switch (keyCode) {
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


// This will convert the players coordinates into tile coordinates
CCPoint ClientDemo::plyrCoordToTileCoord(int playerNum)
{
	int newx = players[playerNum - 1]->getPositionX() + xmove;
	int newy = (levelmanager.levelmap->getMapSize().height*levelmanager.levelmap->getTileSize().height) - (players[playerNum - 1]->getPositionY() + ymove);
  	int tilex = newx / (levelmanager.levelmap->getTileSize().width);
	int tiley = newy / (levelmanager.levelmap->getTileSize().height);
	return(CCPoint(tilex,tiley));
}

int ClientDemo::getTileProperties(CCPoint tileCoord)
{
	if (tileCoord.x >= 0 && tileCoord.x <= levelmanager.levelmap->getMapSize().width && tileCoord.y >= 0 && tileCoord.y <= levelmanager.levelmap->getMapSize().height)
	{
		return (bucketlayer->getTileGIDAt(tileCoord));
	}
}

void ClientDemo::changeLabelColor(int bTile, int playerNum)
{
	if (playerNum == 1) {
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

				auto b2 = tilemapvals["Blue2"].asString();
				auto b3 = tilemapvals["Blue3"].asString();
				auto g1 = tilemapvals["Green1"].asString();
				auto g2 = tilemapvals["Green2"].asString();
				auto g3 = tilemapvals["Green3"].asString();
				
				
				if ("true" == r)
				{
					//p1CLabel->setString("Red");
					p1CLabel->setFontFillColor(ccc3(247, 52, 47));
					pSFXTrigs[0].onBucket = true; //0=p1, 1=p2, 2=p3, 3=p4
				}
				if ("true" == b)
				{
					//p1CLabel->setString("Blue");
					p1CLabel->setFontFillColor(ccc3(49, 58, 197));
					pSFXTrigs[0].onBucket = true;
				}
				if ("true" == y) {
					//p1CLabel->setString("Yellow");
					p1CLabel->setFontFillColor(ccc3(222, 244, 69));
					pSFXTrigs[0].onBucket = true;
				}
				if ("true" == o) {
					//p1CLabel->setString("Orange");
					p1CLabel->setFontFillColor(ccc3(234, 152, 46));
					pSFXTrigs[0].onBucket = true;
				}
				if ("true" == blk) {
					p1CLabel->setFontFillColor(ccc3(36, 33, 25));
					pSFXTrigs[0].onBucket = true;
				}
				
				if ("true" == b2) {
					p1CLabel->setFontFillColor(ccc3(4, 31, 131));
					pSFXTrigs[0].onBucket = true;
				}
				if ("true" == b3) {
					p1CLabel->setFontFillColor(ccc3(1, 16, 73));
					pSFXTrigs[0].onBucket = true;
				}
				if ("true" == g1) {
					p1CLabel->setFontFillColor(ccc3(2, 123, 36));
					pSFXTrigs[0].onBucket = true;
				}
				if ("true" == g2) {
					p1CLabel->setFontFillColor(ccc3(11, 187, 60));
					pSFXTrigs[0].onBucket = true;
				}
				if ("true" == g3) {
					p1CLabel->setFontFillColor(ccc3(47, 247, 145));
					pSFXTrigs[0].onBucket = true;
				}
			}
		}
	}
	else if (playerNum == 2) {
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
				
				auto b2 = tilemapvals["Blue2"].asString();
				auto b3 = tilemapvals["Blue3"].asString();
				auto g1 = tilemapvals["Green1"].asString();
				auto g2 = tilemapvals["Green2"].asString();
				auto g3 = tilemapvals["Green3"].asString();

				if ("true" == r)
				{
					p2CLabel->setFontFillColor(ccc3(247, 52, 47));
					pSFXTrigs[1].onBucket = true;
				}
				if ("true" == b)
				{
					p2CLabel->setFontFillColor(ccc3(49, 58, 197));
					pSFXTrigs[1].onBucket = true;
				}
				if ("true" == y) {
					p2CLabel->setFontFillColor(ccc3(222, 244, 69));
					pSFXTrigs[1].onBucket = true;
				}
				if ("true" == o) {
					p2CLabel->setFontFillColor(ccc3(234, 152, 46));
					pSFXTrigs[1].onBucket = true;
				}
				if ("true" == blk) {
					p1CLabel->setFontFillColor(ccc3(36, 33, 25));
					pSFXTrigs[1].onBucket = true;
				}
				
				if ("true" == b2) {
					p2CLabel->setFontFillColor(ccc3(4, 31, 131));
					pSFXTrigs[1].onBucket = true;
				}
				if ("true" == b3) {
					p2CLabel->setFontFillColor(ccc3(1, 16, 73));
					pSFXTrigs[1].onBucket = true;
				}
				if ("true" == g1) {
					p2CLabel->setFontFillColor(ccc3(2, 123, 36));
					pSFXTrigs[1].onBucket = true;
				}
				if ("true" == g2) {
					p2CLabel->setFontFillColor(ccc3(11, 187, 60));
					pSFXTrigs[1].onBucket = true;
				}
				if ("true" == g3) {
					p2CLabel->setFontFillColor(ccc3(47, 247, 145));
					pSFXTrigs[1].onBucket = true;
				}
			}
		}
	}
	else if (playerNum == 3) {
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
				
				auto b2 = tilemapvals["Blue2"].asString();
				auto b3 = tilemapvals["Blue3"].asString();
				auto g1 = tilemapvals["Green1"].asString();
				auto g2 = tilemapvals["Green2"].asString();
				auto g3 = tilemapvals["Green3"].asString();

				if ("true" == r)
				{
					p3CLabel->setFontFillColor(ccc3(247, 52, 47));
					pSFXTrigs[2].onBucket = true;
				}
				if ("true" == b)
				{
					p3CLabel->setFontFillColor(ccc3(49, 58, 197));
					pSFXTrigs[2].onBucket = true;
				}
				if ("true" == y) {
					p3CLabel->setFontFillColor(ccc3(222, 244, 69));
					pSFXTrigs[2].onBucket = true;
				}
				if ("true" == o) {
					p3CLabel->setFontFillColor(ccc3(234, 152, 46));
					pSFXTrigs[2].onBucket = true;
				}
				if ("true" == blk) {
					p1CLabel->setFontFillColor(ccc3(36, 33, 25));
					pSFXTrigs[2].onBucket = true;
				}
				
				if ("true" == b2) {
					p3CLabel->setFontFillColor(ccc3(4, 31, 131));
					pSFXTrigs[2].onBucket = true;
				}
				if ("true" == b3) {
					p3CLabel->setFontFillColor(ccc3(1, 16, 73));
					pSFXTrigs[2].onBucket = true;
				}
				if ("true" == g1) {
					p3CLabel->setFontFillColor(ccc3(2, 123, 36));
					pSFXTrigs[2].onBucket = true;
				}
				if ("true" == g2) {
					p3CLabel->setFontFillColor(ccc3(11, 187, 60));
					pSFXTrigs[2].onBucket = true;
				}
				if ("true" == g3) {
					p3CLabel->setFontFillColor(ccc3(47, 247, 145));
					pSFXTrigs[2].onBucket = true;
				}
			}
		}

	}
	else if (playerNum == 4) {
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

				auto b2 = tilemapvals["Blue2"].asString();
				auto b3 = tilemapvals["Blue3"].asString();
				auto g1 = tilemapvals["Green1"].asString();
				auto g2 = tilemapvals["Green2"].asString();
				auto g3 = tilemapvals["Green3"].asString();
				
				if ("true" == r)
				{
					p4CLabel->setFontFillColor(ccc3(247, 52, 47));
					pSFXTrigs[3].onBucket = true;
				}
				if ("true" == b)
				{
					p4CLabel->setFontFillColor(ccc3(49, 58, 197));
					pSFXTrigs[3].onBucket = true;
				}
				if ("true" == y) {
					p4CLabel->setFontFillColor(ccc3(222, 244, 69));
					pSFXTrigs[3].onBucket = true;
				}
				if ("true" == o) {
					p4CLabel->setFontFillColor(ccc3(234, 152, 46));
					pSFXTrigs[3].onBucket = true;
				}
				if ("true" == blk) {
					p1CLabel->setFontFillColor(ccc3(36, 33, 25));
					pSFXTrigs[3].onBucket = true;
				}

				if ("true" == b2) {
					p4CLabel->setFontFillColor(ccc3(4, 31, 131));
					pSFXTrigs[3].onBucket = true;
				}
				if ("true" == b3) {
					p4CLabel->setFontFillColor(ccc3(1, 16, 73));
					pSFXTrigs[3].onBucket = true;
				}
				if ("true" == g1) {
					p4CLabel->setFontFillColor(ccc3(2, 123, 36));
					pSFXTrigs[3].onBucket = true;
				}
				if ("true" == g2) {
					p4CLabel->setFontFillColor(ccc3(11, 187, 60));
					pSFXTrigs[3].onBucket = true;
				}
				if ("true" == g3) {
					p4CLabel->setFontFillColor(ccc3(47, 247, 145));
					pSFXTrigs[3].onBucket = true;
				}
				
			}
		}
	}
}


// Will check to see if you are on a bucket and change the color of the player's label
void ClientDemo::space()
{
		
		CCPoint tileCoord = plyrCoordToTileCoord(playernum);
		int bTile = getTileProperties(tileCoord);
		changeLabelColor(bTile, playernum);
}



void ClientDemo::processPacket(ServerPositionPacket p)
{
	if (p.tilevector.size() == 6 && levelmanager.puzzle.currenttilevector.size() != 6)
	{
		CCLOG("loading level 2");
		loadLevel(2);
	}
	else if (p.tilevector.size() == 9 && levelmanager.puzzle.currenttilevector.size() != 9)
	{
		loadLevel(1);
	}
	else if (p.tilevector.size() == 12 && levelmanager.puzzle.currenttilevector.size() != 12)
	{
		loadLevel(3);
	}
	
	CCLOG("updatedserverpacket");
	//CCLOG(std::to_string(p.p1x).c_str());
	//CCLOG(std::to_string(p.p2x).c_str());
	//CCLOG(std::to_string(p.p3x).c_str());
	//CCLOG(std::to_string(p.p4x).c_str());
	//CCLOG(std::to_string(p.vx).c_str());
	//CCLOG(std::to_string(tilevalues[0][0]).c_str());
	//CCLOG(std::to_string(p.tilevalues[0][0]).c_str());

	player1->setPosition(Vec2(p.p1x, p.p1y));
	player2->setPosition(Vec2(p.p2x, p.p2y));
	player3->setPosition(Vec2(p.p3x, p.p3y));
	player4->setPosition(Vec2(p.p4x, p.p4y));
	villain->setPosition(Vec2(p.vx, p.vy));
	pterodactyl->setPosition(Vec2(p.ptx, p.pty));
	candy->setPosition(Vec2(p.candyx, p.candyy));
	//tilevalues = p.tilevalues;
	//player1 animations

	std::string p1anims = animationmanager.stringFromChar(p.p1anim);
	std::string p2anims = animationmanager.stringFromChar(p.p2anim);
	std::string p3anims = animationmanager.stringFromChar(p.p3anim);
	std::string p4anims = animationmanager.stringFromChar(p.p4anim);
	std::string vanims = animationmanager.stringFromChar(p.vanim);
	std::string ptanims = animationmanager.stringFromChar(p.ptanim);

	//////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////
	if (p.p1anim != 0 && player1->getAnim() != p1anims) {
		player1->stopAllActions();
		player1->runAction(RepeatForever::create(animationmanager.animationmap.at(p1anims)));
		player1->setAnim(p1anims);
	}
	if (p.p2anim != 0 && player2->getAnim() != p2anims) {
		player2->stopAllActions();
		player2->runAction(RepeatForever::create(animationmanager.animationmap.at(p2anims)));
		player2->setAnim(p2anims);
	}
	if (p.p3anim != 0 && player3->getAnim() != p3anims) {
		player3->stopAllActions();
		player3->runAction(RepeatForever::create(animationmanager.animationmap.at(p3anims)));
		player3->setAnim(p3anims);
	}
	if (p.p4anim != 0 && player4->getAnim() != p4anims) {
		player4->stopAllActions();
		player4->runAction(RepeatForever::create(animationmanager.animationmap.at(p4anims)));
		player4->setAnim(p4anims);
	}
	if (p.vanim != 0 && villain->getAnim() != vanims) {
		villain->stopAllActions();
		villain->runAction(RepeatForever::create(animationmanager.animationmap.at(vanims)));
		villain->setAnim(vanims);
	}
	if (p.ptanim != 0 && pterodactyl->getAnim() != ptanims) {
		pterodactyl->stopAllActions();
		pterodactyl->runAction(RepeatForever::create(animationmanager.animationmap.at(ptanims)));
		pterodactyl->setAnim(ptanims);
	}


for (int i = 0; i < p.tilevector.size(); i++)
	{
		for (int j = 0; j < p.tilevector[i].size(); j++)
		{
			if (levelmanager.puzzle.currenttilevector[i][j] != p.tilevector[i][j])
			{
				levelmanager.puzzle.currenttilevector[i][j] = p.tilevector[i][j];
				if (levelmanager.puzzle.currenttilevector[i][j] == 1)
				{
					tilespritevector[i][j]->setColor("clear");
					tilespritevector[i][j]->refreshColor();
				}
				if (levelmanager.puzzle.currenttilevector[i][j] == 2)
				{
					tilespritevector[i][j]->setColor("red");
					tilespritevector[i][j]->refreshColor();
				}
				if (levelmanager.puzzle.currenttilevector[i][j] == 3)
				{
					tilespritevector[i][j]->setColor("blue");
					tilespritevector[i][j]->refreshColor();
				}
				if (levelmanager.puzzle.currenttilevector[i][j] == 4)
				{
					tilespritevector[i][j]->setColor("yellow");
					tilespritevector[i][j]->refreshColor();
				}
				if (levelmanager.puzzle.currenttilevector[i][j] == 5)
				{
					tilespritevector[i][j]->setColor("orange");
					tilespritevector[i][j]->refreshColor();
				}
				if (levelmanager.puzzle.currenttilevector[i][j] == 6)
				{
					tilespritevector[i][j]->setColor("black");
					tilespritevector[i][j]->refreshColor();
				}

				if (levelmanager.puzzle.currenttilevector[i][j] == 7)
				{
					tilespritevector[i][j]->setColor("blue2");
					tilespritevector[i][j]->refreshColor();
				}
				if (levelmanager.puzzle.currenttilevector[i][j] == 8)
				{
					tilespritevector[i][j]->setColor("blue3");
					tilespritevector[i][j]->refreshColor();
				}
				if (levelmanager.puzzle.currenttilevector[i][j] == 9)
				{
					tilespritevector[i][j]->setColor("green1");
					tilespritevector[i][j]->refreshColor();
				}
				if (levelmanager.puzzle.currenttilevector[i][j] == 10)
				{
					tilespritevector[i][j]->setColor("green2");
					tilespritevector[i][j]->refreshColor();
				}
				if (levelmanager.puzzle.currenttilevector[i][j] == 11)
				{
					tilespritevector[i][j]->setColor("green3");
					tilespritevector[i][j]->refreshColor();
				}

				if (levelmanager.puzzle.currenttilevector[i][j] == 20)
				{
					tilespritevector[i][j]->setColor("Xred");
					tilespritevector[i][j]->refreshColor();
				}
				if (levelmanager.puzzle.currenttilevector[i][j] == 30)
				{
					tilespritevector[i][j]->setColor("Xblue");
					tilespritevector[i][j]->refreshColor();
				}
				if (levelmanager.puzzle.currenttilevector[i][j] == 40)
				{
					tilespritevector[i][j]->setColor("Xyellow");
					tilespritevector[i][j]->refreshColor();
				}
				if (levelmanager.puzzle.currenttilevector[i][j] == 50)
				{
					tilespritevector[i][j]->setColor("Xorange");
					tilespritevector[i][j]->refreshColor();
				}
				if (levelmanager.puzzle.currenttilevector[i][j] == 60)
				{
					tilespritevector[i][j]->setColor("Xblack");
					tilespritevector[i][j]->refreshColor();
				}

				if (levelmanager.puzzle.currenttilevector[i][j] == 70)
				{
					tilespritevector[i][j]->setColor("Xblue2");
					tilespritevector[i][j]->refreshColor();
				}
				if (levelmanager.puzzle.currenttilevector[i][j] == 71)
				{
					tilespritevector[i][j]->setColor("Xblue3");
					tilespritevector[i][j]->refreshColor();
				}
				if (levelmanager.puzzle.currenttilevector[i][j] == 72)
				{
					tilespritevector[i][j]->setColor("Xgreen1");
					tilespritevector[i][j]->refreshColor();
				}
				if (levelmanager.puzzle.currenttilevector[i][j] == 73)
				{
					tilespritevector[i][j]->setColor("Xgreen2");
					tilespritevector[i][j]->refreshColor();
				}
				if (levelmanager.puzzle.currenttilevector[i][j] == 74)
				{
					tilespritevector[i][j]->setColor("Xgreen3");
					tilespritevector[i][j]->refreshColor();
				}
			}
		}
	}
	//CCLOG(std::to_string(currenttilevector[0][0]).c_str());
	//CCLOG(std::to_string(p.tilevector[0][0]).c_str());

	if (AUDIO_ON)
	{
		processSound(p);
	}
}
/*
void ClientDemo::doReceive()
{
mytcpsocketp->async_read_some(
boost::asio::buffer(indata, max_length), [this](boost::system::error_code ec, std::size_t bytes_recvd)
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
}*/

void ClientDemo::loadLevel(int level)
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

	blockage = levelmanager.levelmap->getLayer("Collision");
	blockage->setVisible(false);
	villain->setPosition(Vec2(250, 150));
	
	bucketlayer = levelmanager.levelmap->getLayer("Paintbuckets");

	for (Sprite* s : levelmanager.levelsprites)
	{
		addChild(s, -999);
	}

	setupPaintTiles();
}

void ClientDemo::setupPaintTiles()
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
			tilespritevector[i][j]->debugDraw(false);
			addChild(tilespritevector[i][j], -999);
		}
	}

}


void ClientDemo::centerCamera()
{
	CCCamera::getDefaultCamera()->setPosition(players[playernum - 1]->getPosition());
}

void ClientDemo::processSound(ServerPositionPacket &p) {

	//===========================================================
	//					ISSUES AND BUGS
	//===========================================================
	//	1. Still need to check if player is on paint grid before 
	//	playing paint sound.
	//
	//	2. Volume of various SFX need a little more adjustment.
	//
	//	3. Pterodactyl swooping is still not QUITE there yet.
	//	Sound and pacing need a little work.
	//
	//	4. Candy-related SFX is not implemented yet.
	//
	//	5. Need to add level-changing SFX. Will do when Jocelyn
	//	adds menus, screens and such.
	//
	//	6. Paint SFX needs to be a little shorter, and only sound
	//	like one stroke instead of two.
	//
	//	7. Sam hitting a player triggers sfx even if they're idle
	//	or have no tiles painted. Will look into solutions, but not
	//	a priority.
	//============================================================

	// GOOD REFERENCES FOR AUDIO CODING
	// http://dan.clarke.name/2011/07/cocos2d-sound-in-android-tutorial/
	// https://searchcode.com/codesearch/view/95985619/

	//===========================================================
	//        NON-ANIMATION BASED AUDIO CODE
	//===========================================================

	//If Sam touches a player
	if (pIFrames[0] == 0)
	{
		if (abs(p.vx - p.p1x) < 5 && abs(p.vy - p.p1y) < 5)
		{
			if (false == isSFXPlaying[1])
			{
				soundIDList[1] = experimental::AudioEngine::play2d("\\res\\sound\\sfx\\player_hit.mp3");
				isSFXPlaying[1] = true;
				experimental::AudioEngine::setFinishCallback(soundIDList[1], [&](int id, const std::string& filePath)
				{
					isSFXPlaying[1] = false;
				});
				pIFrames[0] = 3 * 30; //3 seconds of iframes at 30 fps
			}
		}
	}
	if (pIFrames[1] == 0)
	{
		if (abs(p.vx - p.p2x) < 5 && abs(p.vy - p.p2y) < 5)
		{
			if (false == isSFXPlaying[1])
			{
				soundIDList[1] = experimental::AudioEngine::play2d("\\res\\sound\\sfx\\player_hit.mp3");
				isSFXPlaying[1] = true;
				experimental::AudioEngine::setFinishCallback(soundIDList[1], [&](int id, const std::string& filePath)
				{
					isSFXPlaying[1] = false;
				});
				pIFrames[1] = 3 * 30; //3 seconds of iframes at 30 fps
			}
		}
	}

	if (pIFrames[2] == 0)
	{
		if (abs(p.vx - p.p3x) < 5 && abs(p.vy - p.p3y) < 5)
		{
			if (false == isSFXPlaying[1])
			{
				soundIDList[1] = experimental::AudioEngine::play2d("\\res\\sound\\sfx\\player_hit.mp3");
				isSFXPlaying[1] = true;
				experimental::AudioEngine::setFinishCallback(soundIDList[1], [&](int id, const std::string& filePath)
				{
					isSFXPlaying[1] = false;
				});
				pIFrames[2] = 3 * 30; //3 seconds of iframes at 30 fps
			}
		}
	}

	if (pIFrames[3] == 0)
	{
		if (abs(p.vx - p.p4x) < 5 && abs(p.vy - p.p4y) < 5)
		{
			if (false == isSFXPlaying[1])
			{
				soundIDList[1] = experimental::AudioEngine::play2d("\\res\\sound\\sfx\\player_hit.mp3");
				isSFXPlaying[1] = true;
				experimental::AudioEngine::setFinishCallback(soundIDList[1], [&](int id, const std::string& filePath)
				{
					isSFXPlaying[1] = false;
				});
				pIFrames[3] = 3 * 30; //3 seconds of iframes at 30 fps
			}
		}
	}
	//If Sam touches a player - end

	//===========================================================
	//    END OF NON-ANIMATION BASED AUDIO CODE
	//===========================================================





	//===========================================================
	//        ANIMATION-BASED AUDIO CODE
	//===========================================================

	// soundIDList[0] = paint
	// soundIDList[1] = player_hit
	// soundIDList[2] = sam_teleport
	// soundIDList[3] = sam_reappear
	// soundIDList[4] = sam_whistle
	// soundIDList[5] = ptero_swoop
	// soundIDList[6] = get_paintc
	// soundIDList[7] = player_candy_pickup


	//switch used here in case further animation states are created. modular switch-cases superior.
	switch (p.p1anim) {
	case 5: //p1paint

		if (pSFXTrigs[0].onBucket == true) //if the player is on a bucket
		{
			if (isSFXPlaying[6] == false)
			{
				soundIDList[6] = experimental::AudioEngine::play2d("\\res\\sound\\sfx\\get_paint.mp3", false, 0.5);
				isSFXPlaying[6] = true;
				experimental::AudioEngine::setFinishCallback(soundIDList[6], [&](int id, const std::string& filePath)
				{
					isSFXPlaying[6] = false;
				});
			}
			pSFXTrigs[0].onBucket = false; //need better way to check if theyre onbucket
		}
		else
		{
			if (false == isSFXPlaying[0])
			{
				if (isSFXPlaying[6] == false)
				{
					soundIDList[0] = experimental::AudioEngine::play2d("\\res\\sound\\sfx\\paint.mp3");
					isSFXPlaying[0] = true;
					experimental::AudioEngine::setFinishCallback(soundIDList[0], [&](int id, const std::string& filePath)
					{
						isSFXPlaying[0] = false;
					});
				}
			}
		}
		break;
	default: break;
	}
	switch (p.p2anim) {
	case 11: //p1paint
		if (pSFXTrigs[1].onBucket == true) //if the player is on a bucket
		{
			if (isSFXPlaying[6] == false)
			{
				soundIDList[6] = experimental::AudioEngine::play2d("\\res\\sound\\sfx\\get_paint.mp3", false, 0.5);
				isSFXPlaying[6] = true;
				experimental::AudioEngine::setFinishCallback(soundIDList[6], [&](int id, const std::string& filePath)
				{
					isSFXPlaying[6] = false;
				});
			}
			pSFXTrigs[1].onBucket = false; 
		}
		else
		{
			if (false == isSFXPlaying[0])
			{
				if (isSFXPlaying[6] == false)
				{
					soundIDList[0] = experimental::AudioEngine::play2d("\\res\\sound\\sfx\\paint.mp3");
					isSFXPlaying[0] = true;
					experimental::AudioEngine::setFinishCallback(soundIDList[0], [&](int id, const std::string& filePath)
					{
						isSFXPlaying[0] = false;
					});
				}
			}
		}
		break;
	default: break;
	}
	switch (p.p3anim) {
	case 17: //p1paint
		if (pSFXTrigs[2].onBucket == true) //if the player is on a bucket
		{
			if (isSFXPlaying[6] == false)
			{
				soundIDList[6] = experimental::AudioEngine::play2d("\\res\\sound\\sfx\\get_paint.mp3", false, 0.5);
				isSFXPlaying[6] = true;
				experimental::AudioEngine::setFinishCallback(soundIDList[6], [&](int id, const std::string& filePath)
				{
					isSFXPlaying[6] = false;
				});
			}
			pSFXTrigs[2].onBucket = false; 
		}
		else
		{
			if (false == isSFXPlaying[0])
			{
				if (isSFXPlaying[6] == false)
				{
					soundIDList[0] = experimental::AudioEngine::play2d("\\res\\sound\\sfx\\paint.mp3");
					isSFXPlaying[0] = true;
					experimental::AudioEngine::setFinishCallback(soundIDList[0], [&](int id, const std::string& filePath)
					{
						isSFXPlaying[0] = false;
					});
				}
			}
		}
		break;
	default: break;
	}
	switch (p.p4anim) {
	case 23: //p1paint
		if (pSFXTrigs[3].onBucket == true) //if the player is on a bucket
		{
			if (isSFXPlaying[6] == false)
			{
				soundIDList[6] = experimental::AudioEngine::play2d("\\res\\sound\\sfx\\get_paint.mp3", false, 0.5);
				isSFXPlaying[6] = true;
				experimental::AudioEngine::setFinishCallback(soundIDList[6], [&](int id, const std::string& filePath)
				{
					isSFXPlaying[6] = false;
				});
			}
			pSFXTrigs[3].onBucket = false;
		}
		else
		{
			if (false == isSFXPlaying[0])
			{
				if (isSFXPlaying[6] == false)
				{
					soundIDList[0] = experimental::AudioEngine::play2d("\\res\\sound\\sfx\\paint.mp3");
					isSFXPlaying[0] = true;
					experimental::AudioEngine::setFinishCallback(soundIDList[0], [&](int id, const std::string& filePath)
					{
						isSFXPlaying[0] = false;
					});
				}
			}
		}
		break;
	default: break;
	}
	switch (p.vanim) {
	case 29: //samwarp
		if (false == isSFXPlaying[2])
		{
			soundIDList[2] = experimental::AudioEngine::play2d("\\res\\sound\\sfx\\sam_teleport.mp3");
			isSFXPlaying[2] = true;
			experimental::AudioEngine::setFinishCallback(soundIDList[2], [&](int id, const std::string& filePath)
			{
				isSFXPlaying[2] = false;
			});
		}
		break;
	case 30: //samappear
		if (false == isSFXPlaying[3])
		{
			soundIDList[3] = experimental::AudioEngine::play2d("\\res\\sound\\sfx\\sam_reappear.mp3");
			isSFXPlaying[3] = true;
			experimental::AudioEngine::setFinishCallback(soundIDList[3], [&](int id, const std::string& filePath)
			{
				isSFXPlaying[3] = false;
			});
		}
		break;
	case 31: //samwhistle
		if (false == isSFXPlaying[4])
		{
			soundIDList[4] = experimental::AudioEngine::play2d("\\res\\sound\\sfx\\sam_whistle.mp3");
			isSFXPlaying[4] = true;
			experimental::AudioEngine::setFinishCallback(soundIDList[4], [&](int id, const std::string& filePath)
			{
				isSFXPlaying[4] = false;
			});
		}
		break;
	default: break;
	}

	switch (p.ptanim) {
	case 33: //pteraleft
		if (false == isSFXPlaying[5])
		{
			//change ptero_swoop to have 2 second silence after it plays
			soundIDList[5] = experimental::AudioEngine::play2d("\\res\\sound\\sfx\\ptero_swoop.mp3", true, 0.1);
			isSFXPlaying[5] = true;
			//experimental::AudioEngine::setFinishCallback(soundIDList[5], [&](int id, const std::string& filePath)
			//{
			//	isSFXPlaying[5] = false;
			//});
		}
		break;
	default: break;
	}

	//===========================================================
	//     END OF ANIMATION-BASED AUDIO CODE
	//===========================================================
	for (int i = 0; i < 3; i++)
	{
		if (pIFrames[i] > 0)
			pIFrames[i]--;
	}
}


ClientDemo::~ClientDemo()
{

	if (tcpsessionptr)
		delete tcpsessionptr;

	if (io_service_p)
	{
		// this causes a crash need to investigate
		//delete io_service_p;
		io_service_p = nullptr;
	}

	//if (myudpinterfacep)
	//	delete myudpinterfacep;

}