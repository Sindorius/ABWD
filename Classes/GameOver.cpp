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

	auto menu_item = MenuItemImage::create("res//sprites//ui//goToMainNP.png", "res//sprites//ui//goToMainP.png", CC_CALLBACK_1(GameOver::goToMainMenu, this));
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

	if (MUSIC_ON)
	{
		experimental::AudioEngine::play2d("\\res\\sound\\music\\win_music.mp3", true, 0.5f);
	}

	return true;
}

void GameOver::goToMainMenu(cocos2d::Ref* pSender)
{
	experimental::AudioEngine::stopAll();
	auto scene = MenuScene::createMenu();
	CCDirector::getInstance()->replaceScene(scene);
}


void GameOver::menuCloseCallback(Ref* pSender)
{
	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}


