#include "LevelManager.hpp"




void LevelManager::changeLevel(int level)
{
	if (level == 1)
	{
		levelsprites.clear();
		std::string file = "res//maps//key_room_big.tmx";
		auto str = String::createWithContentsOfFile(FileUtils::getInstance()->fullPathForFilename(file.c_str()).c_str());
		//tileMap = cocos2d::CCTMXTiledMap::createWithXML(str->getCString(), "");
		//tileMap = cocos2d::experimental::TMXTiledMap::createWithXML(str->getCString(), "");
		////////////////////////////////////////////////////////////////////////////////////////////////// NEW ADDED CODE
		levelmap = cocos2d::TMXTiledMap::createWithXML(str->getCString(), "");
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		////////////////////////////////////////////////////////////////////////////////////////////////// NEW ADDED CODE
		Sprite* wallpainting = Sprite::create("res/sprites/objects/key_framed.png");
		wallpainting->getTexture()->setAliasTexParameters();
		wallpainting->setPosition(Vec2(320, 320));
		wallpainting->setScale(1.0f);
		levelsprites.push_back(wallpainting);
		puzzle.changePuzzle(level);
		tilestartpoint = Vec2(276, 48);
	}
	else if (level == 2)
	{
		levelsprites.clear();
		std::string file = "res//maps//happy_sun_paint.tmx";
		auto str = String::createWithContentsOfFile(FileUtils::getInstance()->fullPathForFilename(file.c_str()).c_str());
		//tileMap = cocos2d::CCTMXTiledMap::createWithXML(str->getCString(), "");
		//tileMap = cocos2d::experimental::TMXTiledMap::createWithXML(str->getCString(), "");
		////////////////////////////////////////////////////////////////////////////////////////////////// NEW ADDED CODE
		levelmap = cocos2d::TMXTiledMap::createWithXML(str->getCString(), "");
		
		
		Sprite* wallpainting = Sprite::create("res/sprites/objects/tiny_sun_framed.png");
		wallpainting->getTexture()->setAliasTexParameters();
		wallpainting->setPosition(Vec2(320, 320));
		wallpainting->setScale(1.5f);
		levelsprites.push_back(wallpainting);
		puzzle.changePuzzle(level);
		tilestartpoint = Vec2(264, 90);

	}
	else if (level == 3)
	{
		levelsprites.clear();
		std::string file = "res//maps//pteradactyl_room.tmx";
		auto str = String::createWithContentsOfFile(FileUtils::getInstance()->fullPathForFilename(file.c_str()).c_str());
		//tileMap = cocos2d::CCTMXTiledMap::createWithXML(str->getCString(), "");
		//tileMap = cocos2d::experimental::TMXTiledMap::createWithXML(str->getCString(), "");
		////////////////////////////////////////////////////////////////////////////////////////////////// NEW ADDED CODE
		levelmap = cocos2d::TMXTiledMap::createWithXML(str->getCString(), "");


		Sprite* wallpainting = Sprite::create("res/sprites/objects/pteradactyl_framed.png");
		wallpainting->getTexture()->setAliasTexParameters();
		wallpainting->setPosition(Vec2(370, 460));
		wallpainting->setScale(1.0f);
		levelsprites.push_back(wallpainting);
		puzzle.changePuzzle(level);
		tilestartpoint = Vec2(180, 108);
	}
	else
	{ }

}