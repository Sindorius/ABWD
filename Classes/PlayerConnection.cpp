#include "PlayerConnection.h"

Scene* PlayerConnection::createPlayerConnection()
{
	auto PCScene = Scene::create();
	auto PClayer = PlayerConnection::create();

	PCScene->addChild(PClayer);

	return PCScene;
}


bool PlayerConnection::init()
{
	if (!Layer::init())
	{
		return false;
	}

	std::ifstream is("config.json");
	cereal::JSONInputArchive configloader(is);
	ConfigFileInput setupdata = ConfigFileInput();
	configloader(setupdata);
	is.close();
	IPAddress = setupdata.ipaddress;

	float winSizeWidth = CCDirector::sharedDirector()->getWinSize().width / 2;
	float winSizeHeight = CCDirector::sharedDirector()->getWinSize().height / 2;

	auto begin_button = MenuItemImage::create("res//sprites//ui//choosePlayerNP.png", "res//sprites//ui//choosePlayerP.png", CC_CALLBACK_1(PlayerConnection::beginGame, this));
	begin_button->setPosition(Vec2(winSizeWidth-10, winSizeHeight-100));
	begin_button->setScale(0.6f);

	auto layer = Menu::create(begin_button, NULL);
	layer->setPosition(Point::ZERO);
	this->addChild(layer, 1);

	std::string file = "res//maps//player_connection.tmx";
	auto str = String::createWithContentsOfFile(FileUtils::getInstance()->fullPathForFilename(file.c_str()).c_str());
	playerScreen = cocos2d::TMXTiledMap::createWithXML(str->getCString(), "");
	this->addChild(playerScreen, 0);

	Directions = Sprite::create("res//sprites//ui//playerDirections.png");
	Directions->setScale(0.25f);
	Directions->setPosition(Vec2((int)winSizeWidth - 10, (int)winSizeHeight + 120));
	this->addChild(Directions, 0);

	IPLabel = CCLabelTTF::create(IPAddress, "fonts/Marker Felt.ttf", 12);
	IPLabel->setPosition(Vec2((int)winSizeWidth - 10, (int)winSizeHeight - 24));
	this->addChild(IPLabel, 1);

	keyboard = EventListenerKeyboard::create();
	keyboard->onKeyPressed = CC_CALLBACK_2(PlayerConnection::KeyP, this);
	keyboard->onKeyReleased = CC_CALLBACK_2(PlayerConnection::KeyNP, this);

	_eventDispatcher->addEventListenerWithFixedPriority(keyboard, 2);

	return true;
}


void PlayerConnection::beginGame(cocos2d::Ref* pSender)
{	
	if (IPAddress != "")
	{
		keyboard->setEnabled(false);
		auto scene = ServerConnection::createServerConnection(IPAddress,0); 
		CCDirector::getInstance()->replaceScene(scene);
	}
}


void PlayerConnection::menuCloseCallback(Ref* pSender)
{
	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}


void PlayerConnection::KeyP(EventKeyboard::KeyCode keyCode, Event* event)
{

	switch (keyCode) {
	case EventKeyboard::KeyCode::KEY_0:
		IPAddress += "0";
		IPLabel->setString(IPAddress);
		break;
	case EventKeyboard::KeyCode::KEY_1:
		IPAddress += "1";
		IPLabel->setString(IPAddress);
		break;
	case EventKeyboard::KeyCode::KEY_2:
		IPAddress += "2";
		IPLabel->setString(IPAddress);
		break;
	case EventKeyboard::KeyCode::KEY_3:
		IPAddress += "3";
		IPLabel->setString(IPAddress);
		break;
	case EventKeyboard::KeyCode::KEY_4:
		IPAddress += "4";
		IPLabel->setString(IPAddress);
		break;
	case EventKeyboard::KeyCode::KEY_5:
		IPAddress += "5";
		IPLabel->setString(IPAddress);
		break;
	case EventKeyboard::KeyCode::KEY_6:
		IPAddress += "6";
		IPLabel->setString(IPAddress);
		break;
	case EventKeyboard::KeyCode::KEY_7:
		IPAddress += "7";
		IPLabel->setString(IPAddress);
		break;
	case EventKeyboard::KeyCode::KEY_8:
		IPAddress += "8";
		IPLabel->setString(IPAddress);
		break;
	case EventKeyboard::KeyCode::KEY_9:
		IPAddress += "9";
		IPLabel->setString(IPAddress);
		break;
	case EventKeyboard::KeyCode::KEY_PERIOD:
		IPAddress += ".";
		IPLabel->setString(IPAddress);
		break;
	case EventKeyboard::KeyCode::KEY_BACKSPACE:
		if (IPAddress.size() > 0)
		{
			IPAddress.erase(IPAddress.size() - 1);
			IPLabel->setString(IPAddress);
		}
		break;
	}

	event->stopPropagation();
}


void PlayerConnection::KeyNP(EventKeyboard::KeyCode keyCode, Event* event)
{

	switch (keyCode) {
	case EventKeyboard::KeyCode::KEY_0:
		break;
	case EventKeyboard::KeyCode::KEY_1:
		break;
	case EventKeyboard::KeyCode::KEY_2:
		break;
	case EventKeyboard::KeyCode::KEY_3:
		break;
	case EventKeyboard::KeyCode::KEY_4:
		break;
	case EventKeyboard::KeyCode::KEY_5:
		break;
	case EventKeyboard::KeyCode::KEY_6:
		break;
	case EventKeyboard::KeyCode::KEY_7:
		break;
	case EventKeyboard::KeyCode::KEY_8:
		break;
	case EventKeyboard::KeyCode::KEY_9:
		break;
	case EventKeyboard::KeyCode::KEY_PERIOD:
		break;
	case EventKeyboard::KeyCode::KEY_BACKSPACE:
		break;
	}

	event->stopPropagation();
}
