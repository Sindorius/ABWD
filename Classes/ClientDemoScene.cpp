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
	/*
	auto director = Director::getInstance();
	auto glview = director->getOpenGLView();
	float animint = director->getAnimationInterval();
	CCLOG("from animint");
	CCLOG(std::to_string(animint).c_str());
	int refreshrate = glview->getRunningRefreshRate();
	if (refreshrate == 59)
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
	if (newswapinterval < 1)
	{
		newswapinterval = 1;
	}
	swapframes = newswapinterval;
	swapframecounter = newswapinterval;

	CCLOG("from newswapinterval");
	CCLOG(std::to_string(newswapinterval).c_str());
	*/

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
	p1CLabel->enableStroke(ccColor3B(255,0,0),20.0, true);
	p1CLabel->enableShadow(CCSize(1,0), 50.0, 0.0, true);
	p1CLabel->setPosition(Vec2(player1->getPositionX()+64, player1->getPositionY()+1));
	player1->addChild(p1CLabel,100);

	p2CLabel = CCLabelTTF::create("P2", "fonts/Marker Felt.ttf", 9);
	p2CLabel->enableShadow(CCSize(1, 0), 50.0, 50.0, true);
	p2CLabel->setPosition(Vec2(player2->getPositionX()+64, player2->getPositionY()-48));
	player2->addChild(p2CLabel, 100);

	p3CLabel = CCLabelTTF::create("P3", "fonts/Marker Felt.ttf", 9);
	p3CLabel->enableShadow(CCSize(1, 0), 50.0, 50.0, true);
	p3CLabel->setPosition(Vec2(player3->getPositionX()+64, player3->getPositionY()-104));
	p3CLabel->setAnchorPoint(Vec2(0.5, 0.0));
	player3->addChild(p3CLabel, 100);

	p4CLabel = CCLabelTTF::create("P4", "fonts/Marker Felt.ttf", 9);
	p4CLabel->enableShadow(CCSize(1, 0), 50.0, 50.0, true);
	p4CLabel->setPosition(Vec2(player4->getPositionX()+64, player4->getPositionY()-154));
	p4CLabel->setAnchorPoint(Vec2(0.5, 0.0));
	player4->addChild(p4CLabel, 100);
	
	tileHighlight = Sprite::create("res//sprites//select_tile.png");
	tileHighlight->setPosition(0, 0);
	addChild(tileHighlight, -900);

	winSizeWidth = CCDirector::sharedDirector()->getWinSize().width / 2; // CODE TO TRY
	winSizeHeight = CCDirector::sharedDirector()->getWinSize().height / 2; // CODE TO TRY

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
		// soundIDList[1] = sam_playerhit
		// soundIDList[2] = sam_teleport
		// soundIDList[3] = sam_reappear
		// soundIDList[4] = sam_whistle
		// soundIDList[5] = ptero_swoop
		// soundIDList[6] = get_paint
		// soundIDList[7] = player_candy_pickup
		// soundIDList[8] = sam_munch
		// soundIDList[9] = player_candy_lost
		// soundIDList[10] = puzzle_solved
		// soundIDList[11] = ptero_swoop_fast

		//initalize player sfx triggers to false
		for (int i = 0; i < 3; i++)
		{
			gSFX.pTrigs[i].onBucket = false;
			gSFX.pTrigs[i].onGrid = false;
			gSFX.pTrigs[i].gotCandy = false;
			gSFX.pTrigs[i].lostCandy = false;
		}
		gSFX.levelChange = false;

		experimental::AudioEngine::preload("\\res\\sound\\sfx\\paint.mp3");
		experimental::AudioEngine::preload("\\res\\sound\\sfx\\sam_playerhit.mp3");
		experimental::AudioEngine::preload("\\res\\sound\\sfx\\sam_teleport.mp3");
		experimental::AudioEngine::preload("\\res\\sound\\sfx\\sam_reappear.mp3");
		experimental::AudioEngine::preload("\\res\\sound\\sfx\\sam_whistle.mp3");
		experimental::AudioEngine::preload("\\res\\sound\\sfx\\ptero_swoop.mp3");
		experimental::AudioEngine::preload("\\res\\sound\\sfx\\get_paint.mp3");
		experimental::AudioEngine::preload("\\res\\sound\\sfx\\player_candy_pickup.mp3");
		experimental::AudioEngine::preload("\\res\\sound\\sfx\\sam_munch.mp3");
		experimental::AudioEngine::preload("\\res\\sound\\sfx\\player_candy_lost.mp3");
		experimental::AudioEngine::preload("\\res\\sound\\sfx\\puzzle_solved.mp3");
		experimental::AudioEngine::preload("\\res\\sound\\sfx\\ptero_swoop_fast.mp3");
		experimental::AudioEngine::preload("\\res\\sound\\sfx\\ptero_playerhit.mp3");


		//can probably remove code chunk below by initialzing soundIDList to AudioEngine::INVALID_AUDIO_ID
		//then checking for that in audio sound checks in processSound()
		soundIDList.push_back(experimental::AudioEngine::play2d("\\res\\sound\\sfx\\paint.mp3", false, 0.0f));
		soundIDList.push_back(experimental::AudioEngine::play2d("\\res\\sound\\sfx\\sam_playerhit.mp3", false, 0.0f));
		soundIDList.push_back(experimental::AudioEngine::play2d("\\res\\sound\\sfx\\sam_teleport.mp3", false, 0.0f));
		soundIDList.push_back(experimental::AudioEngine::play2d("\\res\\sound\\sfx\\sam_reappear.mp3", false, 0.0f));
		soundIDList.push_back(experimental::AudioEngine::play2d("\\res\\sound\\sfx\\sam_whistle.mp3", false, 0.0f));
		soundIDList.push_back(experimental::AudioEngine::play2d("\\res\\sound\\sfx\\ptero_swoop.mp3", false, 0.0f));
		soundIDList.push_back(experimental::AudioEngine::play2d("\\res\\sound\\sfx\\get_paint.mp3", false, 0.0f));
		soundIDList.push_back(experimental::AudioEngine::play2d("\\res\\sound\\sfx\\player_candy_pickup.mp3", false, 0.0f));
		soundIDList.push_back(experimental::AudioEngine::play2d("\\res\\sound\\sfx\\sam_munch.mp3", false, 0.0f));
		soundIDList.push_back(experimental::AudioEngine::play2d("\\res\\sound\\sfx\\player_candy_lost.mp3", false, 0.0f));
		soundIDList.push_back(experimental::AudioEngine::play2d("\\res\\sound\\sfx\\puzzle_solved.mp3", false, 0.0f));
		soundIDList.push_back(experimental::AudioEngine::play2d("\\res\\sound\\sfx\\ptero_swoop_fast.mp3", false, 0.0f));
		soundIDList.push_back(experimental::AudioEngine::play2d("\\res\\sound\\sfx\\ptero_playerhit.mp3", false, 0.0f));

		for (unsigned int i = 0; i < soundIDList.size(); i++)
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

void ClientDemo::update(float dt)
{
	
	/*if(!alternate)
	{
		alternate = true;
		io_service_p->poll();
		return;
	}
	else
	{
		alternate = false;
	}*/
	/*
	if (--swapframecounter <= 0)
	{
		swapframecounter = swapframes;
	}
	else
	{
		return;
	}
	*/
	// NEW CODE TO TRY
	if (levelmanager.currentlevel > 4)
	{
		auto GOScene = GameOver::createGameOver();
		CCDirector::getInstance()->replaceScene(GOScene);
	}
	//////////////////

	players[playernum - 1]->setPositionX(players[playernum - 1]->getPositionX() + xmove * players[playernum - 1]->speedboost);
	players[playernum - 1]->setPositionY(players[playernum - 1]->getPositionY() + ymove * players[playernum - 1]->speedboost);

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
	
		CCLOG("sending packet");
		tcpsessionptr->writewithstringbuffer(outstringbuffer);
		io_service_p->poll_one();
	}


	tileHighlight->setOpacity(0);

	for (unsigned int i = 0; i < tilespritevector.size(); i++)
	{
		for (unsigned int j = 0; j < tilespritevector[i].size(); j++)
		{
			if (players[playernum - 1]->getPositionX() > tilespritevector[i][j]->getPositionX() - 12 && players[playernum - 1]->getPositionX() < tilespritevector[i][j]->getPositionX() + 12 && players[playernum - 1]->getPositionY() > tilespritevector[i][j]->getPositionY() - 12 && players[playernum - 1]->getPositionY() < tilespritevector[i][j]->getPositionY() + 12)
			{
				tileHighlight->setOpacity(255);
				tileHighlight->setPosition(tilespritevector[i][j]->getPositionX(), tilespritevector[i][j]->getPositionY());
				gSFX.pTrigs[playernum - 1].onGrid = true;
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

	////////////////////////////////////////////////////// NEW CODE
	if (transitionManager.timer_status())
	{
		NotInTransition = true;

		for (Sprite* ts : transitionManager.transitionSprite)
		{
			removeChild(ts);
		}
	}
	//////////
	centerCamera();
}



void ClientDemo::processPacket(ServerPositionPacket p)
{
	
	for (ServerMessage msg : p.messagevector)
	{
		processServerMessage(msg);
	}
	
	/* move players, with some client side prediction of your own character*/
	if (playernum == 1)
	{
		if (abs(p.p1x - players[0]->getPositionX()) > 8 || abs(p.p1y - players[0]->getPositionY()) > 8)
		{
			float diffx = (player1->getPositionX() - p.p1x)/2.0f;
			float diffy = (player1->getPositionY() - p.p1y)/2.0f;

			player1->setPosition(Vec2(p.p1x + diffx, p.p1y + diffy));
		}
	}
	else{ player1->setPosition(Vec2(p.p1x, p.p1y)); }
	if (playernum == 2)
	{
		if (abs(p.p2x - players[playernum - 1]->getPositionX()) > 8 || abs(p.p2y - players[playernum - 1]->getPositionY()) > 8)
		{
			float diffx = (player2->getPositionX() - p.p2x) / 2.0f;
			float diffy = (player2->getPositionY() - p.p2y) / 2.0f;

			player2->setPosition(Vec2(p.p2x + diffx, p.p2y + diffy));
		}
	}
	else { player2->setPosition(Vec2(p.p2x, p.p2y)); }
	if (playernum == 3)
	{
		if (abs(p.p3x - players[2]->getPositionX()) > 8 || abs(p.p3y - players[2]->getPositionY()) > 8)
		{
			float diffx = (player3->getPositionX() - p.p3x) / 2.0f;
			float diffy = (player3->getPositionY() - p.p3y) / 2.0f;

			player3->setPosition(Vec2(p.p3x + diffx, p.p3y + diffy));
		}
	}
	else { player3->setPosition(Vec2(p.p3x, p.p3y)); }
	if (playernum == 4)
	{
		if (abs(p.p4x - players[3]->getPositionX()) > 8 || abs(p.p4y - players[3]->getPositionY()) > 8)
		{
			float diffx = (player4->getPositionX() - p.p4x) / 2.0f;
			float diffy = (player4->getPositionY() - p.p4y) / 2.0f;

			player4->setPosition(Vec2(p.p4x + diffx, p.p4y + diffy));
		}
	}
	else { player4->setPosition(Vec2(p.p4x, p.p4y)); }


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
	
	updateTilesFromPacket(p);
	//CCLOG(std::to_string(currenttilevector[0][0]).c_str());
	//CCLOG(std::to_string(p.tilevector[0][0]).c_str());

	if (AUDIO_ON)
	{
		processSound(p);
	}
}

void ClientDemo::updateTilesFromPacket(ServerPositionPacket p)
{

	for (unsigned int i = 0; i < p.tilevector.size(); i++)
	{
		for (unsigned int j = 0; j < p.tilevector[i].size(); j++)
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
				// NEW CODE HERE
				if (levelmanager.puzzle.currenttilevector[i][j] == 12)
				{
					tilespritevector[i][j]->setColor("white");
					tilespritevector[i][j]->refreshColor();
				}
				if (levelmanager.puzzle.currenttilevector[i][j] == 13)
				{
					tilespritevector[i][j]->setColor("grey1");
					tilespritevector[i][j]->refreshColor();
				}
				if (levelmanager.puzzle.currenttilevector[i][j] == 14)
				{
					tilespritevector[i][j]->setColor("grey2");
					tilespritevector[i][j]->refreshColor();
				}
				if (levelmanager.puzzle.currenttilevector[i][j] == 15)
				{
					tilespritevector[i][j]->setColor("red2");
					tilespritevector[i][j]->refreshColor();
				}
				if (levelmanager.puzzle.currenttilevector[i][j] == 16)
				{
					tilespritevector[i][j]->setColor("purple1");
					tilespritevector[i][j]->refreshColor();
				}
				if (levelmanager.puzzle.currenttilevector[i][j] == 17)
				{
					tilespritevector[i][j]->setColor("red1");
					tilespritevector[i][j]->refreshColor();
				}
				///////////////
				if (levelmanager.puzzle.currenttilevector[i][j] == 20)
				{
					tilespritevector[i][j]->setColor("Xred1");
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
				if (levelmanager.puzzle.currenttilevector[i][j] == 75)
				{
					tilespritevector[i][j]->setColor("Xwhite");
					tilespritevector[i][j]->refreshColor();
				}
				if (levelmanager.puzzle.currenttilevector[i][j] == 76)
				{
					tilespritevector[i][j]->setColor("Xgrey1");
					tilespritevector[i][j]->refreshColor();
				}
				if (levelmanager.puzzle.currenttilevector[i][j] == 77)
				{
					tilespritevector[i][j]->setColor("Xgrey2");
					tilespritevector[i][j]->refreshColor();
				}
				if (levelmanager.puzzle.currenttilevector[i][j] == 78)
				{
					tilespritevector[i][j]->setColor("Xred2");
					tilespritevector[i][j]->refreshColor();
				}
				if (levelmanager.puzzle.currenttilevector[i][j] == 79)
				{
					tilespritevector[i][j]->setColor("Xpurple1");
					tilespritevector[i][j]->refreshColor();
				}
			}
		}
	}

}

void ClientDemo::processServerMessage(ServerMessage msg)
{
	/*character messagechar, float xpos, float ypos, char status
		0. Assign Player Number, unused, unused, new player number
		1. Player 1 pos, xpos, ypos, animation #
		2. Player 2 pos, xpos, ypos, animation #
		3. Player 3 pos, xpos, ypos, animation #
		4. Player 4 pos, xpos, ypos, animation #
		5. Sam pos, xpos, ypos, animation #
		6. Ptera pos, xpos, ypos, animmation #
		7. Candy pos, xpos, ypos, unused
		8. Got candy, unused, unused, player #
		9. Candy wore off, unused, unused, player #
		10. Change Level, unused, unused, new level #
		11. Drop Player, unused, unused, player #
		12. Player Joined, unused, unused, player #
		
	*/
	if(msg.messagechar == 0)
	{
		playernum = msg.status;
	}
	else if (msg.messagechar == 8)
	{
		if (playernum == msg.status)
		{
			gSFX.pTrigs[playernum - 1].gotCandy = true;
			players[playernum - 1]->speedboost = 2;
		}
	}
	else if (msg.messagechar == 9)
	{
		if (playernum == msg.status)
		{
			gSFX.pTrigs[playernum - 1].lostCandy = true;
			players[playernum - 1]->speedboost = 1;
		}
	}
	else if (msg.messagechar == 10)
	{
		loadLevel(msg.status);
	}
	else if (msg.messagechar == 11)
	{
		players[(msg.status)-1]->setVisible(false);
	}
	else if (msg.messagechar == 12)
	{
		players[(msg.status) - 1]->setVisible(true);
	}
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
				auto y = tilemapvals["Yellow1"].asString();
				auto o = tilemapvals["Orange"].asString();
				auto blk = tilemapvals["Black"].asString();

				auto b2 = tilemapvals["Blue2"].asString();
				auto b3 = tilemapvals["Blue3"].asString();
				auto g1 = tilemapvals["Green1"].asString();
				auto g2 = tilemapvals["Green2"].asString();
				auto g3 = tilemapvals["Green3"].asString();

				auto w = tilemapvals["White"].asString();
				auto gy1 = tilemapvals["Grey1"].asString();
				auto gy2 = tilemapvals["Grey2"].asString();
				auto r2 = tilemapvals["Red2"].asString();
				auto p = tilemapvals["Purple1"].asString();
				auto r1 = tilemapvals["Red1"].asString();



				if ("true" == r)
				{
					//p1CLabel->setString("Red");
					p1CLabel->setFontFillColor(ccc3(247, 52, 47));
					gSFX.pTrigs[0].onBucket = true; //0=p1, 1=p2, 2=p3, 3=p4
				}
				if ("true" == b)
				{
					//p1CLabel->setString("Blue");
					p1CLabel->setFontFillColor(ccc3(49, 58, 197));
					gSFX.pTrigs[0].onBucket = true;
				}
				if ("true" == y) {
					//p1CLabel->setString("Yellow");
					p1CLabel->setFontFillColor(ccc3(222, 244, 69));
					gSFX.pTrigs[0].onBucket = true;
				}
				if ("true" == o) {
					//p1CLabel->setString("Orange");
					p1CLabel->setFontFillColor(ccc3(234, 152, 46));
					gSFX.pTrigs[0].onBucket = true;
				}
				if ("true" == blk) {
					p1CLabel->setFontFillColor(ccc3(36, 33, 25));
					gSFX.pTrigs[0].onBucket = true;
				}

				if ("true" == b2) {
					p1CLabel->setFontFillColor(ccc3(4, 31, 131));
					gSFX.pTrigs[0].onBucket = true;
				}
				if ("true" == b3) {
					p1CLabel->setFontFillColor(ccc3(1, 16, 73));
					gSFX.pTrigs[0].onBucket = true;
				}
				if ("true" == g1) {
					p1CLabel->setFontFillColor(ccc3(2, 123, 36));
					gSFX.pTrigs[0].onBucket = true;
				}
				if ("true" == g2) {
					p1CLabel->setFontFillColor(ccc3(11, 187, 60));
					gSFX.pTrigs[0].onBucket = true;
				}
				if ("true" == g3) {
					p1CLabel->setFontFillColor(ccc3(47, 247, 145));
					gSFX.pTrigs[0].onBucket = true;
				}
				if ("true" == w) {
					p1CLabel->setFontFillColor(ccc3(255, 255, 255));
					gSFX.pTrigs[1].onBucket = true;
				}
				if ("true" == gy1) {
					p1CLabel->setFontFillColor(ccc3(101, 141, 255));
					gSFX.pTrigs[1].onBucket = true;
				}
				if ("true" == gy2) {
					p1CLabel->setFontFillColor(ccc3(203, 216, 229));
					gSFX.pTrigs[1].onBucket = true;
				}
				if ("true" == p) {
					p1CLabel->setFontFillColor(ccc3(148, 55, 122));
					gSFX.pTrigs[1].onBucket = true;
				}
				if ("true" == r2) {
					p1CLabel->setFontFillColor(ccc3(187, 11, 44));
					gSFX.pTrigs[1].onBucket = true;
				}
				if ("true" == r1) {
					p1CLabel->setFontFillColor(ccc3(247, 52, 47));
					gSFX.pTrigs[1].onBucket = true;
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
				auto y = tilemapvals["Yellow1"].asString();
				auto o = tilemapvals["Orange"].asString();
				auto blk = tilemapvals["Black"].asString();

				auto b2 = tilemapvals["Blue2"].asString();
				auto b3 = tilemapvals["Blue3"].asString();
				auto g1 = tilemapvals["Green1"].asString();
				auto g2 = tilemapvals["Green2"].asString();
				auto g3 = tilemapvals["Green3"].asString();

				auto w = tilemapvals["White"].asString();
				auto gy1 = tilemapvals["Grey1"].asString();
				auto gy2 = tilemapvals["Grey2"].asString();
				auto r2 = tilemapvals["Red2"].asString();
				auto p = tilemapvals["Purple1"].asString();
				auto r1 = tilemapvals["Red1"].asString();


				if ("true" == r)
				{
					p2CLabel->setFontFillColor(ccc3(247, 52, 47));
					gSFX.pTrigs[1].onBucket = true;
				}
				if ("true" == b)
				{
					p2CLabel->setFontFillColor(ccc3(49, 58, 197));
					gSFX.pTrigs[1].onBucket = true;
				}
				if ("true" == y) {
					p2CLabel->setFontFillColor(ccc3(222, 244, 69));
					gSFX.pTrigs[1].onBucket = true;
				}
				if ("true" == o) {
					p2CLabel->setFontFillColor(ccc3(234, 152, 46));
					gSFX.pTrigs[1].onBucket = true;
				}
				if ("true" == blk) {
					p1CLabel->setFontFillColor(ccc3(36, 33, 25));
					gSFX.pTrigs[1].onBucket = true;
				}

				if ("true" == b2) {
					p2CLabel->setFontFillColor(ccc3(4, 31, 131));
					gSFX.pTrigs[1].onBucket = true;
				}
				if ("true" == b3) {
					p2CLabel->setFontFillColor(ccc3(1, 16, 73));
					gSFX.pTrigs[1].onBucket = true;
				}
				if ("true" == g1) {
					p2CLabel->setFontFillColor(ccc3(2, 123, 36));
					gSFX.pTrigs[1].onBucket = true;
				}
				if ("true" == g2) {
					p2CLabel->setFontFillColor(ccc3(11, 187, 60));
					gSFX.pTrigs[1].onBucket = true;
				}
				if ("true" == g3) {
					p2CLabel->setFontFillColor(ccc3(47, 247, 145));
					gSFX.pTrigs[1].onBucket = true;
				}
				if ("true" == w) {
					p2CLabel->setFontFillColor(ccc3(255, 255, 255));
					gSFX.pTrigs[1].onBucket = true;
				}
				if ("true" == gy1) {
					p2CLabel->setFontFillColor(ccc3(101, 141, 255));
					gSFX.pTrigs[1].onBucket = true;
				}
				if ("true" == gy2) {
					p2CLabel->setFontFillColor(ccc3(203, 216, 229));
					gSFX.pTrigs[1].onBucket = true;
				}
				if ("true" == p) {
					p2CLabel->setFontFillColor(ccc3(148, 55, 122));
					gSFX.pTrigs[1].onBucket = true;
				}
				if ("true" == r2) {
					p2CLabel->setFontFillColor(ccc3(187, 11, 44));
					gSFX.pTrigs[1].onBucket = true;
				}
				if ("true" == r1) {
					p2CLabel->setFontFillColor(ccc3(247, 52, 47));
					gSFX.pTrigs[1].onBucket = true;
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
				auto y = tilemapvals["Yellow1"].asString();
				auto o = tilemapvals["Orange"].asString();
				auto blk = tilemapvals["Black"].asString();

				auto b2 = tilemapvals["Blue2"].asString();
				auto b3 = tilemapvals["Blue3"].asString();
				auto g1 = tilemapvals["Green1"].asString();
				auto g2 = tilemapvals["Green2"].asString();
				auto g3 = tilemapvals["Green3"].asString();

				auto w = tilemapvals["White"].asString();
				auto gy1 = tilemapvals["Grey1"].asString();
				auto gy2 = tilemapvals["Grey2"].asString();
				auto r2 = tilemapvals["Red2"].asString();
				auto p = tilemapvals["Purple1"].asString();
				auto r1 = tilemapvals["Red1"].asString();


				if ("true" == r)
				{
					p3CLabel->setFontFillColor(ccc3(247, 52, 47));
					gSFX.pTrigs[2].onBucket = true;
				}
				if ("true" == b)
				{
					p3CLabel->setFontFillColor(ccc3(49, 58, 197));
					gSFX.pTrigs[2].onBucket = true;
				}
				if ("true" == y) {
					p3CLabel->setFontFillColor(ccc3(222, 244, 69));
					gSFX.pTrigs[2].onBucket = true;
				}
				if ("true" == o) {
					p3CLabel->setFontFillColor(ccc3(234, 152, 46));
					gSFX.pTrigs[2].onBucket = true;
				}
				if ("true" == blk) {
					p1CLabel->setFontFillColor(ccc3(36, 33, 25));
					gSFX.pTrigs[2].onBucket = true;
				}

				if ("true" == b2) {
					p3CLabel->setFontFillColor(ccc3(4, 31, 131));
					gSFX.pTrigs[2].onBucket = true;
				}
				if ("true" == b3) {
					p3CLabel->setFontFillColor(ccc3(1, 16, 73));
					gSFX.pTrigs[2].onBucket = true;
				}
				if ("true" == g1) {
					p3CLabel->setFontFillColor(ccc3(2, 123, 36));
					gSFX.pTrigs[2].onBucket = true;
				}
				if ("true" == g2) {
					p3CLabel->setFontFillColor(ccc3(11, 187, 60));
					gSFX.pTrigs[2].onBucket = true;
				}
				if ("true" == g3) {
					p3CLabel->setFontFillColor(ccc3(47, 247, 145));
					gSFX.pTrigs[2].onBucket = true;
				}
				if ("true" == w) {
					p3CLabel->setFontFillColor(ccc3(255, 255, 255));
					gSFX.pTrigs[1].onBucket = true;
				}
				if ("true" == gy1) {
					p3CLabel->setFontFillColor(ccc3(101, 141, 255));
					gSFX.pTrigs[1].onBucket = true;
				}
				if ("true" == gy2) {
					p3CLabel->setFontFillColor(ccc3(203, 216, 229));
					gSFX.pTrigs[1].onBucket = true;
				}
				if ("true" == p) {
					p3CLabel->setFontFillColor(ccc3(148, 55, 122));
					gSFX.pTrigs[1].onBucket = true;
				}
				if ("true" == r2) {
					p3CLabel->setFontFillColor(ccc3(187, 11, 44));
					gSFX.pTrigs[1].onBucket = true;
				}
				if ("true" == r1) {
					p3CLabel->setFontFillColor(ccc3(247, 52, 47));
					gSFX.pTrigs[1].onBucket = true;
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
				auto y = tilemapvals["Yellow1"].asString();
				auto o = tilemapvals["Orange"].asString();
				auto blk = tilemapvals["Black"].asString();

				auto b2 = tilemapvals["Blue2"].asString();
				auto b3 = tilemapvals["Blue3"].asString();
				auto g1 = tilemapvals["Green1"].asString();
				auto g2 = tilemapvals["Green2"].asString();
				auto g3 = tilemapvals["Green3"].asString();

				auto w = tilemapvals["White"].asString();
				auto gy1 = tilemapvals["Grey1"].asString();
				auto gy2 = tilemapvals["Grey2"].asString();
				auto r2 = tilemapvals["Red2"].asString();
				auto p = tilemapvals["Purple1"].asString();
				auto r1 = tilemapvals["Red1"].asString();


				if ("true" == r)
				{
					p4CLabel->setFontFillColor(ccc3(247, 52, 47));
					gSFX.pTrigs[3].onBucket = true;
				}
				if ("true" == b)
				{
					p4CLabel->setFontFillColor(ccc3(49, 58, 197));
					gSFX.pTrigs[3].onBucket = true;
				}
				if ("true" == y) {
					p4CLabel->setFontFillColor(ccc3(222, 244, 69));
					gSFX.pTrigs[3].onBucket = true;
				}
				if ("true" == o) {
					p4CLabel->setFontFillColor(ccc3(234, 152, 46));
					gSFX.pTrigs[3].onBucket = true;
				}
				if ("true" == blk) {
					p1CLabel->setFontFillColor(ccc3(36, 33, 25));
					gSFX.pTrigs[3].onBucket = true;
				}

				if ("true" == b2) {
					p4CLabel->setFontFillColor(ccc3(4, 31, 131));
					gSFX.pTrigs[3].onBucket = true;
				}
				if ("true" == b3) {
					p4CLabel->setFontFillColor(ccc3(1, 16, 73));
					gSFX.pTrigs[3].onBucket = true;
				}
				if ("true" == g1) {
					p4CLabel->setFontFillColor(ccc3(2, 123, 36));
					gSFX.pTrigs[3].onBucket = true;
				}
				if ("true" == g2) {
					p4CLabel->setFontFillColor(ccc3(11, 187, 60));
					gSFX.pTrigs[3].onBucket = true;
				}
				if ("true" == g3) {
					p4CLabel->setFontFillColor(ccc3(47, 247, 145));
					gSFX.pTrigs[3].onBucket = true;
				}
				if ("true" == w) {
					p4CLabel->setFontFillColor(ccc3(255, 255, 255));
					gSFX.pTrigs[1].onBucket = true;
				}
				if ("true" == gy1) {
					p4CLabel->setFontFillColor(ccc3(101, 141, 255));
					gSFX.pTrigs[1].onBucket = true;
				}
				if ("true" == gy2) {
					p4CLabel->setFontFillColor(ccc3(203, 216, 229));
					gSFX.pTrigs[1].onBucket = true;
				}
				if ("true" == p) {
					p4CLabel->setFontFillColor(ccc3(148, 55, 122));
					gSFX.pTrigs[1].onBucket = true;
				}
				if ("true" == r2) {
					p4CLabel->setFontFillColor(ccc3(187, 11, 44));
					gSFX.pTrigs[1].onBucket = true;
				}
				if ("true" == r1) {
					p3CLabel->setFontFillColor(ccc3(247, 52, 47));
					gSFX.pTrigs[1].onBucket = true;
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


void ClientDemo::loadLevel(int level)
{
	for (Sprite* s : levelmanager.levelsprites)
	{
		removeChild(s);
	}

	for (unsigned int i = 0; i < tilespritevector.size(); i++)
	{
		for (unsigned int j = 0; j < tilespritevector[i].size(); j++)
		{
			removeChild(tilespritevector[i][j]);
		}
	}

	removeChild(levelmanager.levelmap);

	// NEW CODE ADDED
	NotInTransition = false;

	transitionManager.loadTransition(level);
	for (Sprite* ts : transitionManager.transitionSprite)
	{
		addChild(ts, 10);
	}
	////////////////


	gSFX.levelChange = true;
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
	for (unsigned int i = 0; i < tilespritevector.size(); i++)
	{
		tilespritevector[i].resize(levelmanager.puzzle.currenttilevector[i].size());
	}

	for (unsigned int i = 0; i < tilespritevector.size(); i++)
	{
		for (unsigned int j = 0; j < tilespritevector[i].size(); j++)
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
	if (NotInTransition) // CODE TO TRY
	{
		transitionManager.start_timer = 60;
		CCCamera::getDefaultCamera()->setPosition(players[playernum - 1]->getPosition());
	}
	else
	{
		CCCamera::getDefaultCamera()->setPosition(winSizeWidth, winSizeHeight);
	}
}

void ClientDemo::processSound(ServerPositionPacket &p) {

	//===========================================================
	//					ISSUES AND BUGS
	//===========================================================
	//	1. If player is not holding down space and paints on the
	// grid, they can paint outside the grid once and still get the 
	// painting sfx.
	//
	//	2. Need to sync animations with sfx.
	//
	//	3. Recode processSound() to no longer need a parameter.
	//
	//	4. Use Server Messages for audio triggers - specifically
	//	for grid detection.
	//
	//	3. Volume of various SFX need a little more adjustment.
	//
	//	4. Idle Player check is hack-fixed for now, will implement
	//	better later.
	//============================================================

	// GOOD REFERENCES FOR AUDIO CODING
	// http://dan.clarke.name/2011/07/cocos2d-sound-in-android-tutorial/
	// https://searchcode.com/codesearch/view/95985619/

	//===========================================================
	//        NON-ANIMATION BASED AUDIO
	//===========================================================

	// soundIDList[0] = paint
	// soundIDList[1] = sam_playerhit
	// soundIDList[2] = sam_teleport
	// soundIDList[3] = sam_reappear
	// soundIDList[4] = sam_whistle
	// soundIDList[5] = ptero_swoop
	// soundIDList[6] = get_paintc
	// soundIDList[7] = player_candy_pickup
	// soundIDList[8] = sam munch
	// soundIDList[9] = player_candy_lost
	// soundIDList[10] = puzzle_solved
	// soundIDList[11] = ptero_swoop_fast
	// soundIDList[12] = ptero_playerhit

	//If Sam or pterodactyl touches a player

	if (pIFrames[0] == 0) //if player 1 iframes = 0
	{
		if (gSFX.pTrigs[0].hasPainted == true && villain->getOpacity() > 0 && (abs(p.vx - p.p1x) < 5 && abs(p.vy - p.p1y) < 5))
		{
			if (false == isSFXPlaying[1])
			{
				soundIDList[1] = experimental::AudioEngine::play2d("\\res\\sound\\sfx\\sam_playerhit.mp3", false, 0.8f);
				isSFXPlaying[1] = true;
				experimental::AudioEngine::setFinishCallback(soundIDList[1], [&](int id, const std::string& filePath)
				{
					isSFXPlaying[1] = false;
				});
				pIFrames[0] = 3 * 30; //3 seconds of iframes at 30 fps
			}
		}
		else if (pterodactyl->isHostile() && abs(pterodactyl->getPositionX() + 12 - p.p1x) < 10 && abs(pterodactyl->getPositionY() - p.p1y) < 10 && gSFX.pTrigs[0].hasPainted == true)
		{
			if (false == isSFXPlaying[12])
			{
				soundIDList[12] = experimental::AudioEngine::play2d("\\res\\sound\\sfx\\ptero_playerhit.mp3", false, 0.8f);
				isSFXPlaying[12] = true;
				experimental::AudioEngine::setFinishCallback(soundIDList[12], [&](int id, const std::string& filePath)
				{
					isSFXPlaying[12] = false;
				});
				pIFrames[0] = 2 * 30; //2 seconds of iframes at 30 fps
			}
		}
	}
	if (pIFrames[1] == 0)
	{
		if (gSFX.pTrigs[1].hasPainted == true && villain->getOpacity() > 0 && (abs(p.vx - p.p2x) < 5 && abs(p.vy - p.p2y) < 5))
		{
			if (false == isSFXPlaying[1])
			{
				soundIDList[1] = experimental::AudioEngine::play2d("\\res\\sound\\sfx\\sam_playerhit.mp3", false, 0.8f);
				isSFXPlaying[1] = true;
				experimental::AudioEngine::setFinishCallback(soundIDList[1], [&](int id, const std::string& filePath)
				{
					isSFXPlaying[1] = false;
				});
				pIFrames[1] = 3 * 30; //3 seconds of iframes at 30 fps
			}
		}
		else if (pterodactyl->isHostile() && abs(pterodactyl->getPositionX() + 12 - p.p2x) < 10 && abs(pterodactyl->getPositionY() - p.p2y) < 10 && gSFX.pTrigs[1].hasPainted == true)
		{
			if (false == isSFXPlaying[12])
			{
				soundIDList[12] = experimental::AudioEngine::play2d("\\res\\sound\\sfx\\ptero_playerhit.mp3", false, 0.8f);
				isSFXPlaying[12] = true;
				experimental::AudioEngine::setFinishCallback(soundIDList[12], [&](int id, const std::string& filePath)
				{
					isSFXPlaying[12] = false;
				});
				pIFrames[1] = 2 * 30; //2 seconds of iframes at 30 fps
			}
		}
	}

	if (pIFrames[2] == 0)
	{
		if (gSFX.pTrigs[2].hasPainted == true && villain->getOpacity() > 0 && (abs(p.vx - p.p3x) < 5 && abs(p.vy - p.p3y) < 5))
		{
			if (false == isSFXPlaying[1])
			{
				soundIDList[1] = experimental::AudioEngine::play2d("\\res\\sound\\sfx\\sam_playerhit.mp3", false, 0.8f);
				isSFXPlaying[1] = true;
				experimental::AudioEngine::setFinishCallback(soundIDList[1], [&](int id, const std::string& filePath)
				{
					isSFXPlaying[1] = false;
				});
				pIFrames[2] = 3 * 30; //3 seconds of iframes at 30 fps
			}
		}
		else if (pterodactyl->isHostile() && abs(pterodactyl->getPositionX() + 12 - p.p3x) < 10 && abs(pterodactyl->getPositionY() - p.p3y) < 10 && gSFX.pTrigs[2].hasPainted == true)
		{
			if (false == isSFXPlaying[12])
			{
				soundIDList[12] = experimental::AudioEngine::play2d("\\res\\sound\\sfx\\ptero_playerhit.mp3", false, 0.8f);
				isSFXPlaying[12] = true;
				experimental::AudioEngine::setFinishCallback(soundIDList[12], [&](int id, const std::string& filePath)
				{
					isSFXPlaying[12] = false;
				});
				pIFrames[2] = 2 * 30; //2 seconds of iframes at 30 fps
			}
		}
	}

	if (pIFrames[3] == 0)
	{
		if (gSFX.pTrigs[3].hasPainted == true && villain->getOpacity() > 0 && (abs(p.vx - p.p4x) < 5 && abs(p.vy - p.p4y) < 5))
		{
			if (false == isSFXPlaying[1])
			{
				soundIDList[1] = experimental::AudioEngine::play2d("\\res\\sound\\sfx\\sam_playerhit.mp3", false, 0.8f);
				isSFXPlaying[1] = true;
				experimental::AudioEngine::setFinishCallback(soundIDList[1], [&](int id, const std::string& filePath)
				{
					isSFXPlaying[1] = false;
				});
				pIFrames[3] = 2 * 30; //2 seconds of iframes at 30 fps
			}
		}
		else if (pterodactyl->isHostile() && abs(pterodactyl->getPositionX() + 12 - p.p4x) < 10 && abs(pterodactyl->getPositionY() - p.p4y) < 10 && gSFX.pTrigs[3].hasPainted == true)
		{
			if (false == isSFXPlaying[12])
			{
				soundIDList[12] = experimental::AudioEngine::play2d("\\res\\sound\\sfx\\ptero_playerhit.mp3", false, 0.8f);
				isSFXPlaying[12] = true;
				experimental::AudioEngine::setFinishCallback(soundIDList[12], [&](int id, const std::string& filePath)
				{
					isSFXPlaying[12] = false;
				});
				pIFrames[3] = 2 * 30; //2 seconds of iframes at 30 fps
			}
		}
	}
	//If Sam or pterodactyl touches a player - end


	//If player gets/loses candy buff

	for (unsigned int i = 0; i < 3; i++)
	{
		if (gSFX.pTrigs[i].gotCandy == true)
		{
			if (isSFXPlaying[7] == false)
			{
				soundIDList[7] = experimental::AudioEngine::play2d("\\res\\sound\\sfx\\player_candy_pickup.mp3", false, 0.8f);
				isSFXPlaying[7] = true;
				experimental::AudioEngine::setFinishCallback(soundIDList[7], [&](int id, const std::string& filePath)
				{
					isSFXPlaying[7] = false;
				});
				gSFX.pTrigs[i].gotCandy = false; //possibly needs to go before callback?
			}
		}
		else if (gSFX.pTrigs[i].lostCandy == true)
		{
			if (isSFXPlaying[9] == false)
			{
				soundIDList[9] = experimental::AudioEngine::play2d("\\res\\sound\\sfx\\player_candy_lost.mp3", false, 0.8f);
				isSFXPlaying[9] = true;
				experimental::AudioEngine::setFinishCallback(soundIDList[9], [&](int id, const std::string& filePath)
				{
					isSFXPlaying[9] = false;
				});
				gSFX.pTrigs[i].lostCandy = false;
			}
		}
	}
	//If player gets/loses candy buff - end

	//If level solved
	if (gSFX.levelChange == true) //may need to set bool on changelevel() instead if this has trouble triggering sfx
	{
		if (isSFXPlaying[10] == false)
		{
			soundIDList[10] = experimental::AudioEngine::play2d("\\res\\sound\\sfx\\puzzle_solved.mp3");
			isSFXPlaying[10] = true;
			experimental::AudioEngine::setFinishCallback(soundIDList[10], [&](int id, const std::string& filePath)
			{
				isSFXPlaying[10] = false;
			});
			gSFX.levelChange = false;
		}
	}
	//If level solved - end

	//===========================================================
	//    END OF NON-ANIMATION BASED AUDIO
	//===========================================================





	//===========================================================
	//        ANIMATION-BASED AUDIO
	//===========================================================

	// soundIDList[0] = paint
	// soundIDList[1] = sam_playerhit
	// soundIDList[2] = sam_teleport
	// soundIDList[3] = sam_reappear
	// soundIDList[4] = sam_whistle
	// soundIDList[5] = ptero_swoop
	// soundIDList[6] = get_paintc
	// soundIDList[7] = player_candy_pickup
	// soundIDList[8] = sam munch
	// soundIDList[9] = player_candy_lost
	// soundIDList[10] = puzzle_solved
	// soundIDList[11] = ptero_swoop_fast
	// soundIDList[12] = ptero_playerhit


	//switch used here in case further animation states are created. modular switch-cases superior.
	switch (p.p1anim) {
	case 5: //p1paint
		if (gSFX.pTrigs[0].onBucket == true) //if the player is on a bucket
		{
			if (isSFXPlaying[6] == false)
			{
				soundIDList[6] = experimental::AudioEngine::play2d("\\res\\sound\\sfx\\get_paint.mp3", false, 0.5f);
				isSFXPlaying[6] = true;
				experimental::AudioEngine::setFinishCallback(soundIDList[6], [&](int id, const std::string& filePath)
				{
					isSFXPlaying[6] = false;
				});
			}
			gSFX.pTrigs[0].onBucket = false; //put in callback func?
		}
		else if (gSFX.pTrigs[0].onGrid == true) //if player is on grid
		{
			if (isSFXPlaying[0] == false)
			{
				soundIDList[0] = experimental::AudioEngine::play2d("\\res\\sound\\sfx\\paint.mp3");
				isSFXPlaying[0] = true;
				gSFX.pTrigs[0].hasPainted = true; //temp fix for checking if player is idle
				experimental::AudioEngine::setFinishCallback(soundIDList[0], [&](int id, const std::string& filePath)
				{
					isSFXPlaying[0] = false;
				});
			}
			gSFX.pTrigs[0].onGrid = false;
		}
		break;
	default: break;
	}
	switch (p.p2anim) {
	case 11: //p1paint
		if (gSFX.pTrigs[1].onBucket == true) //if the player is on a bucket
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
			gSFX.pTrigs[1].onBucket = false; 
		}
		else if (gSFX.pTrigs[1].onGrid == true) //if player is on grid
		{
			if (isSFXPlaying[0] == false)
			{
				soundIDList[0] = experimental::AudioEngine::play2d("\\res\\sound\\sfx\\paint.mp3");
				isSFXPlaying[0] = true;
				gSFX.pTrigs[1].hasPainted = true; //temp fix for checking if player is idle
				experimental::AudioEngine::setFinishCallback(soundIDList[0], [&](int id, const std::string& filePath)
				{
					isSFXPlaying[0] = false;
				});
			}
			gSFX.pTrigs[1].onGrid = false;
		}
		break;
	default: break;
	}
	switch (p.p3anim) {
	case 17: //p1paint
		if (gSFX.pTrigs[2].onBucket == true) //if the player is on a bucket
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
			gSFX.pTrigs[2].onBucket = false; 
		}
		else if (gSFX.pTrigs[2].onGrid == true) //if player is on grid
		{
			if (isSFXPlaying[0] == false)
			{
				soundIDList[0] = experimental::AudioEngine::play2d("\\res\\sound\\sfx\\paint.mp3");
				isSFXPlaying[0] = true;
				gSFX.pTrigs[2].hasPainted = true; //temp fix for checking if player is idle
				experimental::AudioEngine::setFinishCallback(soundIDList[0], [&](int id, const std::string& filePath)
				{
					isSFXPlaying[0] = false;
				});
			}
			gSFX.pTrigs[2].onGrid = false;
		}
		break;
	default: break;
	}
	switch (p.p4anim) {
	case 23: //p1paint
		if (gSFX.pTrigs[3].onBucket == true) //if the player is on a bucket
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
			gSFX.pTrigs[3].onBucket = false;
		}
		else if (gSFX.pTrigs[3].onGrid == true) //if player is on grid
		{
			if (isSFXPlaying[0] == false)
			{
				soundIDList[0] = experimental::AudioEngine::play2d("\\res\\sound\\sfx\\paint.mp3");
				isSFXPlaying[0] = true;
				gSFX.pTrigs[3].hasPainted = true; //temp fix for checking if player is idle
				experimental::AudioEngine::setFinishCallback(soundIDList[0], [&](int id, const std::string& filePath)
				{
					isSFXPlaying[0] = false;
				});
			}
			gSFX.pTrigs[3].onGrid = false;
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
			soundIDList[3] = experimental::AudioEngine::play2d("\\res\\sound\\sfx\\sam_reappear.mp3", false, 0.8f);
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
	case 39: //sammunch
		if (false == isSFXPlaying[8])
		{
			soundIDList[8] = experimental::AudioEngine::play2d("\\res\\sound\\sfx\\sam_munch.mp3", false, 0.7f);
			isSFXPlaying[8] = true;
			experimental::AudioEngine::setFinishCallback(soundIDList[8], [&](int id, const std::string& filePath)
			{
				isSFXPlaying[8] = false;
			});
		}
		break;
	default: break;
	}

	switch (p.ptanim) {
	case 33: //pteraleft
		if (false == isSFXPlaying[5])
		{
			if (isSFXPlaying[11] == true)
			{
				experimental::AudioEngine::stop(soundIDList[11]);
				isSFXPlaying[11] = false;
			}
			soundIDList[5] = experimental::AudioEngine::play2d("\\res\\sound\\sfx\\ptero_swoop.mp3", true, 0.1f);
			isSFXPlaying[5] = true;
			//experimental::AudioEngine::setFinishCallback(soundIDList[5], [&](int id, const std::string& filePath)
			//{
			//	isSFXPlaying[5] = false;
			//});
		}
		break;
	case 34: //pteraright
		if (false == isSFXPlaying[5])
		{
			if (isSFXPlaying[11] == true)
			{
				experimental::AudioEngine::stop(soundIDList[11]);
				isSFXPlaying[11] = false;
			}
			soundIDList[5] = experimental::AudioEngine::play2d("\\res\\sound\\sfx\\ptero_swoop.mp3", true, 0.1f);
			isSFXPlaying[5] = true;
			//experimental::AudioEngine::setFinishCallback(soundIDList[5], [&](int id, const std::string& filePath)
			//{
			//	isSFXPlaying[5] = false;
			//});
		}
		break;
	case 40: //pteraANGRYleft
		if (false == isSFXPlaying[11])
		{
			experimental::AudioEngine::stop(soundIDList[5]);
			isSFXPlaying[5] = false;
			soundIDList[11] = experimental::AudioEngine::play2d("\\res\\sound\\sfx\\ptero_swoop_fast.mp3", true, 0.2f);
			isSFXPlaying[11] = true;
			//experimental::AudioEngine::setFinishCallback(soundIDList[11], [&](int id, const std::string& filePath)
			//{
			//	isSFXPlaying[11] = false;
			//});
		}
		break;
	case 41: //pteraANGRYright
		if (false == isSFXPlaying[11])
		{
			experimental::AudioEngine::stop(soundIDList[5]);
			isSFXPlaying[5] = false;
			soundIDList[11] = experimental::AudioEngine::play2d("\\res\\sound\\sfx\\ptero_swoop_fast.mp3", true, 0.2f);
			isSFXPlaying[11] = true;
			//experimental::AudioEngine::setFinishCallback(soundIDList[11], [&](int id, const std::string& filePath)
			//{
			//	isSFXPlaying[11] = false;
			//});
		}
		break;
	default: break;
	}

	//===========================================================
	//     END OF ANIMATION-BASED AUDIO
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