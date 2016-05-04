 #include "ServerConnection.h"

std::string IPAddress = "";
char pickedchars = 0;

Scene* ServerConnection::createServerConnection(char chosencharacters)
{
	IPAddress = "127.0.0.1";
	pickedchars = chosencharacters;
	auto SCScene = Scene::create();
	auto SClayer = ServerConnection::create();

	SCScene->addChild(SClayer);

	return SCScene;
}

Scene* ServerConnection::createServerConnection(std::string ipa, char chosencharacters)
{
	IPAddress = ipa;
	pickedchars = chosencharacters;
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

	joyListener = EventListenerJoystick::create();
	joyListener->onEvent = CC_CALLBACK_1(ServerConnection::Joystick, this);
	_eventDispatcher->addEventListenerWithFixedPriority(joyListener, 1);

	keyListener = EventListenerKeyboard::create();
	keyListener->onKeyPressed = CC_CALLBACK_2(ServerConnection::KeyDown, this);
	_eventDispatcher->addEventListenerWithFixedPriority(keyListener, 2);

	char p1mask = 1;
	char p2mask = 2;
	char p3mask = 4;
	char p4mask = 8;
	char p1there = p1mask & pickedchars;
	char p2there = p2mask & pickedchars;
	char p3there = p3mask & pickedchars;
	char p4there = p4mask & pickedchars;

	
	float winSizeWidth = CCDirector::sharedDirector()->getWinSize().width / 2;
	float winSizeHeight = CCDirector::sharedDirector()->getWinSize().height / 2;

	enter_button = MenuItemImage::create("res//sprites//ui//EnterNP.png", "res//sprites//ui//EnterP.png", CC_CALLBACK_1(ServerConnection::beginGame, this));
	enter_button->setPosition(Vec2(winSizeWidth, winSizeHeight-120));
	enter_button->setScale(0.5f);

	auto p1_button = MenuItemImage::create("res//sprites//ui//p1NP.png", "res//sprites//ui//p1P.png", CC_CALLBACK_1(ServerConnection::player1, this));
	p1_button->setPosition(Vec2((int)winSizeWidth - 210, (int)winSizeHeight - 20));
	p1_button->setScale(0.3f);

	//these button2s are so players can select the labels too.
	//selected image is the same as normal image for now, need selected version
	auto p1_button2 = MenuItemImage::create("res//sprites//ui//p1Label.png", "res//sprites//ui//p1Label.png", CC_CALLBACK_1(ServerConnection::player1, this));
	p1_button2->setPosition(Vec2((int)winSizeWidth - 210, (int)winSizeHeight - 95));
	p1_button2->setScale(0.4f);

	auto p2_button = MenuItemImage::create("res//sprites//ui//p2NP.png", "res//sprites//ui//p2P.png", CC_CALLBACK_1(ServerConnection::player2, this));
	p2_button->setPosition(Vec2((int)winSizeWidth - 90, (int)winSizeHeight - 20));
	p2_button->setScale(0.3f);

	auto p2_button2 = MenuItemImage::create("res//sprites//ui//p2Label.png", "res//sprites//ui//p2Label.png", CC_CALLBACK_1(ServerConnection::player2, this));
	p2_button2->setPosition(Vec2((int)winSizeWidth - 90, (int)winSizeHeight - 95));
	p2_button2->setScale(0.4f);

	auto p3_button = MenuItemImage::create("res//sprites//ui//p3NP.png", "res//sprites//ui//p3P.png", CC_CALLBACK_1(ServerConnection::player3, this));
	p3_button->setPosition(Vec2((int)winSizeWidth + 80, (int)winSizeHeight - 20));
	p3_button->setScale(0.3f);

	auto p3_button2 = MenuItemImage::create("res//sprites//ui//p3Label.png", "res//sprites//ui//p3Label.png", CC_CALLBACK_1(ServerConnection::player3, this));
	p3_button2->setPosition(Vec2((int)winSizeWidth + 80, (int)winSizeHeight - 95));
	p3_button2->setScale(0.4f);

	auto p4_button = MenuItemImage::create("res//sprites//ui//p4NP.png", "res//sprites//ui//p4P.png", CC_CALLBACK_1(ServerConnection::player4, this));
	p4_button->setPosition(Vec2((int)winSizeWidth + 200, (int)winSizeHeight - 20));
	p4_button->setScale(0.3f);

	auto p4_button2 = MenuItemImage::create("res//sprites//ui//p4Label.png", "res//sprites//ui//p4Label.png", CC_CALLBACK_1(ServerConnection::player4, this));
	p4_button2->setPosition(Vec2((int)winSizeWidth + 200, (int)winSizeHeight - 95));
	p4_button2->setScale(0.4f);

	auto layer = Menu::create(enter_button, p1_button, p1_button2, p2_button, p2_button2, p3_button, p3_button2, p4_button, p4_button2, NULL);
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

	p1Chara = Sprite::create("res//sprites//ui//p1P.png");
	p1Chara->setScale(0.3f);
	p1Chara->setPosition(Vec2((int)winSizeWidth - 210, (int)winSizeHeight - 20));
	p1Chara->setOpacity(0);
	this->addChild(p1Chara, 1);

	p2Chara = Sprite::create("res//sprites//ui//p2P.png");
	p2Chara->setScale(0.3f);
	p2Chara->setPosition(Vec2((int)winSizeWidth - 90, (int)winSizeHeight - 20));
	p2Chara->setOpacity(0);
	this->addChild(p2Chara, 1);

	p3Chara = Sprite::create("res//sprites//ui//p3P.png");
	p3Chara->setScale(0.3f);
	p3Chara->setPosition(Vec2((int)winSizeWidth + 80, (int)winSizeHeight - 20));
	p3Chara->setOpacity(0);
	this->addChild(p3Chara, 1);

	p4Chara = Sprite::create("res//sprites//ui//p4P.png");
	p4Chara->setScale(0.3f);
	p4Chara->setPosition(Vec2((int)winSizeWidth + 200, (int)winSizeHeight - 20));
	p4Chara->setOpacity(0);
	this->addChild(p4Chara, 1);

	if (p1there == p1mask)
	{
		p1_button->setOpacity(20);
	}
	if (p2there == p2mask)
	{
		p2_button->setOpacity(20);
	}
	if (p3there == p3mask)
	{
		p3_button->setOpacity(20);
	}
	if (p4there == p4mask)
	{
		p4_button->setOpacity(20);
	}

	return true;
}


void ServerConnection::beginGame(cocos2d::Ref* pSender)
{
	if (aPlayerChosen == true)
	{
		_eventDispatcher->removeEventListener(joyListener);
		//joyListener->release();
		//joyListener = nullptr;

		_eventDispatcher->removeEventListener(keyListener);
		//keyListener->release();
		//keyListener = nullptr;

		auto scene = HowToPlay::createHowToPlay(IPAddress, playerNum); 
		CCDirector::getInstance()->replaceScene(TransitionFade::create(0.5f, scene));
	}
}

void ServerConnection::player1(cocos2d::Ref* sSender)
{
	//this if block deals with de-selecting previously 
	//selected player
	if (aPlayerChosen == true)
	{
		if (playerNum == 2)
		{
			p2Chara->setOpacity(0);
		}
		else if (playerNum == 3)
		{
			p3Chara->setOpacity(0);
		}
		else if (playerNum == 4)
		{
			p4Chara->setOpacity(0);
		}
	}
	p1Chara->setOpacity(255);
	aPlayerChosen = true;
	playerNum = 1;
}

void ServerConnection::player2(cocos2d::Ref* sSender)
{
	if (aPlayerChosen == true)
	{
		if (playerNum == 1)
		{
			p1Chara->setOpacity(0);
		}
		else if (playerNum == 3)
		{
			p3Chara->setOpacity(0);
		}
		else if (playerNum == 4)
		{
			p4Chara->setOpacity(0);
		}
	}
	p2Chara->setOpacity(255);
	aPlayerChosen = true;
	playerNum = 2;
}

void ServerConnection::player3(cocos2d::Ref* sSender)
{
	if (aPlayerChosen == true)
	{
		if (playerNum == 1)
		{
			p1Chara->setOpacity(0);
		}
		else if (playerNum == 2)
		{
			p2Chara->setOpacity(0);
		}
		else if (playerNum == 4)
		{
			p4Chara->setOpacity(0);
		}
	}
	p3Chara->setOpacity(255);
	aPlayerChosen = true;
	playerNum = 3;
}

void ServerConnection::player4(cocos2d::Ref* sSender)
{
	if (aPlayerChosen == true)
	{
		if (playerNum == 1)
		{
			p1Chara->setOpacity(0);
		}
		else if (playerNum == 2)
		{
			p2Chara->setOpacity(0);
		}
		else if (playerNum == 3)
		{
			p3Chara->setOpacity(0);
		}
	}
	p4Chara->setOpacity(255);
	aPlayerChosen = true;
	playerNum = 4;
}

void ServerConnection::menuCloseCallback(Ref* pSender)
{

	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}

void ServerConnection::Joystick(cocos2d::Event* event)
{
	EventJoystick* e = (EventJoystick*)event;
	//CCLOG("JOYSTICK PRESENT");
	bool present = e->isPresent();
	//CCLOG(std::to_string(present).c_str());
	if (present)
	{
		//default select player 1
		if (aPlayerChosen == false)
		{
			player1(this);
		}
		if (timeDelay == 0) //so you dont skip screens if you hold down button too long on previous screen
		{//CCLOG(e->getName());
			int foraxis;
			const float* axisval = e->getAxes(&foraxis);
			float xval = axisval[0];
			//CCLOG(std::to_string(xval).c_str());
			bool nox = false;
			bool noy = false;
			//below if/else-if statements should check for d-pad too...
			if (xval > 0.6)
			{
				if (playerNum == 1)
				{
					timeDelay = 10; //10 frames or 1/3rd of a second
					player2(this);
				}
				else if (playerNum == 2)
				{
					timeDelay = 10;
					player3(this);
				}
				else if (playerNum == 3)
				{
					timeDelay = 10;
					player4(this);
				}
			}
			else if (xval < -0.6)
			{
				if (playerNum == 2)
				{
					timeDelay = 10;
					player1(this);
				}
				else if (playerNum == 3)
				{
					timeDelay = 10;
					player2(this);
				}
				else if (playerNum == 4)
				{
					timeDelay = 10;
					player3(this);
				}
			}
			int forbutton;
			const unsigned char* buttonval = e->getButtonValues(&forbutton);
			unsigned char b0 = buttonval[0];
			unsigned char b1 = buttonval[1];
			unsigned char b2 = buttonval[2];
			unsigned char b3 = buttonval[3];

			if (b0 || b1 || b2 || b3)
			{
				enter_button->selected();
				button1 = true; //for key_release code
			}

			if (button1 == true && !b0 && !b1 && !b2 && !b3) //button was pushed then released
			{
				enter_button->activate();
				button1 = false;
			}
		}
		if (timeDelay > 0)
		{
			timeDelay--;
		}
	}
	event->stopPropagation();
}

void ServerConnection::KeyDown(EventKeyboard::KeyCode keyCode, Event* event)
{
	switch (keyCode) {
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
