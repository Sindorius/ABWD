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

	float winSizeWidth = CCDirector::sharedDirector()->getWinSize().width / 2;
	float winSizeHeight = CCDirector::sharedDirector()->getWinSize().height / 2;

	auto server_button = MenuItemImage::create("res//sprites//ui//serverNP.png", "res//sprites//ui//serverP.png", CC_CALLBACK_1(MenuScene::server, this));
	server_button->setPosition(Vec2(winSizeWidth, winSizeHeight - 25));
	server_button->setScale(0.4f);

	auto player_button = MenuItemImage::create("res//sprites//ui//playerNP.png", "res//sprites//ui//playerP.png", CC_CALLBACK_1(MenuScene::player, this));
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

	experimental::AudioEngine::play2d("\\res\\sound\\music\\menu_music.mp3", true);

	return true;
}

void MenuScene::server(cocos2d::Ref* pSender)
{
	auto scene = ServerConnection::createServerConnection(0);
	CCDirector::getInstance()->replaceScene(scene);
}

void MenuScene::player(cocos2d::Ref* pSender)
{
	auto scene = PlayerConnection::createPlayerConnection();
	CCDirector::getInstance()->replaceScene(scene);
}


void MenuScene::menuCloseCallback(Ref* pSender)
{
	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}


