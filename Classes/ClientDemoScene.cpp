#include "ClientDemoScene.h"

USING_NS_CC;
//using boost::asio::ip::udp;
using boost::asio::ip::tcp;


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



	std::string file = "res//maps//happy_sun_paint.tmx";
	auto str = String::createWithContentsOfFile(FileUtils::getInstance()->fullPathForFilename(file.c_str()).c_str());
	tileMap = cocos2d::CCTMXTiledMap::createWithXML(str->getCString(), "");

	addChild(tileMap, -1000);

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// NEW CODE HERE
	// Load the paint bucket layer
	bucketlayer = tileMap->getLayer("Paintbuckets");
	blockage = tileMap->getLayer("Collision");
	blockage->setVisible(false);

	// Check to see if there is an object layer 
	spawnObjs = tileMap->objectGroupNamed("SpawnObjects");

	if (spawnObjs == NULL) {
		CCLOG("TMX map has no Red Bucket object layer");
	}

	// Player one spawn position coordinates 
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
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	player1 = Player::create(1);
	player1->setPlayernum(1);
	player1->getTexture()->setAliasTexParameters();
	player1->setAnchorPoint(Vec2(0.5, 0.0));
	//player1->setPosition(Vec2(100, 100));
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////// NEW CODE ADDED
	player1->setPosition(Vec2(p1X, p1Y));
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	addChild(player1, 0);

	player2 = Player::create(2);
	player2->setPlayernum(2);
	player2->getTexture()->setAliasTexParameters();
	player2->setAnchorPoint(Vec2(0.5, 0.0));
	//player2->setPosition(Vec2(200, 200));
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////// NEW CODE ADDED
	player2->setPosition(Vec2(p2X, p2Y));
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	addChild(player2, 0);

	player3 = Player::create(3);
	player3->setPlayernum(3);
	player3->getTexture()->setAliasTexParameters();
	player3->setAnchorPoint(Vec2(0.5, 0.0));
	//player3->setPosition(Vec2(300, 300));
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////// NEW CODE ADDED
	player3->setPosition(Vec2(p3X, p3Y));
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	addChild(player3, 0);

	player4 = Player::create(4);
	player4->setPlayernum(4);
	player4->getTexture()->setAliasTexParameters();
	player4->setAnchorPoint(Vec2(0.5, 0.0));
	//player4->setPosition(Vec2(400, 400));
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////// NEW CODE ADDED
	player4->setPosition(Vec2(p4X, p4Y));
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	addChild(player4, 0);

	players.push_back(player1);
	players.push_back(player2);
	players.push_back(player3);
	players.push_back(player4);

	villain = Villain::create();
	villain->getTexture()->setAliasTexParameters();
	villain->setAnchorPoint(Vec2(0.5, 0.0));
	villain->setPosition(Vec2(250, 150));
	addChild(villain, 0);

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// NEW ADDED CODE
	// Player Label Creation
	p1CLabel = CCLabelTTF::create("p1", "fonts/Marker Felt.ttf", 20);
	p1CLabel->setPosition(Vec2(p1X, p1Y + 46));
	p1CLabel->setAnchorPoint(Vec2(0.5, 0.0));
	addChild(p1CLabel, 100);

	p2CLabel = CCLabelTTF::create("p2", "fonts/Marker Felt.ttf", 20);
	p2CLabel->setPosition(Vec2(p2X, p2Y + 46));
	p2CLabel->setAnchorPoint(Vec2(0.5, 0.0));
	addChild(p2CLabel, 100);

	p3CLabel = CCLabelTTF::create("p3", "fonts/Marker Felt.ttf", 20);
	p3CLabel->setPosition(Vec2(p3X, p3Y + 46));
	p3CLabel->setAnchorPoint(Vec2(0.5, 0.0));
	addChild(p3CLabel, 100);

	p4CLabel = CCLabelTTF::create("p4", "fonts/Marker Felt.ttf", 20);
	p4CLabel->setPosition(Vec2(p4X, p4Y + 46));
	p4CLabel->setAnchorPoint(Vec2(0.5, 0.0));
	addChild(p4CLabel, 100);
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	Sprite* wallpainting = Sprite::create("res/sprites/objects/tiny_sun_framed.png");
	wallpainting->getTexture()->setAliasTexParameters();
	wallpainting->setPosition(Vec2(320, 320));
	wallpainting->setScale(1.5);
	addChild(wallpainting, -999);

	for (int i = 0; i <= 5; i++)
	{
		for (int j = 0; j <= 5; j++)
		{
			tileptrarray[i][j] = PaintTile::create();
			tileptrarray[i][j]->setPosition(24 * i + 264, 24 * j + 90);
			tileptrarray[i][j]->setScale(1);
			//tileptrarray[i][j]->debugDraw(true);
			addChild(tileptrarray[i][j], -999);
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
	}

	for (Player* p : players)
	{
		p->setZOrder(-p->getPositionY());
	}
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
	std::string playerstring = "p";
	playerstring += std::to_string(playernum).c_str();
	switch (keyCode) {
	case EventKeyboard::KeyCode::KEY_UP_ARROW:
		
		//players[playernum - 1]->stopAllActions();
		//players[playernum - 1]->runAction(RepeatForever::create(animationmanager.animationmap.at(playerstring+"up")));
		//players[playernum - 1]->setAnim(playerstring + "up");
		ymove += 2;
		break;

	case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
		//players[playernum - 1]->stopAllActions();
		//players[playernum - 1]->runAction(RepeatForever::create(animationmanager.animationmap.at(playerstring+"down")));
		//players[playernum - 1]->setAnim(playerstring + "down");
		ymove -= 2;
		
		break;
	case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
		//players[playernum - 1]->stopAllActions();
		//players[playernum - 1]->runAction(RepeatForever::create(animationmanager.animationmap.at(playerstring + "left")));
		//players[playernum - 1]->setAnim(playerstring + "left");
		xmove -= 2;
		break;
	case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
		//players[playernum - 1]->stopAllActions();
		//players[playernum - 1]->runAction(RepeatForever::create(animationmanager.animationmap.at(playerstring + "right")));
		//players[playernum - 1]->setAnim(playerstring + "right");
		xmove += 2;
		break;
	case EventKeyboard::KeyCode::KEY_SPACE:
		//players[playernum - 1]->stopAllActions();
		//players[playernum - 1]->runAction(RepeatForever::create(animationmanager.animationmap.at(playerstring + "paint")));
		//players[playernum - 1]->setAnim(playerstring + "paint");
		button1 = true;
		xmove = 0;
		ymove = 0;
		///////////////////////////////////////////////////////////////////////////////////////////////////////////// NEW CODE ADDED
		space();
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		break;
	}
	event->stopPropagation();
}

void ClientDemo::KeyRelease(EventKeyboard::KeyCode keyCode, Event* event)
{

	switch (keyCode) {
	case EventKeyboard::KeyCode::KEY_UP_ARROW:
		//	player1->stopAllActions();
		ymove = 0;
		break;
	case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
		//player1->stopAllActions();
		ymove = 0;
		break;
	case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
		//player1->stopAllActions();
		xmove = 0;
		break;
	case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
		//player1->stopAllActions();
		xmove = 0;
		break;
	case EventKeyboard::KeyCode::KEY_SPACE:
		//player1->stopAllActions();
		button1 = false;
		break;
	}
	event->stopPropagation();

}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// NEW CODE ADDED
// This will convert the players coordinates into tile coordinates
CCPoint ClientDemo::plyrCoordToTileCoord(int playerNum)
{
		int newx = players[playerNum -1]->getPositionX() / (tileMap->getTileSize().width + xmove);
		int newy = (360 - players[playerNum - 1]->getPositionY()) / (tileMap->getTileSize().height + ymove);
		return(CCPoint(newx, newy));
}
	



int ClientDemo::getTileProperties(CCPoint tileCoord)
{
	if (tileCoord.x >= 0 && tileCoord.x <= 25 && tileCoord.y >= 0 && tileCoord.y <= 14)
	{
		return (bucketlayer->getTileGIDAt(tileCoord));
	}
}



void ClientDemo::changeLabelColor(int bTile, int playerNum)
{
	if (playerNum == 1) {
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
					//p1CLabel->setString("Red");
					p1CLabel->setFontFillColor(ccc3(247, 52, 47));
				}
				if ("true" == b)
				{
					//p1CLabel->setString("Blue");
					p1CLabel->setFontFillColor(ccc3(49, 58, 197));
				}
				if ("true" == y) {
					//p1CLabel->setString("Yellow");
					p1CLabel->setFontFillColor(ccc3(222, 244, 69));
				}
				if ("true" == o) {
					//p1CLabel->setString("Orange");
					p1CLabel->setFontFillColor(ccc3(234, 152, 46));
				}
			}
		}
	}
	else if (playerNum == 2) {
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
					p2CLabel->setFontFillColor(ccc3(247, 52, 47));
				}
				if ("true" == b)
				{
					p2CLabel->setFontFillColor(ccc3(49, 58, 197));
				}
				if ("true" == y) {
					p2CLabel->setFontFillColor(ccc3(222, 244, 69));
				}
				if ("true" == o) {
					p2CLabel->setFontFillColor(ccc3(234, 152, 46));
				}
			}
		}
	}
	else if (playerNum == 3) {
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
					p3CLabel->setFontFillColor(ccc3(247, 52, 47));
				}
				if ("true" == b)
				{
					p3CLabel->setFontFillColor(ccc3(49, 58, 197));
				}
				if ("true" == y) {
					p3CLabel->setFontFillColor(ccc3(222, 244, 69));
				}
				if ("true" == o) {
					p3CLabel->setFontFillColor(ccc3(234, 152, 46));
				}
			}
		}

	}
	else if (playerNum == 4) {
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
					p4CLabel->setFontFillColor(ccc3(247, 52, 47));
				}
				if ("true" == b)
				{
					p4CLabel->setFontFillColor(ccc3(49, 58, 197));
				}
				if ("true" == y) {
					p4CLabel->setFontFillColor(ccc3(222, 244, 69));
				}
				if ("true" == o) {
					p4CLabel->setFontFillColor(ccc3(234, 152, 46));
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

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


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
	

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// NEW ADDED CODE
	p1CLabel->setPosition(Vec2(p.p1x, p.p1y + 46));
	p2CLabel->setPosition(Vec2(p.p2x, p.p2y + 46));
	p3CLabel->setPosition(Vec2(p.p3x, p.p3y + 46));
	p4CLabel->setPosition(Vec2(p.p4x, p.p4y + 46));
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	player1->setPosition(Vec2(p.p1x, p.p1y));
	player2->setPosition(Vec2(p.p2x, p.p2y));
	player3->setPosition(Vec2(p.p3x, p.p3y));
	player4->setPosition(Vec2(p.p4x, p.p4y));
	villain->setPosition(Vec2(p.vx, p.vy));
	//tilevalues = p.tilevalues;
	//player1 animations

	//////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////
	if (player1->getAnim() != p.p1anim && p.p1anim !="") {
		player1->stopAllActions();
		player1->runAction(RepeatForever::create(animationmanager.animationmap.at(p.p1anim)));
		player1->setAnim(p.p1anim);
	}
	if (player2->getAnim() != p.p2anim && p.p2anim != "") {
		player2->stopAllActions();
		player2->runAction(RepeatForever::create(animationmanager.animationmap.at(p.p2anim)));
		player2->setAnim(p.p2anim);
	}
	if (player3->getAnim() != p.p3anim && p.p3anim != "") {
		player3->stopAllActions();
		player3->runAction(RepeatForever::create(animationmanager.animationmap.at(p.p3anim)));
		player3->setAnim(p.p3anim);
	}
	if (player4->getAnim() != p.p4anim && p.p4anim != "") {
		player4->stopAllActions();
		player4->runAction(RepeatForever::create(animationmanager.animationmap.at(p.p4anim)));
		player4->setAnim(p.p4anim);
	}
	if (villain->getAnim() != p.vanim && p.vanim != "") {
		villain->stopAllActions();
		villain->runAction(RepeatForever::create(animationmanager.animationmap.at(p.vanim)));
		villain->setAnim(p.vanim);
	}


	for (int i = 0; i <= 5; i++)
	{
		for (int j = 0; j <= 5; j++)
		{
			if (tilevalues[i][j] != p.tilevalues[i][j])
			{
				tilevalues[i][j] = p.tilevalues[i][j];
				if (tilevalues[i][j] == 2)
				{
					tileptrarray[i][j]->setColor("red");
					tileptrarray[i][j]->refreshColor();
				}
				if (tilevalues[i][j] == 3)
				{
					tileptrarray[i][j]->setColor("blue");
					tileptrarray[i][j]->refreshColor();
					CCLOG(std::to_string(tilevalues[0][0]).c_str());
					CCLOG(std::to_string(p.tilevalues[0][0]).c_str());
				}
				if (tilevalues[i][j] == 4)
				{
					tileptrarray[i][j]->setColor("yellow");
					tileptrarray[i][j]->refreshColor();
				}
				if (tilevalues[i][j] == 5)
				{
					tileptrarray[i][j]->setColor("orange");
					tileptrarray[i][j]->refreshColor();
				}
				if (tilevalues[i][j] == 6)
				{
					tileptrarray[i][j]->setColor("black");
					tileptrarray[i][j]->refreshColor();
				}
			}
		}
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