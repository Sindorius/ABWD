 #include "ServerConnection.h"

std::string IPAddress = "";

Scene* ServerConnection::createServerConnection()
{
	IPAddress = "127.0.0.1";
	auto SCScene = Scene::create();
	auto SClayer = ServerConnection::create();

	SCScene->addChild(SClayer);

	return SCScene;
}

Scene* ServerConnection::createServerConnection(std::string ipa)
{
	IPAddress = ipa;
	auto SCScene = Scene::create();
	auto SClayer = ServerConnection::create();

	SCScene->addChild(SClayer);

	return SCScene;
}

bool ServerConnection::init()
{
	if (!Layer::init())
	{
		return false;
	}

	float winSizeWidth = CCDirector::sharedDirector()->getWinSize().width / 2;
	float winSizeHeight = CCDirector::sharedDirector()->getWinSize().height / 2;

	auto enter_button = MenuItemImage::create("res//sprites//ui//EnterNP.png", "res//sprites//ui//EnterP.png", CC_CALLBACK_1(ServerConnection::beginGame, this));
	enter_button->setPosition(Vec2(winSizeWidth, winSizeHeight-120));
	enter_button->setScale(0.5f);

	auto p1_button = MenuItemImage::create("res//sprites//ui//p1NP.png", "res//sprites//ui//p1P.png", CC_CALLBACK_1(ServerConnection::player1, this));
	p1_button->setPosition(Vec2((int)winSizeWidth - 210, (int)winSizeHeight - 20));
	p1_button->setScale(0.3f);

	auto p2_button = MenuItemImage::create("res//sprites//ui//p2NP.png", "res//sprites//ui//p2P.png", CC_CALLBACK_1(ServerConnection::player2, this));
	p2_button->setPosition(Vec2((int)winSizeWidth - 90, (int)winSizeHeight - 20));
	p2_button->setScale(0.3f);

	auto p3_button = MenuItemImage::create("res//sprites//ui//p3NP.png", "res//sprites//ui//p3P.png", CC_CALLBACK_1(ServerConnection::player3, this));
	p3_button->setPosition(Vec2((int)winSizeWidth + 80, (int)winSizeHeight - 20));
	p3_button->setScale(0.3f);

	auto p4_button = MenuItemImage::create("res//sprites//ui//p4NP.png", "res//sprites//ui//p4P.png", CC_CALLBACK_1(ServerConnection::player4, this));
	p4_button->setPosition(Vec2((int)winSizeWidth + 200, (int)winSizeHeight - 20));
	p4_button->setScale(0.3f);

	auto layer = Menu::create(enter_button, p1_button, p2_button, p3_button, p4_button, NULL);
	layer->setPosition(Point::ZERO);
	this->addChild(layer, 1);

	std::string file = "res//maps//server_connection.tmx";
	auto str = String::createWithContentsOfFile(FileUtils::getInstance()->fullPathForFilename(file.c_str()).c_str());
	serverScreen = cocos2d::TMXTiledMap::createWithXML(str->getCString(), "");
	this->addChild(serverScreen, 0);

	Directions = Sprite::create("res//sprites//ui//choosePlayerDirections.png");
	Directions->setScale(0.25f);
	Directions->setPosition(Vec2((int)winSizeWidth - 10, (int)winSizeHeight + 120));
	this->addChild(Directions, 0);

	p1 = Sprite::create("res//sprites//ui//p1Label.png");
	p1->setScale(0.4f);
	p1->setPosition(Vec2((int)winSizeWidth - 210, (int)winSizeHeight - 95));
	this->addChild(p1, 0);

	p1Chara = Sprite::create("res//sprites//ui//p1P.png");
	p1Chara->setScale(0.3f);
	p1Chara->setPosition(Vec2((int)winSizeWidth - 210, (int)winSizeHeight - 20));
	p1Chara->setOpacity(0);
	this->addChild(p1Chara, 1);

	p2 = Sprite::create("res//sprites//ui//p2Label.png");
	p2->setScale(0.4f);
	p2->setPosition(Vec2((int)winSizeWidth - 90, (int)winSizeHeight - 95));
	this->addChild(p2, 0);

	p2Chara = Sprite::create("res//sprites//ui//p2P.png");
	p2Chara->setScale(0.3f);
	p2Chara->setPosition(Vec2((int)winSizeWidth - 90, (int)winSizeHeight - 20));
	p2Chara->setOpacity(0);
	this->addChild(p2Chara, 1);

	p3 = Sprite::create("res//sprites//ui//p3Label.png");
	p3->setScale(0.4f);
	p3->setPosition(Vec2((int)winSizeWidth + 80, (int)winSizeHeight - 95));
	this->addChild(p3, 0);

	p3Chara = Sprite::create("res//sprites//ui//p3P.png");
	p3Chara->setScale(0.3f);
	p3Chara->setPosition(Vec2((int)winSizeWidth + 80, (int)winSizeHeight - 20));
	p3Chara->setOpacity(0);
	this->addChild(p3Chara, 1);

	p4 = Sprite::create("res//sprites//ui//p4Label.png");
	p4->setScale(0.4f);
	p4->setPosition(Vec2((int)winSizeWidth + 200, (int)winSizeHeight - 95));
	this->addChild(p4, 0);

	p4Chara = Sprite::create("res//sprites//ui//p4P.png");
	p4Chara->setScale(0.3f);
	p4Chara->setPosition(Vec2((int)winSizeWidth + 200, (int)winSizeHeight - 20));
	p4Chara->setOpacity(0);
	this->addChild(p4Chara, 1);

	return true;
}


void ServerConnection::beginGame(cocos2d::Ref* pSender)
{
	if (aPlayerChosen == true)
	{
		auto scene = HowToPlay::createHowToPlay(IPAddress, playerNum); 
		CCDirector::getInstance()->replaceScene(scene);
	}
}

void ServerConnection::player1(cocos2d::Ref* sSender)
{
	if (aPlayerChosen == false) 
	{
		p1Chara->setOpacity(255);
		aPlayerChosen = true;
		playerNum = 1;
	}
}

void ServerConnection::player2(cocos2d::Ref* sSender)
{
	if(aPlayerChosen == false)
	{
		p2Chara->setOpacity(255);
		aPlayerChosen = true;
		playerNum = 2;
	}
}

void ServerConnection::player3(cocos2d::Ref* sSender)
{
	if (aPlayerChosen == false)
	{
		p3Chara->setOpacity(255);
		aPlayerChosen = true;
		playerNum = 3;
	}
}

void ServerConnection::player4(cocos2d::Ref* sSender)
{
	if (aPlayerChosen == false) 
	{
		p4Chara->setOpacity(255);
		aPlayerChosen = true;
		playerNum = 4;
	}
}

void ServerConnection::menuCloseCallback(Ref* pSender)
{
	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}

