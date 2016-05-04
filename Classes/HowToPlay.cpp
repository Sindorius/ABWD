#include "HowToPlay.h"

// CODE TO TRY
std::string IPADDRESS = "";
int PLAYERNUM = 1;
//////////////

Scene* HowToPlay::createHowToPlay()
{
	auto HTPScene = Scene::create();
	auto HTPlayer = HowToPlay::create();

	HTPScene->addChild(HTPlayer);

	return HTPScene;
}

// CODE TO TRY
Scene* HowToPlay::createHowToPlay(std::string ip, int pn)
{
	IPADDRESS = ip;
	PLAYERNUM = pn;

	auto HTPScene = Scene::create();
	auto HTPlayer = HowToPlay::create();

	HTPScene->addChild(HTPlayer);

	return HTPScene;
}
///////////////


bool HowToPlay::init()
{
	if (!Layer::init())
	{
		return false;
	}

	float winSizeWidth = CCDirector::sharedDirector()->getWinSize().width / 2;
	float winSizeHeight = CCDirector::sharedDirector()->getWinSize().height / 2;

	begin_button = MenuItemImage::create("res//sprites//ui//GameBeginNP.png", "res//sprites//ui//GameBeginP.png", CC_CALLBACK_1(HowToPlay::begin, this));
	begin_button->setPosition(Vec2(winSizeWidth + 12, winSizeHeight - 125));
	begin_button->setScale(0.5f);

	auto layer = Menu::create(begin_button, NULL);
	layer->setPosition(Point::ZERO);
	this->addChild(layer, 1);

	std::string file = "res//maps//how_to_play.tmx";
	auto str = String::createWithContentsOfFile(FileUtils::getInstance()->fullPathForFilename(file.c_str()).c_str());
	HTPScreen = cocos2d::TMXTiledMap::createWithXML(str->getCString(), "");
	this->addChild(HTPScreen, 0);

	Directions = Sprite::create("res//sprites//ui//how_to_play.png");
	Directions->setScale(0.5f);
	Directions->setPosition(Vec2((int)winSizeWidth, (int)winSizeHeight));
	this->addChild(Directions, 0);

	joyListener = EventListenerJoystick::create();
	joyListener->onEvent = CC_CALLBACK_1(HowToPlay::Joystick, this);
	_eventDispatcher->addEventListenerWithFixedPriority(joyListener, 1);

	keyListener = EventListenerKeyboard::create();
	keyListener->onKeyPressed = CC_CALLBACK_2(HowToPlay::KeyDown, this);
	_eventDispatcher->addEventListenerWithFixedPriority(keyListener, 2);

	return true;
}


void HowToPlay::begin(cocos2d::Ref* pSender)
{
	_eventDispatcher->removeEventListener(joyListener);
	//joyListener->release();
	//joyListener = nullptr;

	_eventDispatcher->removeEventListener(keyListener);
	//keyListener->release();
	//keyListener = nullptr;

	experimental::AudioEngine::stopAll();
	auto scene = ClientDemo::createScene(IPADDRESS, PLAYERNUM); // CODE TO TRY
	//CCDirector::getInstance()->replaceScene(scene);
	Director::getInstance()->replaceScene(TransitionFade::create(2.0f, scene));
}


void HowToPlay::menuCloseCallback(Ref* pSender)
{

	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}

void HowToPlay::Joystick(cocos2d::Event* event)
{
	EventJoystick* e = (EventJoystick*)event;
	//CCLOG("JOYSTICK PRESENT");
	bool present = e->isPresent();
	//CCLOG(std::to_string(present).c_str());
	if (present)
	{
//		if (timeDelay == 0)
//		{
			int forbutton;
			const unsigned char* buttonval = e->getButtonValues(&forbutton);
			unsigned char b0 = buttonval[0];
			unsigned char b1 = buttonval[1];
			unsigned char b2 = buttonval[2];
			unsigned char b3 = buttonval[3];

			if (b0 || b1 || b2 || b3)
			{
				begin_button->selected();
				button1 = true; //for key_release code
			}

			if (button1 == true && !b0 && !b1 && !b2 && !b3) //button was pushed then released
			{
				begin_button->activate();
				button1 = false;
			}
//		}
//		if (timeDelay > 0)
//		{
//			timeDelay--;
//		}
	}
	event->stopPropagation();
}

void HowToPlay::KeyDown(EventKeyboard::KeyCode keyCode, Event* event)
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