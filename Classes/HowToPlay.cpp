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

	auto begin_button = MenuItemImage::create("res//sprites//ui//GameBeginNP.png", "res//sprites//ui//GameBeginP.png", CC_CALLBACK_1(HowToPlay::begin, this));
	begin_button->setPosition(Vec2(winSizeWidth - 25, winSizeHeight - 125));
	begin_button->setScale(0.5f);

	auto layer = Menu::create(begin_button, NULL);
	layer->setPosition(Point::ZERO);
	this->addChild(layer, 1);

	std::string file = "res//maps//how_to_play.tmx";
	auto str = String::createWithContentsOfFile(FileUtils::getInstance()->fullPathForFilename(file.c_str()).c_str());
	HTPScreen = cocos2d::TMXTiledMap::createWithXML(str->getCString(), "");
	this->addChild(HTPScreen, 0);

	Directions = Sprite::create("res//sprites//ui//howToPlayDirections.png");
	Directions->setScale(0.2f);
	Directions->setPosition(Vec2((int)winSizeWidth - 10, (int)winSizeHeight + 143));
	this->addChild(Directions, 0);

	PaintBuckets = Sprite::create("res//sprites//buckets.png");
	PaintBuckets->setScale(0.6f);
	PaintBuckets->setPosition(Vec2((int)winSizeWidth - 225, (int)winSizeHeight - 17));
	this->addChild(PaintBuckets, 0);

	HTP_D1 = Sprite::create("res//sprites//ui//HTP_D1.png");
	HTP_D1->setScale(0.12f);
	HTP_D1->setPosition(Vec2((int)winSizeWidth - 100, (int)winSizeHeight + 75));
	this->addChild(HTP_D1, 0);

	HTP_D4 = Sprite::create("res//sprites//ui//HTP_D4.png");
	HTP_D4->setScale(0.12f);
	HTP_D4->setPosition(Vec2((int)winSizeWidth + 30, (int)winSizeHeight + 35));
	this->addChild(HTP_D4, 0);

	HTP_D2 = Sprite::create("res//sprites//ui//HTP_D2.png");
	HTP_D2->setScale(0.12f);
	HTP_D2->setPosition(Vec2((int)winSizeWidth - 50, (int)winSizeHeight - 20));
	this->addChild(HTP_D2, 0);

	HTP_D3 = Sprite::create("res//sprites//ui//HTP_D3.png");
	HTP_D3->setScale(0.12f);
	HTP_D3->setPosition(Vec2((int)winSizeWidth - 50, (int)winSizeHeight - 70));
	this->addChild(HTP_D3, 0);

	return true;
}


void HowToPlay::begin(cocos2d::Ref* pSender)
{
	auto scene = ClientDemo::createScene(IPADDRESS, PLAYERNUM); // CODE TO TRY
	CCDirector::getInstance()->replaceScene(scene);
	//CCDirector::getInstance()->replaceScene(TransitionFade::create(0.9, scene, Color3B(255, 255, 255)));

}


void HowToPlay::menuCloseCallback(Ref* pSender)
{
	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}