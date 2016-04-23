#include "MenuScene.h"

Scene* MenuScene::createMenu()
{
	auto ptScene = Scene::create();
	auto ptlayer = MenuScene::create();

	ptScene->addChild(ptlayer);

	return ptScene;
}


bool MenuScene::init()
{
	if (!Layer::init())
	{
		return false;
	}

	//listeners init
	joyListener = EventListenerJoystick::create();
	joyListener->onEvent = CC_CALLBACK_1(MenuScene::Joystick, this);
	_eventDispatcher->addEventListenerWithFixedPriority(joyListener, 1);

	keyListener = EventListenerKeyboard::create();
	keyListener->onKeyPressed = CC_CALLBACK_2(MenuScene::KeyDown, this);
	//keyListener->onKeyReleased = CC_CALLBACK_2(MenuScene::KeyRelease, this);

	_eventDispatcher->addEventListenerWithFixedPriority(keyListener, 2);
	//listeners init end

	float winSizeWidth = CCDirector::sharedDirector()->getWinSize().width / 2;
	float winSizeHeight = CCDirector::sharedDirector()->getWinSize().height / 2;

	server_button = MenuItemImage::create("res//sprites//ui//serverNP.png", "res//sprites//ui//serverP.png", CC_CALLBACK_1(MenuScene::server, this));
	server_button->setPosition(Vec2(winSizeWidth, winSizeHeight - 25));
	server_button->setScale(0.4f);

	player_button = MenuItemImage::create("res//sprites//ui//playerNP.png", "res//sprites//ui//playerP.png", CC_CALLBACK_1(MenuScene::player, this));
	player_button->setPosition(Vec2(winSizeWidth, winSizeHeight - 70));
	player_button->setScale(0.4f);

	auto menu = Menu::create(server_button, player_button, NULL);
	menu->setPosition(Point::ZERO);
	this->addChild(menu, 1);

	std::string file = "res//maps//main_menu.tmx";
	auto str = String::createWithContentsOfFile(FileUtils::getInstance()->fullPathForFilename(file.c_str()).c_str());
	menuScreen = cocos2d::TMXTiledMap::createWithXML(str->getCString(), "");
	this->addChild(menuScreen, 0);

	title = Sprite::create("res//sprites//ui//title2.png");
	title->setScale(0.25f);
	title->setPosition(Vec2((int)winSizeWidth - 10, (int)winSizeHeight + 110));
	this->addChild(title, 0);

	if (MUSIC_ON)
	{
		experimental::AudioEngine::play2d("\\res\\sound\\music\\menu_music.mp3", true, 0.4f);
	}

	return true;
}

void MenuScene::server(cocos2d::Ref* pSender)
{
	_eventDispatcher->removeEventListener(joyListener);
	//joyListener->release();
	//joyListener = nullptr;

	_eventDispatcher->removeEventListener(keyListener);
	//keyListener->release();
	//keyListener = nullptr;

	auto scene = ServerConnection::createServerConnection(0);
	CCDirector::getInstance()->replaceScene(TransitionFade::create(0.5f,scene));
}

void MenuScene::player(cocos2d::Ref* pSender)
{
	_eventDispatcher->removeEventListener(joyListener);
	//joyListener->release();
	//joyListener = nullptr;

	_eventDispatcher->removeEventListener(keyListener);
	//keyListener->release();
	//keyListener = nullptr;

	auto scene = PlayerConnection::createPlayerConnection();
	CCDirector::getInstance()->replaceScene(TransitionFade::create(0.5f, scene));
}


void MenuScene::menuCloseCallback(Ref* pSender)
{
	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}

void MenuScene::Joystick(cocos2d::Event* event)
{
	EventJoystick* e = (EventJoystick*)event;
	//CCLOG("JOYSTICK PRESENT");
	bool present = e->isPresent();
	//CCLOG(std::to_string(present).c_str());
	if (present)
	{
		//CCLOG(e->getName());

		int forbutton;
		const unsigned char* buttonval = e->getButtonValues(&forbutton);
		unsigned char b0 = buttonval[0];
		unsigned char b1 = buttonval[1];
		unsigned char b2 = buttonval[2];
		unsigned char b3 = buttonval[3];

		if (b0 || b1 || b2 || b3)
		{
			player_button->selected();
			button1 = true; //for key_release code
			//add button to select hidden server button
		}

		if (button1 == true && !b0 && !b1 && !b2 && !b3) //button was pushed then released
		{
			button1 = false;
			player_button->activate();
		}

	}
	event->stopPropagation();
}


void MenuScene::KeyDown(EventKeyboard::KeyCode keyCode, Event* event)
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

/*void MenuScene::KeyRelease(EventKeyboard::KeyCode keyCode, Event* event)
{

	switch (keyCode) {
	case EventKeyboard::KeyCode::KEY_UP_ARROW:
		break;
	}

	event->stopPropagation();

}*/


