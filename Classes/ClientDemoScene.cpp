#include "ClientDemoScene.h"

USING_NS_CC;
using boost::asio::ip::tcp;

int port = 10001;
std::string ipaddress;
int playerNumber;

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

Scene* ClientDemo::createScene(std::string ipA, int playerNum)
{
	ipaddress = ipA;
	playerNumber = playerNum;

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
	log("from animint");
	log(std::to_string(animint).c_str());
	int refreshrate = glview->getRunningRefreshRate();
	if (refreshrate == 59)
	{
		refreshrate = 60;
	}
	if (refreshrate == 119)
	{
		refreshrate = 120;
	}
	log("from get refresh rate");
	log(std::to_string(refreshrate).c_str());
	int newswapinterval = refreshrate*animint;
	if (newswapinterval < 1)
	{
		newswapinterval = 1;
	}
	swapframes = newswapinterval;
	swapframecounter = newswapinterval;

	log("from newswapinterval");
	log(std::to_string(newswapinterval).c_str());
	*/

	std::ifstream is("config.json");
	cereal::JSONInputArchive configloader(is);
	setupdata = ConfigFileInput();
	configloader(setupdata);
	is.close();

	char mycp1[32];
	char mycp2[32];
	//strncpy(mycp1, setupdata.ipaddress.c_str(), 32);
	//strncpy(mycp2, std::to_string(setupdata.port).c_str(), 32);
	//playernum = setupdata.level;
	//myendpoint = resolver.resolve({ tcp::v4(), mycp1, mycp2 });

	strncpy(mycp1, ipaddress.c_str(), 32);  // NEW CODE TO TRY
	strncpy(mycp2, std::to_string(port).c_str(), 32); // NEW CODE TO TRY
	playernum = playerNumber; // NEW CODE TO TRY

	log("setting player number");
	log(std::to_string(playernum).c_str());
	try
	{
		log("setting up tcp interface");
		log(mycp1);
		log(mycp2);
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
		log("exception");
		log(e.what());
	}


	player1 = Player::create(1);
	addChild(player1, 0);
	player2 = Player::create(2);
	addChild(player2, 0);
	player3 = Player::create(3);
	addChild(player3, 0);
	player4 = Player::create(4);
	addChild(player4, 0);
	players.push_back(player1);
	players.push_back(player2);
	players.push_back(player3);
	players.push_back(player4);

	villain = Villain::create(false);
	addChild(villain, 0);

	pterodactyl = Pterodactyl::create(false);
	addChild(pterodactyl, 0);

	candy = Candy::create();
	addChild(candy, 0);

	tileHighlight = Sprite::create("res//sprites//select_tile.png");
	if (nullptr != tileHighlight)
	{
		tileHighlight->setPosition(0, 0);
		tileHighlight->getTexture()->setAliasTexParameters();
		addChild(tileHighlight, -900);
	}
	bucketHighlight = Sprite::create("res//sprites//bucket_highlight.png");
	
	if (nullptr != bucketHighlight)
	{
		bucketHighlight->setPosition(0, 0);
		bucketHighlight->getTexture()->setAliasTexParameters();
		addChild(bucketHighlight, -901);
	}

	loadLevel(1);

	//create Game Menu
	gameMenuLayer = GameMenu::createGameMenu();

	addChild(gameMenuLayer, 1000); //so its above everything, including transition screen


	winSizeWidth = Director::getInstance()->getWinSize().width / 2;
	winSizeHeight = Director::getInstance()->getWinSize().height / 2;

	//AUDIO INITIALIZATION
	if (gSound.audioOn)
	{
		initializeSound(); //all sound initialization is in here now, cleaner
	}
	playernum = playerNumber;
	players[playernum - 1]->getLabel()->setOpacity(255);
	for (int i = 1; i <= 4; i++)
	{
		if(playernum != i)
		{
			players[i - 1]->setVisible(false);
		}
	}


	auto joyListener = EventListenerJoystick::create();
	joyListener->onEvent = CC_CALLBACK_1(ClientDemo::Joystick, this);
	_eventDispatcher->addEventListenerWithFixedPriority(joyListener, 1);


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

	if (isPaused == true)
	{
		updateFromMenu();
	}
	if (eventActive == 0 && isPaused == false && smoothCamera == false)
	{
		players[playernum - 1]->setPositionX(players[playernum - 1]->getPositionX() + xmove * players[playernum - 1]->speedboost);
		players[playernum - 1]->setPositionY(players[playernum - 1]->getPositionY() + ymove * players[playernum - 1]->speedboost);
	}

	log("UPDATE DT");
	log(std::to_string(dt).c_str());

	io_service_p->poll();
	//log("POLLING");
	if (eventActive == 0)
	{
		if (isPaused == false && smoothCamera == false)
		{
			if (xmove || ymove || button1)
			{

				PlayerInputPacket p2 = PlayerInputPacket(playernum, xmove, ymove, button1);
				std::ostringstream os2;
				cereal::BinaryOutputArchive outar(os2);
				outar(p2);
				outstringbuffer = os2.str();

				log("outstringbuffer length");
				log(std::to_string(outstringbuffer.length()).c_str());
				log("sending packet");
				tcpsessionptr->writewithstringbuffer(outstringbuffer);
				io_service_p->poll_one();
			}
		}


		tileHighlight->setOpacity(0);
		//bucketHighlight->setOpacity(0);

		for (unsigned int i = 0; i < SPRITE_GRID.size(); i++)
		{
			for (unsigned int j = 0; j < SPRITE_GRID[i].size(); j++)
			{
				if (players[playernum - 1]->getPositionX() > SPRITE_GRID[i][j]->getPositionX() - 12
					&& players[playernum - 1]->getPositionX() < SPRITE_GRID[i][j]->getPositionX() + 12
					&& players[playernum - 1]->getPositionY() > SPRITE_GRID[i][j]->getPositionY() - 12
					&& players[playernum - 1]->getPositionY() < SPRITE_GRID[i][j]->getPositionY() + 12)
				{
					tileHighlight->setOpacity(255);
					tileHighlight->setPosition(SPRITE_GRID[i][j]->getPositionX(), SPRITE_GRID[i][j]->getPositionY());
					gSound.pTrigs[playernum - 1].onGrid = true;
				}
			}
		}
		//check if player is on a bucket and highlight it
		highlightBuckets();

		for (Player* p : players)
		{
			p->setZOrder(-p->getPositionY());
		}

		if (levelmanager.currentlevel != 1) {
			villain->setOpacity(255);
			villain->setZOrder(-villain->getPositionY());
			pterodactyl->setOpacity(255);
			pterodactyl->setZOrder(-pterodactyl->getPositionY());
			candy->setZOrder(-candy->getPositionY());
		}
	}
		////////// NEW CODE HERE!!!
		/*if (playerOneActive == false) {
			if (player1->getPositionX() != playerOneSP["x"].asInt() || player1->getPositionY() != playerOneSP["y"].asInt()) {
				playerOneActive = true;
				player1->setOpacity(255);
				p1CLabel->setOpacity(255);
			}
		}
		if (playerTwoActive == false) {
			if (player2->getPositionX() != playerTwoSP["x"].asInt() || player2->getPositionY() != playerTwoSP["y"].asInt()) {
				playerTwoActive = true;
				player2->setOpacity(255);
				p2CLabel->setOpacity(255);
			}
		}
		if (playerThreeActive == false) {
			if (player3->getPositionX() != playerThreeSP["x"].asInt() || player3->getPositionY() != playerThreeSP["y"].asInt()) {
				playerThreeActive = true;
				player3->setOpacity(255);
				p3CLabel->setOpacity(255);
			}
		}
		if (playerFourActive == false) {
			if (player4->getPositionX() != playerFourSP["x"].asInt() || player4->getPositionY() != playerFourSP["y"].asInt()) {
				playerFourActive = true;
				player4->setOpacity(255);
				p4CLabel->setOpacity(255);
			}
		}*/

		if (NotInTransition == false && transitionManager.timer_status()) //check if transition is over, timer at 0
		{
			NotInTransition = true;

			for (Sprite* ts : transitionManager.transitionSprite)
			{
				removeChild(ts);
			}
			villain->runAction(FadeIn::create(1.0f));
		}

		if (gameTimer == 0)
		{
			centerCamera();
		}
		else
		{
			gameTimer--;
		}
		if (eventActive != 0)
		{
			runEvents();
		}
}



void ClientDemo::processPacket(ServerPositionPacket p)
{
	
	for (ServerMessage msg : p.messagevector)
	{
		processServerMessage(msg);
	}
//	if (killsound)
	///{
		//cocos2d::experimental::AudioEngine::stopAll();
		//cocos2d::experimental::AudioEngine::end();
		//return;
	//}
	if (levelmanager.currentlevel != p.level)
	{
		loadLevel(p.level);
	}
	
	activechars = p.activeplayers;
	
	if (eventActive == 0)
	{
		setVisiblePlayers(activechars);
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
		player1->stopAllActionsByTag(1);
		RepeatForever* repeat = RepeatForever::create(animationmanager.animationmap.at(p1anims));
		repeat->setTag(1);
		player1->runAction(repeat);
		player1->setAnim(p1anims);
	}
	if (p.p2anim != 0 && player2->getAnim() != p2anims) {
		player2->stopAllActionsByTag(1);
		RepeatForever* repeat = RepeatForever::create(animationmanager.animationmap.at(p2anims));
		repeat->setTag(1);
		player2->runAction(repeat);
		player2->setAnim(p2anims);
	}
	if (p.p3anim != 0 && player3->getAnim() != p3anims) {
		player3->stopAllActionsByTag(1);
		RepeatForever* repeat = RepeatForever::create(animationmanager.animationmap.at(p3anims));
		repeat->setTag(1);
		player3->runAction(repeat);
		player3->setAnim(p3anims);
	}
	if (p.p4anim != 0 && player4->getAnim() != p4anims) {
		player4->stopAllActionsByTag(1);
		RepeatForever* repeat = RepeatForever::create(animationmanager.animationmap.at(p4anims));
		repeat->setTag(1);
		player4->runAction(repeat);
		player4->setAnim(p4anims);
	}
	if (p.vanim != 0 && villain->getAnim() != vanims) {
		villain->stopAllActionsByTag(1);
		RepeatForever* repeat = RepeatForever::create(animationmanager.animationmap.at(vanims));
		repeat->setTag(1);
		villain->runAction(repeat);
		villain->setAnim(vanims);
	}
	if (p.ptanim != 0 && pterodactyl->getAnim() != ptanims) {
		pterodactyl->stopAllActionsByTag(1);
		RepeatForever* repeat = RepeatForever::create(animationmanager.animationmap.at(ptanims));
		repeat->setTag(1);
		pterodactyl->runAction(repeat);
		pterodactyl->setAnim(ptanims);
	}
	
	updateTilesFromPacket(p);
	//log(std::to_string(currenttilevector[0][0]).c_str());
	//log(std::to_string(p.tilevector[0][0]).c_str());

	if (gSound.audioOn && gSound.sfxOn && !gameMenuLayer->isVisible())
	{
		processSound(p);
	}
}

void ClientDemo::setVisiblePlayers(char activechars)
{
	char p1mask = 1;
	char p2mask = 2;
	char p3mask = 4;
	char p4mask = 8;
	
	char p1there = p1mask & activechars;
	char p2there = p2mask & activechars;
	char p3there = p3mask & activechars;
	char p4there = p4mask & activechars;
	if (p1there == p1mask || playernum == 1)
	{
		player1->setVisible(true);
		player1->getLabel()->setOpacity(255);
	}
	else {
		player1->setVisible(false);
		player1->getLabel()->setOpacity(0);
	}
	if (p2there == p2mask || playernum == 2)
	{
		player2->setVisible(true);
		player2->getLabel()->setOpacity(255);
	}
	else {
		player2->setVisible(false);
		player2->getLabel()->setOpacity(0);
	}
	if (p3there == p3mask || playernum == 3)
	{
		player3->setVisible(true);
		player3->getLabel()->setOpacity(255);
	}
	else {
		player3->setVisible(false);
		player3->getLabel()->setOpacity(0);

	}
	if (p4there == p4mask || playernum == 4)
	{
		player4->setVisible(true);
		player4->getLabel()->setOpacity(255);
	}
	else {
		player4->setVisible(false);
		player4->getLabel()->setOpacity(0);
	}
}

void ClientDemo::updateTilesFromPacket(ServerPositionPacket p)
{

	for (unsigned int i = 0; i < p.tilevector.size(); i++)
	{
		for (unsigned int j = 0; j < p.tilevector[i].size(); j++)
		{
			if (CURRENT_GRID[i][j] != p.tilevector[i][j])
			{
				CURRENT_GRID[i][j] = p.tilevector[i][j];
				if (CURRENT_GRID[i][j] == 1)
				{
					SPRITE_GRID[i][j]->setColor("clear");
					SPRITE_GRID[i][j]->refreshColor();
				}
				else if (CURRENT_GRID[i][j] == 2)
				{
					SPRITE_GRID[i][j]->setColor("red");
					SPRITE_GRID[i][j]->refreshColor();
				}
				else if (CURRENT_GRID[i][j] == 3)
				{
					SPRITE_GRID[i][j]->setColor("blue");
					SPRITE_GRID[i][j]->refreshColor();
				}
				else if (CURRENT_GRID[i][j] == 4)
				{
					SPRITE_GRID[i][j]->setColor("yellow");
					SPRITE_GRID[i][j]->refreshColor();
				}
				else if (CURRENT_GRID[i][j] == 5)
				{
					SPRITE_GRID[i][j]->setColor("orange");
					SPRITE_GRID[i][j]->refreshColor();
				}
				else if (CURRENT_GRID[i][j] == 6)
				{
					SPRITE_GRID[i][j]->setColor("black");
					SPRITE_GRID[i][j]->refreshColor();
				}

				else if (CURRENT_GRID[i][j] == 7)
				{
					SPRITE_GRID[i][j]->setColor("blue2");
					SPRITE_GRID[i][j]->refreshColor();
				}
				else if (CURRENT_GRID[i][j] == 8)
				{
					SPRITE_GRID[i][j]->setColor("blue3");
					SPRITE_GRID[i][j]->refreshColor();
				}
				else if (CURRENT_GRID[i][j] == 9)
				{
					SPRITE_GRID[i][j]->setColor("green1");
					SPRITE_GRID[i][j]->refreshColor();
				}
				else if (CURRENT_GRID[i][j] == 10)
				{
					SPRITE_GRID[i][j]->setColor("green2");
					SPRITE_GRID[i][j]->refreshColor();
				}
				else if (CURRENT_GRID[i][j] == 11)
				{
					SPRITE_GRID[i][j]->setColor("green3");
					SPRITE_GRID[i][j]->refreshColor();
				}
				else if (CURRENT_GRID[i][j] == 12)
				{
					SPRITE_GRID[i][j]->setColor("white");
					SPRITE_GRID[i][j]->refreshColor();
				}
				else if (CURRENT_GRID[i][j] == 13)
				{
					SPRITE_GRID[i][j]->setColor("grey1");
					SPRITE_GRID[i][j]->refreshColor();
				}
				else if (CURRENT_GRID[i][j] == 14)
				{
					SPRITE_GRID[i][j]->setColor("grey2");
					SPRITE_GRID[i][j]->refreshColor();
				}
				else if (CURRENT_GRID[i][j] == 15)
				{
					SPRITE_GRID[i][j]->setColor("red2");
					SPRITE_GRID[i][j]->refreshColor();
				}
				else if (CURRENT_GRID[i][j] == 16)
				{
					SPRITE_GRID[i][j]->setColor("purple1");
					SPRITE_GRID[i][j]->refreshColor();
				}
				else if (CURRENT_GRID[i][j] == 17)
				{
					SPRITE_GRID[i][j]->setColor("red1");
					SPRITE_GRID[i][j]->refreshColor();
				}
				else if (CURRENT_GRID[i][j] == 20)
				{
					SPRITE_GRID[i][j]->setColor("Xred1");
					SPRITE_GRID[i][j]->refreshColor();
				}
				else if (CURRENT_GRID[i][j] == 30)
				{
					SPRITE_GRID[i][j]->setColor("Xblue");
					SPRITE_GRID[i][j]->refreshColor();
				}
				else if (CURRENT_GRID[i][j] == 40)
				{
					SPRITE_GRID[i][j]->setColor("Xyellow");
					SPRITE_GRID[i][j]->refreshColor();
				}
				else if (CURRENT_GRID[i][j] == 50)
				{
					SPRITE_GRID[i][j]->setColor("Xorange");
					SPRITE_GRID[i][j]->refreshColor();
				}
				else if (CURRENT_GRID[i][j] == 60)
				{
					SPRITE_GRID[i][j]->setColor("Xblack");
					SPRITE_GRID[i][j]->refreshColor();
				}

				else if (CURRENT_GRID[i][j] == 70)
				{
					SPRITE_GRID[i][j]->setColor("Xblue2");
					SPRITE_GRID[i][j]->refreshColor();
				}
				else if (CURRENT_GRID[i][j] == 71)
				{
					SPRITE_GRID[i][j]->setColor("Xblue3");
					SPRITE_GRID[i][j]->refreshColor();
				}
				else if (CURRENT_GRID[i][j] == 72)
				{
					SPRITE_GRID[i][j]->setColor("Xgreen1");
					SPRITE_GRID[i][j]->refreshColor();
				}
				else if (CURRENT_GRID[i][j] == 73)
				{
					SPRITE_GRID[i][j]->setColor("Xgreen2");
					SPRITE_GRID[i][j]->refreshColor();
				}
				else if (CURRENT_GRID[i][j] == 74)
				{
					SPRITE_GRID[i][j]->setColor("Xgreen3");
					SPRITE_GRID[i][j]->refreshColor();
				}
				else if (CURRENT_GRID[i][j] == 75)
				{
					SPRITE_GRID[i][j]->setColor("Xwhite");
					SPRITE_GRID[i][j]->refreshColor();
				}
				else if (CURRENT_GRID[i][j] == 76)
				{
					SPRITE_GRID[i][j]->setColor("Xgrey1");
					SPRITE_GRID[i][j]->refreshColor();
				}
				else if (CURRENT_GRID[i][j] == 77)
				{
					SPRITE_GRID[i][j]->setColor("Xgrey2");
					SPRITE_GRID[i][j]->refreshColor();
				}
				else if (CURRENT_GRID[i][j] == 78)
				{
					SPRITE_GRID[i][j]->setColor("Xred2");
					SPRITE_GRID[i][j]->refreshColor();
				}
				else if (CURRENT_GRID[i][j] == 79)
				{
					SPRITE_GRID[i][j]->setColor("Xpurple1");
					SPRITE_GRID[i][j]->refreshColor();
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
	7. Candy spawned, xpos, ypos, unused
	8. Got candy, unused, unused, player #
	9. Candy wore off, unused, unused, player #
	10. Change Level, unused, unused, new level #
	11. Drop Player, unused, unused, player #
	12. Player Joined, unused, unused, player #
	13. Sam hit player, unused, unused, player #
	14. Ptero hit player, unused, unused, player #
	15. Go to win game, unused, unused, unused	
	16. Player got bucket, player number, unused, color #
	17. Player already taken, unused, unused, player #
	18. Puzzle completed, unused, unused, unused
	19. Event change, event #, phase #, event status
	*/
	
	if(msg.messagechar == 0)
	{
		playernum = msg.status;
	}
	else if (msg.messagechar == 7)
	{
		experimental::AudioEngine::play2d("\\res\\sound\\sfx\\candy_spawn.mp3", false, 0.7f);
	}
	else if (msg.messagechar == 8)
	{
		if (playernum == msg.status)
		{
			gSound.pTrigs[playernum - 1].gotCandy = true;
			players[playernum - 1]->speedboost = 2;
		}
	}
	else if (msg.messagechar == 9)
	{
		if (playernum == msg.status)
		{
			gSound.pTrigs[playernum - 1].lostCandy = true;
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
	else if (msg.messagechar == 13)
	{
		gSound.pTrigs[msg.status - 1].samCollide = true;
	}
	else if (msg.messagechar == 14)
	{
		gSound.pTrigs[msg.status - 1].ptCollide = true;
	}
	else if (msg.messagechar == 15)
	{
		_eventDispatcher->removeAllEventListeners();
		cocos2d::experimental::AudioEngine::stopAll();
		auto scene = GameOver::createGameOver();
		Director::getInstance()->replaceScene(scene);	
	}
	else if (msg.messagechar == 16)
	{
		auto labelcolor(Color3B(255, 255, 255));
		switch (msg.status)
		{
		case 2: // red
			labelcolor = Color3B(247, 52, 47);
			break;
		case 3: // blue
			labelcolor = Color3B(49, 58, 197);
			break;
		case 4: // yellow 
			labelcolor = Color3B(236, 250, 85);
			break;
		case 5: // orange
			labelcolor = Color3B(234, 152, 26);
			break;
		case 6: // black
			labelcolor = Color3B(36, 33, 25);
			break;
		case 7: 
			labelcolor = Color3B(4, 31, 131);
			break;
		case 8: 
			labelcolor = Color3B(1, 16, 73);
			break;
		case 9: 
			labelcolor = Color3B(2, 123, 36);
			break;
		case 10: 
			labelcolor = Color3B(11, 187, 60);
			break;
		case 11: 
			labelcolor = Color3B(47, 247, 145);
			break;
		case 12: 
			labelcolor = Color3B(255, 255, 255);
			break;
		case 13: 
			labelcolor = Color3B(101, 141, 186);
			break;
		case 14: 
			labelcolor = Color3B(203, 216, 229);
			break;
		case 15: // red2
			labelcolor = Color3B(187, 11, 44);
			break;
		case 16:  // purple1
			labelcolor = Color3B(148, 55, 122);
			break;
		case 17: 
			labelcolor = Color3B(247, 52, 47);
			break;


		}
		if (msg.xpos == 1)
		{
			//player1->getLabel()->setFontFillColor(labelcolor);
			player1->getLabel()->setColor(labelcolor);
			gSound.pTrigs[playernum - 1].onBucket = true;
		}
		if (msg.xpos == 2)
		{
			//player2->getLabel()->setFontFillColor(labelcolor);
			player2->getLabel()->setColor(labelcolor);
			gSound.pTrigs[playernum - 1].onBucket = true;
		}
		if (msg.xpos == 3)
		{
			//player3->getLabel()->setFontFillColor(labelcolor);
			player3->getLabel()->setColor(labelcolor);
			gSound.pTrigs[playernum - 1].onBucket = true;
		}
		if (msg.xpos == 4)
		{
			//player4->getLabel()->setFontFillColor(labelcolor);
			player4->getLabel()->setColor(labelcolor);
			gSound.pTrigs[playernum - 1].onBucket = true;
		}


	}
	else if (msg.messagechar == 17)
	{
		_eventDispatcher->removeAllEventListeners();
		auto scene = ServerConnection::createServerConnection(ipaddress, activechars);
		Director::getInstance()->replaceScene(scene);
	}

	else if (msg.messagechar == 18)
	{
		//could prob do this with client-side tilesCompleted handling
		eventActive = 2;
		for (unsigned int i = 0; i < players.size(); i++)
		{
			players[i]->setVisible(false);
		}
		tileHighlight->setOpacity(0);
		bucketHighlight->setOpacity(0);
		villain->setVisible(false);
		pterodactyl->setVisible(false);
		candy->setVisible(false);
		smoothCamera = true;
		if (levelmanager.currentlevel == 1)
		{
			pos.x = 240;
			pos.y = 168;
		}
		else if (levelmanager.currentlevel == 2)
		{
			pos.x = 238;
			pos.y = 150;
		}
		else if (levelmanager.currentlevel == 3)
		{
			pos.x = 300;
			pos.y = 150;
		}
		else if (levelmanager.currentlevel == 4)
		{
			pos.x = 370;
			pos.y = 320;
		}
		//play victory music until level completed screen comes
		experimental::AudioEngine::stop(soundIDList[14]);
		soundIDList[14] = experimental::AudioEngine::play2d("res\\sound\\music\\victory.mp3", false, gSound.mVolume);
		
	}

	/*else if (msg.messagechar == 18)
	{
		if ((unsigned int)msg.xpos <= SPRITE_GRID.size() && (unsigned int)msg.ypos <= SPRITE_GRID[0].size()) //prevents out of bounds vector subscript, but essentially skips over servermessage?
		{
			if (msg.status == 0) //paint tile wet
			{
				SPRITE_GRID[(int)msg.xpos][(int)msg.ypos]->setDry(true);
			}
			else if (msg.status == 1) //paint tile dry
			{
				SPRITE_GRID[(int)msg.xpos][(int)msg.ypos]->setDry(false);
			}
			SPRITE_GRID[(int)msg.xpos][(int)msg.ypos]->refreshColor();
		}
	}*/

	//Event #1: Sam Painting
	//Event #2: TBA
	//Event #3: TBA
	//etc etc
	else if (msg.messagechar == 19)
	{
		if (msg.xpos == 1) //sam painting event
		{
			if (msg.ypos == 0) //not phase specific
			{
				if (msg.status == 1) //blank canvas removed
				{
					blankCanvas->setVisible(false);
				}
				else if (msg.status == 2)
				{
					soundIDList[0] = experimental::AudioEngine::play2d("\\res\\sound\\sfx\\paint.mp3", true);
				}
				else if (msg.status == 3)
				{
					experimental::AudioEngine::stop(soundIDList[0]);
					soundIDList[15] = experimental::AudioEngine::play2d("\\res\\sound\\sfx\\sam_laugh.mp3");
				}
				else if (msg.status == 4) //event is over
				{
					eventActive = 0;
				}
				else if (msg.status == 5) //event started
				{
					eventActive = 1;
					blankCanvas->setVisible(true);
				}
			}
			if (msg.ypos == 2) //phase-2 specific
			{
				pEvent.canvasFade = true;
			}
		}
	}
}



void ClientDemo::KeyDown(EventKeyboard::KeyCode keyCode, Event* event)
{

	
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
		case EventKeyboard::KeyCode::KEY_W:
			ymove += 2;
			break;
		case EventKeyboard::KeyCode::KEY_A:
			xmove -= 2;
			break;
		//KEY_S is down further since it also deals with sound toggling too
		case EventKeyboard::KeyCode::KEY_D:
			xmove += 2;
			break;
		case EventKeyboard::KeyCode::KEY_SPACE:
			button1 = true;
			//space(); - handled server-side now
			break;
		case EventKeyboard::KeyCode::KEY_CTRL:
			button2 = true;
			break;
		//CTRL + M = Toggle Music On/Off
		case EventKeyboard::KeyCode::KEY_M:
			if (button2) //if CTRL is pressed down too
				//toggle music on/off
				if (gSound.musicOn)
				{
					gSound.musicOn = false;
					gSound.oldMVol = gSound.mVolume;
					gSound.mVolume = 0.0f;
					experimental::AudioEngine::stop(soundIDList[14]);
				}
				else
				{
					gSound.musicOn = true;
					gSound.mVolume = gSound.oldMVol;
					if (levelmanager.currentlevel == 1)
					{
						soundIDList[14] = experimental::AudioEngine::play2d("\\res\\sound\\music\\samlvl_music.mp3", true, gSound.mVolume);
					}
					else if (levelmanager.currentlevel == 2)
					{
						soundIDList[14] = experimental::AudioEngine::play2d("\\res\\sound\\music\\candylvl_music.mp3", true, gSound.mVolume);
					}
					else if (levelmanager.currentlevel == 3)
					{
						soundIDList[14] = experimental::AudioEngine::play2d("\\res\\sound\\music\\ptlvl_music.mp3", true, gSound.mVolume);
					}
					else if (levelmanager.currentlevel == 4)
					{
						soundIDList[14] = experimental::AudioEngine::play2d("\\res\\sound\\music\\sunlvl_music.mp3", true, gSound.mVolume);
					}
				}
			break;
		//CTRL + S = Toggle SFX On/Off
		case EventKeyboard::KeyCode::KEY_S:
			if (button2) //if CTRL is pressed down too
				//toggle sfx on/off
				if (gSound.sfxOn)
				{
					gSound.sfxOn = false;
					experimental::AudioEngine::stop(soundIDList[5]);
					experimental::AudioEngine::stop(soundIDList[11]);
				}
				else
				{
					gSound.sfxOn = true;
					//hack fix for now, need to deal with looped sfx properly in processSound()
					if (levelmanager.currentlevel > 3)
					{
						soundIDList[5] = experimental::AudioEngine::play2d("\\res\\sound\\sfx\\ptero_swoop.mp3", true, 0.1f);
						isSFXPlaying[5] = true;
					} 
				}
			else
			{
				ymove -= 2;
			}
			break;
		case EventKeyboard::KeyCode::KEY_EQUAL:
			if (gSound.musicOn && gSound.mVolume <= 1.0f)
			{
				gSound.mVolume += 0.1f;
				experimental::AudioEngine::setVolume(soundIDList[14], gSound.mVolume);
			}
			break;
		case EventKeyboard::KeyCode::KEY_MINUS:
			if (gSound.musicOn && gSound.mVolume >= 0.0f)
			{
				gSound.mVolume -= 0.1f;
				experimental::AudioEngine::setVolume(soundIDList[14], gSound.mVolume);
			}
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
	case EventKeyboard::KeyCode::KEY_W:
		ymove = 0;
		break;
	case EventKeyboard::KeyCode::KEY_S:
		if (!button2)
			ymove = 0;
		break;
	case EventKeyboard::KeyCode::KEY_A:
		xmove = 0;
		break;
	case EventKeyboard::KeyCode::KEY_D:
		xmove = 0;
		break;
	case EventKeyboard::KeyCode::KEY_SPACE:
		button1 = false;
		break;
	case EventKeyboard::KeyCode::KEY_CTRL:
		button2 = false;
		break;
	case EventKeyboard::KeyCode::KEY_ESCAPE:
		if (isPaused == false)
		{
			PauseGame();
		}
		else
		{
			ResumeGame();
		}
		break;
	}

	event->stopPropagation();

}



void ClientDemo::Joystick(cocos2d::Event* event)
{
	EventJoystick* e = (EventJoystick*)event;
	//log("JOYSTICK PRESENT");
	bool present = e->isPresent();
	//log(std::to_string(present).c_str());
	if (present)
	{
			//log(e->getName());
			int foraxis;
			const float* axisval = e->getAxes(&foraxis);
			float xval = axisval[0];
			float yval = axisval[1];
			//log(std::to_string(xval).c_str());
			//log(std::to_string(yval).c_str());
			bool nox = false;
			bool noy = false;
			if (yval > 0.5)
			{
				ymove = -2;
			}
			else if (yval < -0.5)
			{
				ymove = 2;
			}
			else {
				ymove = 0;
			}
			if (xval > 0.5)
			{
				xmove = 2;
			}
			else if (xval < -0.5)
			{
				xmove = -2;
			}
			else {
				xmove = 0;
			}
			if (nox && noy)
			{
				xmove = 0;
				ymove = 0;
			}


			int forbutton;
			const unsigned char* buttonval = e->getButtonValues(&forbutton);
			unsigned char b0 = buttonval[0];
			unsigned char b1 = buttonval[1];
			unsigned char b2 = buttonval[2];
			unsigned char b3 = buttonval[3];
			unsigned char b8 = buttonval[7];
		
			if (b0 || b1 || b2 || b3)
			{
				button1 = true;
			}
			else
			{
				button1 = false;
			}
			if (b8)
			{
				button3 = true;
			}
			if (button3 == true && !b8) //b8 pressed then released
			{
				if (isPaused)
				{
					ResumeGame();
				}
				else
				{
					PauseGame();
				}
				button3 = false;
			}
	}
}


// This will convert the players coordinates into tile coordinates
Point ClientDemo::plyrCoordToTileCoord(int playerNum)
{
	int newx = players[playerNum - 1]->getPositionX() + xmove;
	int newy = (levelmanager.levelmap->getMapSize().height*levelmanager.levelmap->getTileSize().height) - (players[playerNum - 1]->getPositionY() + ymove);
  	int tilex = newx / (levelmanager.levelmap->getTileSize().width);
	int tiley = newy / (levelmanager.levelmap->getTileSize().height);
	return(Point(tilex,tiley));
}

int ClientDemo::getTileProperties(TMXLayer* mapLayer, Point tileCoord)
{
	if (tileCoord.x >= 0 && tileCoord.x <= levelmanager.levelmap->getMapSize().width && tileCoord.y >= 0 && tileCoord.y <= levelmanager.levelmap->getMapSize().height)
	{
		return (mapLayer->getTileGIDAt(tileCoord));
	}
}

void ClientDemo::changeLabelColor(int bTile, int playerNum)
{
	/*if (playerNum == 1) {
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
					p1CLabel->setFontFillColor(Color3B(247, 52, 47));
					gSound.pTrigs[0].onBucket = true; //0=p1, 1=p2, 2=p3, 3=p4
				}
				if ("true" == b)
				{
					//p1CLabel->setString("Blue");
					p1CLabel->setFontFillColor(Color3B(49, 58, 197));
					gSound.pTrigs[0].onBucket = true;
				}
				if ("true" == y) {
					//p1CLabel->setString("Yellow");
					p1CLabel->setFontFillColor(Color3B(222, 244, 69));
					gSound.pTrigs[0].onBucket = true;
				}
				if ("true" == o) {
					//p1CLabel->setString("Orange");
					p1CLabel->setFontFillColor(Color3B(234, 152, 46));
					gSound.pTrigs[0].onBucket = true;
				}
				if ("true" == blk) {
					p1CLabel->setFontFillColor(Color3B(36, 33, 25));
					gSound.pTrigs[0].onBucket = true;
				}

				if ("true" == b2) {
					p1CLabel->setFontFillColor(Color3B(4, 31, 131));
					gSound.pTrigs[0].onBucket = true;
				}
				if ("true" == b3) {
					p1CLabel->setFontFillColor(Color3B(1, 16, 73));
					gSound.pTrigs[0].onBucket = true;
				}
				if ("true" == g1) {
					p1CLabel->setFontFillColor(Color3B(2, 123, 36));
					gSound.pTrigs[0].onBucket = true;
				}
				if ("true" == g2) {
					p1CLabel->setFontFillColor(Color3B(11, 187, 60));
					gSound.pTrigs[0].onBucket = true;
				}
				if ("true" == g3) {
					p1CLabel->setFontFillColor(Color3B(47, 247, 145));
					gSound.pTrigs[0].onBucket = true;
				}
				if ("true" == w) {
					p1CLabel->setFontFillColor(Color3B(255, 255, 255));
					gSound.pTrigs[0].onBucket = true;
				}
				if ("true" == gy1) {
					p1CLabel->setFontFillColor(Color3B(101, 141, 255));
					gSound.pTrigs[0].onBucket = true;
				}
				if ("true" == gy2) {
					p1CLabel->setFontFillColor(Color3B(203, 216, 229));
					gSound.pTrigs[0].onBucket = true;
				}
				if ("true" == p) {
					p1CLabel->setFontFillColor(Color3B(148, 55, 122));
					gSound.pTrigs[0].onBucket = true;
				}
				if ("true" == r2) {
					p1CLabel->setFontFillColor(Color3B(187, 11, 44));
					gSound.pTrigs[0].onBucket = true;
				}
				if ("true" == r1) {
					p1CLabel->setFontFillColor(Color3B(247, 52, 47));
					gSound.pTrigs[0].onBucket = true;
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
					p2CLabel->setFontFillColor(Color3B(247, 52, 47));
					gSound.pTrigs[1].onBucket = true;
				}
				if ("true" == b)
				{
					p2CLabel->setFontFillColor(Color3B(49, 58, 197));
					gSound.pTrigs[1].onBucket = true;
				}
				if ("true" == y) {
					p2CLabel->setFontFillColor(Color3B(222, 244, 69));
					gSound.pTrigs[1].onBucket = true;
				}
				if ("true" == o) {
					p2CLabel->setFontFillColor(Color3B(234, 152, 46));
					gSound.pTrigs[1].onBucket = true;
				}
				if ("true" == blk) {
					p1CLabel->setFontFillColor(Color3B(36, 33, 25));
					gSound.pTrigs[1].onBucket = true;
				}

				if ("true" == b2) {
					p2CLabel->setFontFillColor(Color3B(4, 31, 131));
					gSound.pTrigs[1].onBucket = true;
				}
				if ("true" == b3) {
					p2CLabel->setFontFillColor(Color3B(1, 16, 73));
					gSound.pTrigs[1].onBucket = true;
				}
				if ("true" == g1) {
					p2CLabel->setFontFillColor(Color3B(2, 123, 36));
					gSound.pTrigs[1].onBucket = true;
				}
				if ("true" == g2) {
					p2CLabel->setFontFillColor(Color3B(11, 187, 60));
					gSound.pTrigs[1].onBucket = true;
				}
				if ("true" == g3) {
					p2CLabel->setFontFillColor(Color3B(47, 247, 145));
					gSound.pTrigs[1].onBucket = true;
				}
				if ("true" == w) {
					p2CLabel->setFontFillColor(Color3B(255, 255, 255));
					gSound.pTrigs[1].onBucket = true;
				}
				if ("true" == gy1) {
					p2CLabel->setFontFillColor(Color3B(101, 141, 255));
					gSound.pTrigs[1].onBucket = true;
				}
				if ("true" == gy2) {
					p2CLabel->setFontFillColor(Color3B(203, 216, 229));
					gSound.pTrigs[1].onBucket = true;
				}
				if ("true" == p) {
					p2CLabel->setFontFillColor(Color3B(148, 55, 122));
					gSound.pTrigs[1].onBucket = true;
				}
				if ("true" == r2) {
					p2CLabel->setFontFillColor(Color3B(187, 11, 44));
					gSound.pTrigs[1].onBucket = true;
				}
				if ("true" == r1) {
					p2CLabel->setFontFillColor(Color3B(247, 52, 47));
					gSound.pTrigs[1].onBucket = true;
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
					p3CLabel->setFontFillColor(Color3B(247, 52, 47));
					gSound.pTrigs[2].onBucket = true;
				}
				if ("true" == b)
				{
					p3CLabel->setFontFillColor(Color3B(49, 58, 197));
					gSound.pTrigs[2].onBucket = true;
				}
				if ("true" == y) {
					p3CLabel->setFontFillColor(Color3B(222, 244, 69));
					gSound.pTrigs[2].onBucket = true;
				}
				if ("true" == o) {
					p3CLabel->setFontFillColor(Color3B(234, 152, 46));
					gSound.pTrigs[2].onBucket = true;
				}
				if ("true" == blk) {
					p1CLabel->setFontFillColor(Color3B(36, 33, 25));
					gSound.pTrigs[2].onBucket = true;
				}

				if ("true" == b2) {
					p3CLabel->setFontFillColor(Color3B(4, 31, 131));
					gSound.pTrigs[2].onBucket = true;
				}
				if ("true" == b3) {
					p3CLabel->setFontFillColor(Color3B(1, 16, 73));
					gSound.pTrigs[2].onBucket = true;
				}
				if ("true" == g1) {
					p3CLabel->setFontFillColor(Color3B(2, 123, 36));
					gSound.pTrigs[2].onBucket = true;
				}
				if ("true" == g2) {
					p3CLabel->setFontFillColor(Color3B(11, 187, 60));
					gSound.pTrigs[2].onBucket = true;
				}
				if ("true" == g3) {
					p3CLabel->setFontFillColor(Color3B(47, 247, 145));
					gSound.pTrigs[2].onBucket = true;
				}
				if ("true" == w) {
					p3CLabel->setFontFillColor(Color3B(255, 255, 255));
					gSound.pTrigs[2].onBucket = true;
				}
				if ("true" == gy1) {
					p3CLabel->setFontFillColor(Color3B(101, 141, 255));
					gSound.pTrigs[2].onBucket = true;
				}
				if ("true" == gy2) {
					p3CLabel->setFontFillColor(Color3B(203, 216, 229));
					gSound.pTrigs[2].onBucket = true;
				}
				if ("true" == p) {
					p3CLabel->setFontFillColor(Color3B(148, 55, 122));
					gSound.pTrigs[2].onBucket = true;
				}
				if ("true" == r2) {
					p3CLabel->setFontFillColor(Color3B(187, 11, 44));
					gSound.pTrigs[2].onBucket = true;
				}
				if ("true" == r1) {
					p3CLabel->setFontFillColor(Color3B(247, 52, 47));
					gSound.pTrigs[2].onBucket = true;
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
					p4CLabel->setFontFillColor(Color3B(247, 52, 47));
					gSound.pTrigs[3].onBucket = true;
				}
				if ("true" == b)
				{
					p4CLabel->setFontFillColor(Color3B(49, 58, 197));
					gSound.pTrigs[3].onBucket = true;
				}
				if ("true" == y) {
					p4CLabel->setFontFillColor(Color3B(222, 244, 69));
					gSound.pTrigs[3].onBucket = true;
				}
				if ("true" == o) {
					p4CLabel->setFontFillColor(Color3B(234, 152, 46));
					gSound.pTrigs[3].onBucket = true;
				}
				if ("true" == blk) {
					p1CLabel->setFontFillColor(Color3B(36, 33, 25));
					gSound.pTrigs[3].onBucket = true;
				}

				if ("true" == b2) {
					p4CLabel->setFontFillColor(Color3B(4, 31, 131));
					gSound.pTrigs[3].onBucket = true;
				}
				if ("true" == b3) {
					p4CLabel->setFontFillColor(Color3B(1, 16, 73));
					gSound.pTrigs[3].onBucket = true;
				}
				if ("true" == g1) {
					p4CLabel->setFontFillColor(Color3B(2, 123, 36));
					gSound.pTrigs[3].onBucket = true;
				}
				if ("true" == g2) {
					p4CLabel->setFontFillColor(Color3B(11, 187, 60));
					gSound.pTrigs[3].onBucket = true;
				}
				if ("true" == g3) {
					p4CLabel->setFontFillColor(Color3B(47, 247, 145));
					gSound.pTrigs[3].onBucket = true;
				}
				if ("true" == w) {
					p4CLabel->setFontFillColor(Color3B(255, 255, 255));
					gSound.pTrigs[3].onBucket = true;
				}
				if ("true" == gy1) {
					p4CLabel->setFontFillColor(Color3B(101, 141, 255));
					gSound.pTrigs[3].onBucket = true;
				}
				if ("true" == gy2) {
					p4CLabel->setFontFillColor(Color3B(203, 216, 229));
					gSound.pTrigs[3].onBucket = true;
				}
				if ("true" == p) {
					p4CLabel->setFontFillColor(Color3B(148, 55, 122));
					gSound.pTrigs[3].onBucket = true;
				}
				if ("true" == r2) {
					p4CLabel->setFontFillColor(Color3B(187, 11, 44));
					gSound.pTrigs[3].onBucket = true;
				}
				if ("true" == r1) {
					p3CLabel->setFontFillColor(Color3B(247, 52, 47));
					gSound.pTrigs[3].onBucket = true;
				}
			}
		}
	}*/
}


// Will check to see if you are on a bucket and change the color of the player's label
//UNUSED
void ClientDemo::space()
{	
		Point tileCoord = plyrCoordToTileCoord(playernum);
		int bTile = getTileProperties(blockage, tileCoord);
		changeLabelColor(bTile, playernum);
}


void ClientDemo::loadLevel(int level)
{
	//code that should be run only after game start (removing previous assets)
	if (levelmanager.currentlevel != 0) //at game start currentlevel = 0
	{
		for (unsigned int i = 0; i < SPRITE_GRID.size(); i++)
		{
			for (unsigned int j = 0; j < SPRITE_GRID[i].size(); j++)
			{
				removeChild(SPRITE_GRID[i][j]);
			}
		}

		//remove old map
		removeChild(levelmanager.levelmap);

		//reset player color+label on new level
		for (unsigned int i = 0; i < players.size(); i++)
		{
			players[i]->setColor("");
			players[i]->getLabel()->setColor(Color3B::WHITE);
		}

	}

	if (transitionManager.start_timer == 60) //if not in transition and centercamera() has been called before (not new game, not player joining game in progress)
	{
		NotInTransition = false;

		//stop playing victory music
		experimental::AudioEngine::stop(soundIDList[14]);

		transitionManager.loadTransition(level);
		for (Sprite* ts : transitionManager.transitionSprite)
		{
			addChild(ts, 10);
		}
	}

	levelmanager.setLevel(level);

	addChild(levelmanager.levelmap, -1000);

	setupPaintTiles();


	blockage = levelmanager.levelmap->getLayer("Collision");
	if (blockage != NULL)
	{
		blockage->setVisible(false);
	}
	
	bucketlayer = levelmanager.levelmap->getLayer("Paintbuckets");

	blankCanvas = levelmanager.levelmap->getLayer("BlankCanvas");
	
	if (blankCanvas != NULL)
	{
		blankCanvas->setCascadeOpacityEnabled(true);
		//below is hack fix until check for client joining game in progress is coded in
		blankCanvas->setVisible(false); //so players joining game in progress see paintings
	}

	spawnObjs = levelmanager.levelmap->objectGroupNamed("SpawnObjects");

	if (spawnObjs == NULL) {
		log("TMX map has SpawnObjects layer");
	}
	else {
		playerOneSP = spawnObjs->objectNamed("P1spawnPoint");
		playerTwoSP = spawnObjs->objectNamed("P2spawnPoint");
		playerThreeSP = spawnObjs->objectNamed("P3spawnPoint");
		playerFourSP = spawnObjs->objectNamed("P4spawnPoint");
		player1->setPosition(Vec2(playerOneSP["x"].asInt(), playerOneSP["y"].asInt()));
		player2->setPosition(Vec2(playerTwoSP["x"].asInt(), playerTwoSP["y"].asInt()));
		player3->setPosition(Vec2(playerThreeSP["x"].asInt(), playerThreeSP["y"].asInt()));
		player4->setPosition(Vec2(playerFourSP["x"].asInt(), playerFourSP["y"].asInt()));
	}

	if (nullptr != tileHighlight)
	{
		tileHighlight->setOpacity(0);
	}
	if (nullptr != bucketHighlight)
	{
		bucketHighlight->setOpacity(0);
	}

	if (level == 1)
	{
		pterodactyl->setVisible(false);
		villain->setVisible(false);
		candy->setVisible(false);
		//this->setScale(1.0f);
	}
	else if (level == 2) {
		gSound.levelChange = true;
		pterodactyl->setVisible(false);
		villain->setVisible(true);
		villain->setOpacity(0);
	}
	else if (level == 3) {
		gSound.levelChange = true;
		pterodactyl->setVisible(false);
		villain->setVisible(true);
		candy->setVisible(true);
		villain->setOpacity(0);
	}
	else if (level == 4) {
		gSound.levelChange = true;
		pterodactyl->setVisible(true);
		villain->setVisible(true);
		candy->setVisible(true);
		villain->setOpacity(0);
	}

	smoothCamera = true;

	for (unsigned int i = 0; i < players.size(); i++)
	{
		players[i]->setVisible(false);
	}
	if (EVENTS_ON == 0)
	{
		blankCanvas->setVisible(false);
	}
	else
	{
		//eventActive = 1;
	}

	button1 = false;
}

void ClientDemo::setupPaintTiles()
{
	SPRITE_GRID.resize(CURRENT_GRID.size());
	for (unsigned int i = 0; i < SPRITE_GRID.size(); i++)
	{
		SPRITE_GRID[i].resize(CURRENT_GRID[i].size());
	}

	for (unsigned int i = 0; i < SPRITE_GRID.size(); i++)
	{
		for (unsigned int j = 0; j < SPRITE_GRID[i].size(); j++)
		{
			SPRITE_GRID[i][j] = PaintTile::create();
			SPRITE_GRID[i][j]->setDry(true); //client will not see wet tiles (hidden server mechanic)
			SPRITE_GRID[i][j]->setPosition(24 * j + levelmanager.tilestartpoint.x, 24 * i + levelmanager.tilestartpoint.y);
			SPRITE_GRID[i][j]->debugDraw(false);
			addChild(SPRITE_GRID[i][j], -999);
		}
	}

}


void ClientDemo::centerCamera()
{
	if (NotInTransition)
	{
		if (eventActive == 0)
		{
			if (smoothCamera)
			{
				Vec2 camPos = Camera::getDefaultCamera()->getPosition();
				Vec2 pPos = players[playernum - 1]->getPosition();
				int dist = players[playernum - 1]->getSpeed()*players[playernum - 1]->speedboost + players[playernum - 1]->getSpeed()*players[playernum - 1]->speedboost;

				//if camera is further away from player position than normal, smooth camera
				if ((abs(camPos.x - pPos.x) + abs(camPos.y - pPos.y)) > dist)
				{
					//lerping tenth of distance
					camPos.x += (pPos.x - camPos.x) * 0.1f;
					camPos.y += (pPos.y - camPos.y) * 0.1f;
					Camera::getDefaultCamera()->setPosition(camPos);
				}
				else
				{
					smoothCamera = false;
				}
			}
			else
			{
				Camera::getDefaultCamera()->setPosition(players[playernum - 1]->getPosition());
			}
		}
		else if (eventActive == 1) //sam painting event happening
		{
			Camera::getDefaultCamera()->setPosition(villain->getPosition());
		}
		else if (eventActive == 2)
		{
			if (smoothCamera)
			{
				Vec2 camPos = Camera::getDefaultCamera()->getPosition();

				//if camera is further away from player position than normal, smooth camera
				if ((abs(camPos.x - pos.x) + abs(camPos.y - pos.y)) > 4)
				{
					//lerping tenth of distance
					camPos.x += (pos.x - camPos.x) * 0.1f;
					camPos.y += (pos.y - camPos.y) * 0.1f;
					Camera::getDefaultCamera()->setPosition(camPos);
				}
				else
				{
					smoothCamera = false;
				}
			}
			else
			{
				Camera::getDefaultCamera()->setPosition(pos);
			}
		}
		transitionManager.start_timer = 60;
		//if((players[playernum -1]->getPositionX() > 320 && players[playernum - 1]->getPositionX() < (levelmanager.levelmap->getMapSize().width*24)-320) || (players[playernum - 1]->getPositionY() > 180 && players[playernum - 1]->getPositionY() < (levelmanager.levelmap->getMapSize().height * 24) - 180))
	}
	else
	{
		Camera::getDefaultCamera()->setPosition(winSizeWidth, winSizeHeight);
	}
}

void ClientDemo::processSound(ServerPositionPacket &p) {

	//===========================================================
	//					ISSUES AND BUGS
	//===========================================================
	//	1. Need to sync animations with sfx.
	//
	//	2. Use Server Messages for grid detection.
	//
	//	3. Volume of various SFX need a little more adjustment.
	//
	//	4. Idle Player check is hack-fixed for now, will implement
	//	better later.
	//
	//	5. Strange bug where sometimes sam_playerhit always plays
	//	instead of paint. Fixed by resetting game.
	//
	//  6. Find a cleaner way to use callbacks.
	//
	//	7. Edit sfx to normalize audio and allow sfx toggling to
	//	keep processing sfx, but keeping volume at zero. This 
	//	ensures sfx/animation synchronization.
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
	// soundIDList[13] = player_footsteps
	// soundIDList[14] = music
	// soundIDList[15] = sam_laugh

	//these callbacks only work if theyre outside for loops.
	experimental::AudioEngine::setFinishCallback(soundIDList[1], [&](int id, const std::string& filePath)
	{
		isSFXPlaying[1] = false;
	});

	experimental::AudioEngine::setFinishCallback(soundIDList[7], [&](int id, const std::string& filePath)
	{
		isSFXPlaying[7] = false;
	});

	experimental::AudioEngine::setFinishCallback(soundIDList[9], [&](int id, const std::string& filePath)
	{
		isSFXPlaying[9] = false;
	});

	experimental::AudioEngine::setFinishCallback(soundIDList[12], [&](int id, const std::string& filePath)
	{
		isSFXPlaying[12] = false;
	});
	//end of play2d callback definitions

	/*//if music was toggled on/off
	if (gSound.mVolume > 0.0f && gSound.musicOn == false)
	{
		gSound.oldMVol = gSound.mVolume;
		gSound.mVolume = 0.0f;
		experimental::AudioEngine::stop(soundIDList[14]);
		//experimental::AudioEngine::setVolume(soundIDList[14], gSound.mVolume);
	}
	else if (gSound.musicOn == true && gSound.mVolume == 0.0f)
	{
		gSound.mVolume = gSound.oldMVol;
		if (levelmanager.currentlevel == 1)
		{
			soundIDList[14] = experimental::AudioEngine::play2d("\\res\\sound\\music\\samlvl_music.mp3", true, gSound.mVolume);
		}
		else if (levelmanager.currentlevel == 2)
		{
			soundIDList[14] = experimental::AudioEngine::play2d("\\res\\sound\\music\\candylvl_music.mp3", true, gSound.mVolume);
		}
		else if (levelmanager.currentlevel == 3)
		{
			soundIDList[14] = experimental::AudioEngine::play2d("\\res\\sound\\music\\ptlvl_music.mp3", true, gSound.mVolume);
		}
		else if (levelmanager.currentlevel == 4)
		{
			soundIDList[14] = experimental::AudioEngine::play2d("\\res\\sound\\music\\sunlvl_music.mp3", true, gSound.mVolume);
		}
	}
	//end of music toggled on/off */




	//If Sam or pterodactyl touches a player
	for (unsigned int i = 0; i < 4; i++)
	{
		if (gSound.pTrigs[i].samCollide == true && gSound.pTrigs[i].hasPainted == true && villain->getOpacity() > 0)
		{
			if (false == isSFXPlaying[1])
			{
				soundIDList[1] = experimental::AudioEngine::play2d("\\res\\sound\\sfx\\sam_playerhit.mp3", false, 0.8f);
				isSFXPlaying[1] = true;
				gSound.pTrigs[i].samCollide = false;
			}
		}
		else if (gSound.pTrigs[i].ptCollide == true && gSound.pTrigs[i].hasPainted == true)
		{
			if (false == isSFXPlaying[12])
			{
				soundIDList[12] = experimental::AudioEngine::play2d("\\res\\sound\\sfx\\ptero_playerhit.mp3", false, 0.8f);
				isSFXPlaying[12] = true;
				gSound.pTrigs[i].ptCollide = false;
			}
		}
	}
	//If Sam or pterodactyl touches a player - end


	//If player gets/loses candy buff

	for (unsigned int i = 0; i < 3; i++)
	{
		if (gSound.pTrigs[i].gotCandy == true)
		{
			if (isSFXPlaying[7] == false)
			{
				soundIDList[7] = experimental::AudioEngine::play2d("\\res\\sound\\sfx\\player_candy_pickup.mp3", false, 0.8f);
				isSFXPlaying[7] = true;
				gSound.pTrigs[i].gotCandy = false;
			}
		}
		else if (gSound.pTrigs[i].lostCandy == true)
		{
			if (isSFXPlaying[9] == false)
			{
				soundIDList[9] = experimental::AudioEngine::play2d("\\res\\sound\\sfx\\player_candy_lost.mp3", false, 0.8f);
				isSFXPlaying[9] = true;
				gSound.pTrigs[i].lostCandy = false;
			}
		}
	}
	//If player gets/loses candy buff - end

	//If level solved
	if (gSound.levelChange == true)
	{
		//play level completed sfx - DEPRECATED: TransitionManager now handles lvl completed sfx
		//if (isSFXPlaying[10] == false)
		//{
		//	soundIDList[10] = experimental::AudioEngine::play2d("\\res\\sound\\sfx\\puzzle_solved.mp3");
		//	isSFXPlaying[10] = true;
		//	experimental::AudioEngine::setFinishCallback(soundIDList[10], [&](int id, const std::string& filePath)
		//	{
				experimental::AudioEngine::stop(soundIDList[14]);
		//		isSFXPlaying[10] = false;
				if (gSound.musicOn && NotInTransition)
				{//play new level's music
					if (levelmanager.currentlevel == 1)
					{
						soundIDList[14] = experimental::AudioEngine::play2d("\\res\\sound\\music\\samlvl_music.mp3", true, 0.4f);
					}
					else if (levelmanager.currentlevel == 2)
					{
						soundIDList[14] = experimental::AudioEngine::play2d("\\res\\sound\\music\\candylvl_music.mp3", true, 0.4f);
					}
					else if (levelmanager.currentlevel == 3)
					{
						soundIDList[14] = experimental::AudioEngine::play2d("\\res\\sound\\music\\ptlvl_music.mp3", true, 0.4f);
					}
					else if (levelmanager.currentlevel == 4)
					{
						soundIDList[14] = experimental::AudioEngine::play2d("\\res\\sound\\music\\sunlvl_music.mp3", true, 0.4f);
					}
					gSound.levelChange = false;
				}
//			});	
	}
	//}
	//If level solved - end

	//===========================================================
	//    END OF NON-ANIMATION BASED AUDIO
	//===========================================================





	//===========================================================
	//        ANIMATION-BASED AUDIO
	//===========================================================


	//switch used here in case further animation states are created. modular switch-cases superior.
	switch (p.p1anim) {
	/*	//case 1-4 are walking in the 4 directions
	case 1:
		if (isSFXPlaying[13] == false)
		{
			soundIDList[13] = experimental::AudioEngine::play2d("\\res\\sound\\sfx\\player_footsteps.mp3", true, 0.4f);
			isSFXPlaying[13] = true;
		}
		break;
	case 2:
		if (isSFXPlaying[13] == false)
		{
			soundIDList[13] = experimental::AudioEngine::play2d("\\res\\sound\\sfx\\player_footsteps.mp3", true, 0.4f);
			isSFXPlaying[13] = true;
		}
		break;
	case 3:
		if (isSFXPlaying[13] == false)
		{
			soundIDList[13] = experimental::AudioEngine::play2d("\\res\\sound\\sfx\\player_footsteps.mp3", true, 0.4f);
			isSFXPlaying[13] = true;
		}
		break;
	case 4:
		if (isSFXPlaying[13] == false)
		{
			soundIDList[13] = experimental::AudioEngine::play2d("\\res\\sound\\sfx\\player_footsteps.mp3", true, 0.4f);
			isSFXPlaying[13] = true;
		}
		break; */
	case 5: //p1paint
		if (gSound.pTrigs[0].onBucket == true) //if the player is on a bucket
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
			gSound.pTrigs[0].onBucket = false;
		}
		else if (gSound.pTrigs[0].onGrid == true) //if player is on grid
		{
			if (isSFXPlaying[0] == false)
			{
				soundIDList[0] = experimental::AudioEngine::play2d("\\res\\sound\\sfx\\paint.mp3");
				isSFXPlaying[0] = true;
				gSound.pTrigs[0].hasPainted = true; //temp fix for checking if player is idle
				experimental::AudioEngine::setFinishCallback(soundIDList[0], [&](int id, const std::string& filePath)
				{
					isSFXPlaying[0] = false;
				});
			}
			gSound.pTrigs[0].onGrid = false;
		}
		break;
	//case 35:
	//	if (isSFXPlaying[13] == true)
	//	{
	//		experimental::AudioEngine::stop(soundIDList[13]);
	//		isSFXPlaying[13] = false;
	//	}
	//	break;
	default: break;
	}
	switch (p.p2anim) {
	/*	//case 7-10 are walking in the 4 directions
	case 7:
		if (isSFXPlaying[13] == false)
		{
			soundIDList[13] = experimental::AudioEngine::play2d("\\res\\sound\\sfx\\player_footsteps.mp3", true, 0.4f);
			isSFXPlaying[13] = true;
		}
		break;
	case 8:
		if (isSFXPlaying[13] == false)
		{
			soundIDList[13] = experimental::AudioEngine::play2d("\\res\\sound\\sfx\\player_footsteps.mp3", true, 0.4f);
			isSFXPlaying[13] = true;
		}
		break;
	case 9:
		if (isSFXPlaying[13] == false)
		{
			soundIDList[13] = experimental::AudioEngine::play2d("\\res\\sound\\sfx\\player_footsteps.mp3", true, 0.4f);
			isSFXPlaying[13] = true;
		}
		break;
	case 10:
		if (isSFXPlaying[13] == false)
		{
			soundIDList[13] = experimental::AudioEngine::play2d("\\res\\sound\\sfx\\player_footsteps.mp3", true, 0.4f);
			isSFXPlaying[13] = true;
		}
		break; */
	case 11: //p2paint
		if (gSound.pTrigs[1].onBucket == true) //if the player is on a bucket
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
			gSound.pTrigs[1].onBucket = false;
		}
		else if (gSound.pTrigs[1].onGrid == true) //if player is on grid
		{
			if (isSFXPlaying[0] == false)
			{
				soundIDList[0] = experimental::AudioEngine::play2d("\\res\\sound\\sfx\\paint.mp3");
				isSFXPlaying[0] = true;
				gSound.pTrigs[1].hasPainted = true; //temp fix for checking if player is idle
				experimental::AudioEngine::setFinishCallback(soundIDList[0], [&](int id, const std::string& filePath)
				{
					isSFXPlaying[0] = false;
				});
			}
			gSound.pTrigs[1].onGrid = false;
		}
		break;
	//case 36:
	//	if (isSFXPlaying[13] == true)
	//	{
	//		experimental::AudioEngine::stop(soundIDList[13]);
	//		isSFXPlaying[13] = false;
	//	}
		break;
	default: break;
	}
	switch (p.p3anim)
	{
		//case 13-16 are walking in the 4 directions
	/*case 13:
		if (isSFXPlaying[13] == false)
		{
			soundIDList[13] = experimental::AudioEngine::play2d("\\res\\sound\\sfx\\player_footsteps.mp3", true, 0.4f);
			isSFXPlaying[13] = true;
		}
		break;
	case 14:
		if (isSFXPlaying[13] == false)
		{
			soundIDList[13] = experimental::AudioEngine::play2d("\\res\\sound\\sfx\\player_footsteps.mp3", true, 0.4f);
			isSFXPlaying[13] = true;
		}
		break;
	case 15:
		if (isSFXPlaying[13] == false)
		{
			soundIDList[13] = experimental::AudioEngine::play2d("\\res\\sound\\sfx\\player_footsteps.mp3", true, 0.4f);
			isSFXPlaying[13] = true;
		}
		break;
	case 16:
		if (isSFXPlaying[13] == false)
		{
			soundIDList[13] = experimental::AudioEngine::play2d("\\res\\sound\\sfx\\player_footsteps.mp3", true, 0.4f);
			isSFXPlaying[13] = true;
		}
		break;*/
	case 17: //p3paint
		if (gSound.pTrigs[2].onBucket == true) //if the player is on a bucket
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
			gSound.pTrigs[2].onBucket = false;
		}
		else if (gSound.pTrigs[2].onGrid == true) //if player is on grid
		{
			if (isSFXPlaying[0] == false)
			{
				soundIDList[0] = experimental::AudioEngine::play2d("\\res\\sound\\sfx\\paint.mp3");
				isSFXPlaying[0] = true;
				gSound.pTrigs[2].hasPainted = true; //temp fix for checking if player is idle
				experimental::AudioEngine::setFinishCallback(soundIDList[0], [&](int id, const std::string& filePath)
				{
					isSFXPlaying[0] = false;
				});
			}
			gSound.pTrigs[2].onGrid = false;
		}
		break;
	//case 37:
	//	if (isSFXPlaying[13] == true)
	//	{
	//		experimental::AudioEngine::stop(soundIDList[13]);
	//		isSFXPlaying[13] = false;
	//	}
	//	break;
	default: break;
}
	switch (p.p4anim) {
	/*		//case 13-16 are walking in the 4 directions
	case 19:
		if (isSFXPlaying[13] == false)
		{
			soundIDList[13] = experimental::AudioEngine::play2d("\\res\\sound\\sfx\\player_footsteps.mp3", true, 0.4f);
			isSFXPlaying[13] = true;
		}
		break;
	case 20:
		if (isSFXPlaying[13] == false)
		{
			soundIDList[13] = experimental::AudioEngine::play2d("\\res\\sound\\sfx\\player_footsteps.mp3", true, 0.4f);
			isSFXPlaying[13] = true;
		}
		break;
	case 21:
		if (isSFXPlaying[13] == false)
		{
			soundIDList[13] = experimental::AudioEngine::play2d("\\res\\sound\\sfx\\player_footsteps.mp3", true, 0.4f);
			isSFXPlaying[13] = true;
		}
		break;
	case 22:
		if (isSFXPlaying[13] == false)
		{
			soundIDList[13] = experimental::AudioEngine::play2d("\\res\\sound\\sfx\\player_footsteps.mp3", true, 0.4f);
			isSFXPlaying[13] = true;
		}
		break; */
	case 23: //p4paint
		if (gSound.pTrigs[3].onBucket == true) //if the player is on a bucket
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
			gSound.pTrigs[3].onBucket = false;
		}
		else if (gSound.pTrigs[3].onGrid == true) //if player is on grid
		{
			if (isSFXPlaying[0] == false)
			{
				soundIDList[0] = experimental::AudioEngine::play2d("\\res\\sound\\sfx\\paint.mp3");
				isSFXPlaying[0] = true;
				gSound.pTrigs[3].hasPainted = true; //temp fix for checking if player is idle
				experimental::AudioEngine::setFinishCallback(soundIDList[0], [&](int id, const std::string& filePath)
				{
					isSFXPlaying[0] = false;
				});
			}
			gSound.pTrigs[3].onGrid = false;
		}
		break;
	//case 38:
	//	if (isSFXPlaying[13] == true)
	//	{
	//		experimental::AudioEngine::stop(soundIDList[13]);
	//		isSFXPlaying[13] = false;
	//	}
	//	break;
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
		if (false == isSFXPlaying[5] && pterodactyl->isVisible() == true && levelmanager.currentlevel > 3) //shouldnt need 3rd check, hack fix for now
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
		if (false == isSFXPlaying[5] && pterodactyl->isVisible() == true && levelmanager.currentlevel > 3) //shouldnt need 3rd check, hack fix for now)
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
		if (false == isSFXPlaying[11] && pterodactyl->isVisible() == true && levelmanager.currentlevel > 3) //shouldnt need 3rd check, hack fix for now
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
		if (false == isSFXPlaying[11] && pterodactyl->isVisible() == true && levelmanager.currentlevel > 3) //shouldnt need 3rd check, hack fix for now
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

	//hackfix to get lvl 1 music to play
	//stopall() in howtoplay.cpp cant be followed too quickly by play2d(). cocos2d bug?
}

void ClientDemo::goToMainMenu(cocos2d::Ref* pSender)
{
	_eventDispatcher->removeAllEventListeners();
	cocos2d::experimental::AudioEngine::stopAll();
	auto scene = MenuScene::createMenu();
	Director::getInstance()->replaceScene(scene);
}



ClientDemo::~ClientDemo()
{
	//below lines prevented win screen to play music, and commenting
	//them out doesn't cause the client to crash, so...
	//cocos2d::experimental::AudioEngine::stopAll();
	//cocos2d::experimental::AudioEngine::end();

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

void ClientDemo::initializeSound()
{
	if (gSound.audioOn)
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
		// soundIDList[12] = ptero_playerhit
		// soundIDList[13] = player_footsteps
		// soundIDList[14] = music
		// soundIDList[15] = sam_laugh

		if (gSound.sfxOn)
		{
			//initalize player sfx triggers to false
			//for (int i = 0; i < 3; i++)
			//{
			//	gSound.pTrigs[i].onBucket = false;
			//	gSound.pTrigs[i].onGrid = false;
			//	gSound.pTrigs[i].gotCandy = false;
			//	gSound.pTrigs[i].lostCandy = false;
			//}
			//gSound.levelChange = false;

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
			experimental::AudioEngine::preload("\\res\\sound\\sfx\\player_footsteps.mp3");
			experimental::AudioEngine::preload("\\res\\sound\\sfx\\sam_laugh.mp3");


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
			soundIDList.push_back(experimental::AudioEngine::play2d("\\res\\sound\\sfx\\player_footsteps.mp3", false, 0.0f));
			soundIDList.push_back(experimental::AudioEngine::play2d("\\res\\sound\\music\\samlvl_music.mp3", false, 0.5f)); //hackfix to get lvl 1 music to play
			soundIDList.push_back(experimental::AudioEngine::play2d("\\res\\sound\\sfx\\sam_laugh.mp3", false, 0.0f));

			for (unsigned int i = 0; i < soundIDList.size(); i++)
			{
				isSFXPlaying.push_back(false);
			}
		}

		if (gSound.musicOn)
		{
			//preload background music
			experimental::AudioEngine::preload("\\res\\sound\\music\\menu_music.mp3");
			experimental::AudioEngine::preload("\\res\\sound\\music\\samlvl_music.mp3");
			experimental::AudioEngine::preload("\\res\\sound\\music\\candylvl_music.mp3");
			experimental::AudioEngine::preload("\\res\\sound\\music\\ptlvl_music.mp3");
			experimental::AudioEngine::preload("\\res\\sound\\music\\sunlvl_music.mp3");
			experimental::AudioEngine::preload("\\res\\sound\\music\\win_music.mp3");
		}
	}
}

//check if a player is on a bucket and then highlight it
void ClientDemo::highlightBuckets(void)
{
	if (nullptr != bucketHighlight)
	{
		Point tileCoord = plyrCoordToTileCoord(playernum);

		if (tileCoord.x >= 0 && tileCoord.x <= levelmanager.levelmap->getMapSize().width && tileCoord.y >= 0 && tileCoord.y <= levelmanager.levelmap->getMapSize().height)
		{
			int bTile = bucketlayer->getTileGIDAt(tileCoord);

			if (bTile)
			{
				auto tilemapvals = levelmanager.levelmap->getPropertiesForGID(bTile).asValueMap();

				if (!tilemapvals.empty())
				{
					bool r = tilemapvals["Red"].asBool();
					bool b = tilemapvals["Blue"].asBool();
					bool y = tilemapvals["Yellow1"].asBool();
					bool o = tilemapvals["Orange"].asBool();
					bool blk = tilemapvals["Black"].asBool();

					bool b2 = tilemapvals["Blue2"].asBool();
					bool b3 = tilemapvals["Blue3"].asBool();
					bool g1 = tilemapvals["Green1"].asBool();
					bool g2 = tilemapvals["Green2"].asBool();
					bool g3 = tilemapvals["Green3"].asBool();

					bool w = tilemapvals["White"].asBool();
					bool gy1 = tilemapvals["Grey1"].asBool();
					bool gy2 = tilemapvals["Grey2"].asBool();
					bool r2 = tilemapvals["Red2"].asBool();
					bool p = tilemapvals["Purple1"].asBool();
					bool r1 = tilemapvals["Red1"].asBool();

					bool render = r || b || y || o || blk || b2 || b3 || g1 || g2 || g3 || w || gy1 || gy2 || r2 || p || r1;

					if (render) {
						Vec2 render_at = bucketlayer->getPositionAt(tileCoord);
						render_at.x += 12;
						render_at.y += 12;
						bucketHighlight->setPosition(render_at);
						bucketHighlight->setOpacity(150);
					}

				}
			}
			else
			{
				bucketHighlight->setOpacity(0);
			}
		}
	}
}

void ClientDemo::PauseGame(void)
{
	
	/*//check if single player or other players around
	int check = 0;
	for (unsigned int i = 0; i < players.size(); i++)
	{
		if (players[i]->isVisible())
		{
			check++;
		}
	}
	if (check < 2)
	{
		this->pauseSchedulerAndActions();
	}
	//this->setTouchEnabled(false);*/
	gameMenuLayer->setMusic(gSound.musicOn);
	gameMenuLayer->setSFX(gSound.sfxOn);
	if (gSound.musicOn)
	{
		experimental::AudioEngine::stop(soundIDList[14]);
		soundIDList[14] = experimental::AudioEngine::play2d("\\res\\sound\\music\\menu_music.mp3", true, gSound.mVolume);
	}
	gameMenuLayer->ShowGameMenu();
	experimental::AudioEngine::pauseAll();
	isPaused = true;
}


void ClientDemo::ResumeGame(void)
{
	/*//check if single player or other players around
	int check = 0;
	for (unsigned int i = 0; i < players.size(); i++)
	{
		if (players[i]->isVisible())
		{
			check++;
		}
	}
	if (check < 2)
	{
		this->resumeSchedulerAndActions();
	}
	//this->setTouchEnabled(true);
	*/
	gameMenuLayer->HideGameMenu();
	experimental::AudioEngine::resumeAll();
	isPaused = false;
	if (gSound.musicOn)
	{
		experimental::AudioEngine::stop(soundIDList[14]);

		if (levelmanager.currentlevel == 1)
		{
			soundIDList[14] = experimental::AudioEngine::play2d("\\res\\sound\\music\\samlvl_music.mp3", true, gSound.mVolume);
		}
		else if (levelmanager.currentlevel == 2)
		{
			soundIDList[14] = experimental::AudioEngine::play2d("\\res\\sound\\music\\candylvl_music.mp3", true, gSound.mVolume);
		}
		else if (levelmanager.currentlevel == 3)
		{
			soundIDList[14] = experimental::AudioEngine::play2d("\\res\\sound\\music\\ptlvl_music.mp3", true, gSound.mVolume);
		}
		else if (levelmanager.currentlevel == 4)
		{
			soundIDList[14] = experimental::AudioEngine::play2d("\\res\\sound\\music\\sunlvl_music.mp3", true, gSound.mVolume);
		}
	}
}

void ClientDemo::updateFromMenu(void)
{
	//check if player clicked resume game
	if (gameMenuLayer->checkResume())
	{
		gameMenuLayer->setResume(false);
		ResumeGame();
	}
	//check if player clicked exit game
	if (gameMenuLayer->checkExit())
	{
		Director::getInstance()->end();
		exit(0);
	}
	if (gameMenuLayer->checkVideo() != Director::getInstance()->getOpenGLView()->getFrameZoomFactor())
	{
		Director::getInstance()->getOpenGLView()->setFrameZoomFactor(gameMenuLayer->checkVideo());
		Camera::getDefaultCamera()->setPosition(players[playernum - 1]->getPosition()); //prevents slow re-positioning of gamemenu+camera
	}
	//set menu pos to center around camera pos
	gameMenuLayer->SetMenuCamera(Vec2(Camera::getDefaultCamera()->getPositionX(), Camera::getDefaultCamera()->getPositionY() + 25));

	//check if player turned music on in game menu
	if (gameMenuLayer->isMusicOn() && gSound.musicOn == false)
	{
		gSound.musicOn = true;
		gSound.mVolume = gSound.oldMVol;
		soundIDList[14] = experimental::AudioEngine::play2d("\\res\\sound\\music\\menu_music.mp3", true, gSound.mVolume);
	}
	//check if player turned music off in game menu
	else if (gameMenuLayer->isMusicOn() == false && gSound.musicOn == true)
	{
		gSound.musicOn = false;
		gSound.oldMVol = gSound.mVolume;
		gSound.mVolume = 0.0f;
		experimental::AudioEngine::stop(soundIDList[14]);
	}
	//check if player turned sfx on in game menu
	if (gameMenuLayer->isSFXOn() && gSound.sfxOn == false)
	{
		gSound.sfxOn = true;
		//hack fix for now, need to deal with looped sfx properly in processSound()
		if (levelmanager.currentlevel > 3)
		{
			soundIDList[5] = experimental::AudioEngine::play2d("\\res\\sound\\sfx\\ptero_swoop.mp3", true, 0.1f);
			isSFXPlaying[5] = true;
		}
	}
	//check if player turned sfx off in game menu
	else if (gameMenuLayer->isSFXOn() == false && gSound.sfxOn == true)
	{
		gSound.sfxOn = false;
		experimental::AudioEngine::stop(soundIDList[5]);
		experimental::AudioEngine::stop(soundIDList[11]);
	}
}

void ClientDemo::runEvents()
{
	if (eventActive == 1) //sam painting event
	{
		if (pEvent.canvasFade == true) //if phase 2 started
		{
			if (pEvent.init == false) //if phase 2 has not been initialized yet (getting blank canvas sprites)
			{
				if (levelmanager.currentlevel == 2)
				{
					pEvent.tileSprites.push_back(blankCanvas->getTileAt(Vec2(9, 0)));
					pEvent.tileSprites.push_back(blankCanvas->getTileAt(Vec2(9, 1)));
					pEvent.tileSprites.push_back(blankCanvas->getTileAt(Vec2(9, 2)));
					pEvent.tileSprites.push_back(blankCanvas->getTileAt(Vec2(10, 0)));
					pEvent.tileSprites.push_back(blankCanvas->getTileAt(Vec2(10, 1)));
					pEvent.tileSprites.push_back(blankCanvas->getTileAt(Vec2(10, 2)));
				}
				else if (levelmanager.currentlevel == 3)
				{
					//top painting
					pEvent.tileSprites.push_back(blankCanvas->getTileAt(Vec2(11, 0)));
					pEvent.tileSprites.push_back(blankCanvas->getTileAt(Vec2(11, 1)));
					pEvent.tileSprites.push_back(blankCanvas->getTileAt(Vec2(11, 2)));
					pEvent.tileSprites.push_back(blankCanvas->getTileAt(Vec2(12, 0)));
					pEvent.tileSprites.push_back(blankCanvas->getTileAt(Vec2(12, 1)));
					pEvent.tileSprites.push_back(blankCanvas->getTileAt(Vec2(12, 2)));
					pEvent.tileSprites.push_back(blankCanvas->getTileAt(Vec2(13, 0)));
					pEvent.tileSprites.push_back(blankCanvas->getTileAt(Vec2(13, 1)));
					pEvent.tileSprites.push_back(blankCanvas->getTileAt(Vec2(13, 2)));

					//left painting
					pEvent.tileSprites.push_back(blankCanvas->getTileAt(Vec2(1, 7)));
					pEvent.tileSprites.push_back(blankCanvas->getTileAt(Vec2(1, 8)));
					pEvent.tileSprites.push_back(blankCanvas->getTileAt(Vec2(1, 9)));
					pEvent.tileSprites.push_back(blankCanvas->getTileAt(Vec2(2, 7)));
					pEvent.tileSprites.push_back(blankCanvas->getTileAt(Vec2(2, 8)));
					pEvent.tileSprites.push_back(blankCanvas->getTileAt(Vec2(2, 9)));
					pEvent.tileSprites.push_back(blankCanvas->getTileAt(Vec2(3, 7)));
					pEvent.tileSprites.push_back(blankCanvas->getTileAt(Vec2(3, 8)));
					pEvent.tileSprites.push_back(blankCanvas->getTileAt(Vec2(3, 9)));

					//right painting
					pEvent.tileSprites.push_back(blankCanvas->getTileAt(Vec2(21, 7)));
					pEvent.tileSprites.push_back(blankCanvas->getTileAt(Vec2(21, 8)));
					pEvent.tileSprites.push_back(blankCanvas->getTileAt(Vec2(21, 9)));
					pEvent.tileSprites.push_back(blankCanvas->getTileAt(Vec2(22, 7)));
					pEvent.tileSprites.push_back(blankCanvas->getTileAt(Vec2(22, 8)));
					pEvent.tileSprites.push_back(blankCanvas->getTileAt(Vec2(22, 9)));
					pEvent.tileSprites.push_back(blankCanvas->getTileAt(Vec2(23, 7)));
					pEvent.tileSprites.push_back(blankCanvas->getTileAt(Vec2(23, 8)));
					pEvent.tileSprites.push_back(blankCanvas->getTileAt(Vec2(23, 9)));
				}
				else if (levelmanager.currentlevel == 4)
				{
					//top painting
					pEvent.tileSprites.push_back(blankCanvas->getTileAt(Vec2(14, 0)));
					pEvent.tileSprites.push_back(blankCanvas->getTileAt(Vec2(14, 1)));
					pEvent.tileSprites.push_back(blankCanvas->getTileAt(Vec2(14, 2)));
					pEvent.tileSprites.push_back(blankCanvas->getTileAt(Vec2(15, 0)));
					pEvent.tileSprites.push_back(blankCanvas->getTileAt(Vec2(15, 1)));
					pEvent.tileSprites.push_back(blankCanvas->getTileAt(Vec2(15, 2)));
					pEvent.tileSprites.push_back(blankCanvas->getTileAt(Vec2(16, 0)));
					pEvent.tileSprites.push_back(blankCanvas->getTileAt(Vec2(16, 1)));
					pEvent.tileSprites.push_back(blankCanvas->getTileAt(Vec2(16, 2)));

					//left painting
					pEvent.tileSprites.push_back(blankCanvas->getTileAt(Vec2(3, 8)));
					pEvent.tileSprites.push_back(blankCanvas->getTileAt(Vec2(3, 9)));
					pEvent.tileSprites.push_back(blankCanvas->getTileAt(Vec2(3, 10)));
					pEvent.tileSprites.push_back(blankCanvas->getTileAt(Vec2(4, 8)));
					pEvent.tileSprites.push_back(blankCanvas->getTileAt(Vec2(4, 9)));
					pEvent.tileSprites.push_back(blankCanvas->getTileAt(Vec2(4, 10)));
					pEvent.tileSprites.push_back(blankCanvas->getTileAt(Vec2(5, 8)));
					pEvent.tileSprites.push_back(blankCanvas->getTileAt(Vec2(5, 9)));
					pEvent.tileSprites.push_back(blankCanvas->getTileAt(Vec2(5, 10)));

					//right painting
					pEvent.tileSprites.push_back(blankCanvas->getTileAt(Vec2(25, 8)));
					pEvent.tileSprites.push_back(blankCanvas->getTileAt(Vec2(25, 9)));
					pEvent.tileSprites.push_back(blankCanvas->getTileAt(Vec2(25, 10)));
					pEvent.tileSprites.push_back(blankCanvas->getTileAt(Vec2(26, 8)));
					pEvent.tileSprites.push_back(blankCanvas->getTileAt(Vec2(26, 9)));
					pEvent.tileSprites.push_back(blankCanvas->getTileAt(Vec2(26, 10)));
					pEvent.tileSprites.push_back(blankCanvas->getTileAt(Vec2(27, 8)));
					pEvent.tileSprites.push_back(blankCanvas->getTileAt(Vec2(27, 9)));
					pEvent.tileSprites.push_back(blankCanvas->getTileAt(Vec2(27, 10)));

					//bottom painting
					pEvent.tileSprites.push_back(blankCanvas->getTileAt(Vec2(14, 18)));
					pEvent.tileSprites.push_back(blankCanvas->getTileAt(Vec2(14, 19)));
					pEvent.tileSprites.push_back(blankCanvas->getTileAt(Vec2(14, 20)));
					pEvent.tileSprites.push_back(blankCanvas->getTileAt(Vec2(15, 18)));
					pEvent.tileSprites.push_back(blankCanvas->getTileAt(Vec2(15, 19)));
					pEvent.tileSprites.push_back(blankCanvas->getTileAt(Vec2(15, 20)));
					pEvent.tileSprites.push_back(blankCanvas->getTileAt(Vec2(16, 18)));
					pEvent.tileSprites.push_back(blankCanvas->getTileAt(Vec2(16, 19)));
					pEvent.tileSprites.push_back(blankCanvas->getTileAt(Vec2(16, 20)));
				}
				opacity = 252;
				pEvent.init = true;
			}
			//gradually make blank canvases fade
			if (pEvent.tileSprites[0]->getDisplayedOpacity() > 0)
			{
				for (unsigned int i = 0; i < pEvent.tileSprites.size(); i++)
				{
					//pEvent.tileSprites[i]->setOpacity(pEvent.tileSprites[i]->getOpacity() - 5); <-- makes blank canvas layer blink
					pEvent.tileSprites[i]->setOpacity(opacity);
				}
				opacity -= 4;
			}
			else
			{
				pEvent.tileSprites.clear();
				pEvent.canvasFade = false;
				pEvent.init = false;
			}
		}
	}
	if (eventActive == 2) //end of level victory freeze
	{
		//play victory music until level completed screen comes
		//experimental::AudioEngine::stop(soundIDList[14]);
		//soundIDList[14] = experimental::AudioEngine::play2d("res\\sound\\music\\victory.mp3", false, 0.5f);
	}
}

void ClientDemo::playSound(int id, std::string& filePath)
{
	if (gSound.audioOn && gSound.sfxOn && isSFXPlaying[id] == false)
	{
		soundIDList[id] = experimental::AudioEngine::play2d(filePath);
		isSFXPlaying[id] = true;
		experimental::AudioEngine::setFinishCallback(soundIDList[id], [&](int id, const std::string& filePath)
		{
			isSFXPlaying[id] = false;
		});
	}
}