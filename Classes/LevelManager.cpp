#include "LevelManager.hpp"


void LevelManager::setLevel(int level)
{
	if (level == -1)
	{
		currentlevel = -1;
		
		std::string file = "res//maps//key_room_big.tmx";
		auto str = String::createWithContentsOfFile(FileUtils::getInstance()->fullPathForFilename(file.c_str()).c_str());
		levelmap = cocos2d::TMXTiledMap::createWithXML(str->getCString(), "");

		tilestartpoint = Vec2(276, 48);
		puzzle.changePuzzle(level);
		lastLevel = false;
	}
	
	if (level == 1)
	{
		currentlevel = 1;

		std::string file = "res//maps//paint_sam.tmx";
		auto str = String::createWithContentsOfFile(FileUtils::getInstance()->fullPathForFilename(file.c_str()).c_str());
		levelmap = cocos2d::TMXTiledMap::createWithXML(str->getCString(), "");

		puzzle.changePuzzle(level);
		tilestartpoint = Vec2(180, 90);
		lastLevel = false;

	}
	else if (level == 2)
	{
		currentlevel = 2;

		std::string file = "res//maps//paint_candy.tmx";
		auto str = String::createWithContentsOfFile(FileUtils::getInstance()->fullPathForFilename(file.c_str()).c_str());
		levelmap = cocos2d::TMXTiledMap::createWithXML(str->getCString(), "");

		puzzle.changePuzzle(level);
		tilestartpoint = Vec2(134, 104);
		lastLevel = false;
	}
	else if (level == 3)
	{
		currentlevel = 3;
		std::string file = "res//maps//paint_ptera.tmx";
		auto str = String::createWithContentsOfFile(FileUtils::getInstance()->fullPathForFilename(file.c_str()).c_str());
		levelmap = cocos2d::TMXTiledMap::createWithXML(str->getCString(), "");

		puzzle.changePuzzle(level);
		tilestartpoint = Vec2(168, 64);
		lastLevel = false;
	}
	else if (level == 4)
	{
		currentlevel = 4;
		std::string file = "res//maps//paint_sun.tmx";
		auto str = String::createWithContentsOfFile(FileUtils::getInstance()->fullPathForFilename(file.c_str()).c_str());
		levelmap = cocos2d::TMXTiledMap::createWithXML(str->getCString(), "");

		puzzle.changePuzzle(level);
		tilestartpoint = Vec2(230, 230);
		lastLevel = true;
	}

}