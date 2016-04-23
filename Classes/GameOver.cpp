#include "GameOver.h"

Scene* GameOver::createGameOver()
{
	auto gameOverScene = Scene::create();
	auto gameOverlayer = GameOver::create();

	gameOverScene->addChild(gameOverlayer);

	return gameOverScene;
}


bool GameOver::init()
{
	if (!Layer::init())
	{
		return false;
	}

	float winSizeWidth = CCDirector::sharedDirector()->getWinSize().width / 2;
	float winSizeHeight = CCDirector::sharedDirector()->getWinSize().height / 2;

	menu_item = MenuItemImage::create("res//sprites//ui//goToMainNP.png", "res//sprites//ui//goToMainP.png", CC_CALLBACK_1(GameOver::goToMainMenu, this));
	menu_item->setPosition(Vec2(winSizeWidth - 12, winSizeHeight - 35));
	menu_item->setScale(0.7f);

	auto menu = Menu::create(menu_item, NULL);
	menu->setPosition(Point::ZERO);
	this->addChild(menu, 1);

	std::string file = "res//maps//game_over.tmx";
	auto str = String::createWithContentsOfFile(FileUtils::getInstance()->fullPathForFilename(file.c_str()).c_str());
	titleScreen = cocos2d::TMXTiledMap::createWithXML(str->getCString(), "");
	this->addChild(titleScreen, 0);

	gameover = Sprite::create("res//sprites//ui//game_overTitle.png");
	gameover->setScale(0.25f);
	gameover->setPosition(Vec2((int)winSizeWidth - 10, (int)winSizeHeight + 120));
	this->addChild(gameover, 0);

	joyListener = EventListenerJoystick::create();
	joyListener->onEvent = CC_CALLBACK_1(GameOver::Joystick, this);
	_eventDispatcher->addEventListenerWithFixedPriority(joyListener, 1);

	if (MUSIC_ON)
	{
		experimental::AudioEngine::play2d("\\res\\sound\\music\\win_music.mp3", true, 0.5f);
	}

	return true;
}

void GameOver::goToMainMenu(cocos2d::Ref* pSender)
{
	_eventDispatcher->removeEventListener(joyListener);
	joyListener->release();
	joyListener = nullptr;
	experimental::AudioEngine::stopAll();
	auto scene = MenuScene::createMenu();
	CCDirector::getInstance()->replaceScene(TransitionFade::create(3.0f, scene));
}


void GameOver::menuCloseCallback(Ref* pSender)
{
	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}

void GameOver::Joystick(cocos2d::Event* event)
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
			menu_item->selected();
			button1 = true; //for key_release code
		}

		if (button1 == true && !b0 && !b1 && !b2 && !b3) //button was pushed then released
		{
			button1 = false;
			menu_item->activate();
		}
	}
}


