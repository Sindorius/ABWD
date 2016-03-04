#include "LevelManager.hpp"




void LevelManager::changeLevel(int level)
{
	if (level == 1)
	{
		currentlevel = 1;
		levelsprites.clear();
		
		std::string file = "res//maps//key_room_big.tmx";
		auto str = String::createWithContentsOfFile(FileUtils::getInstance()->fullPathForFilename(file.c_str()).c_str());
		levelmap = cocos2d::TMXTiledMap::createWithXML(str->getCString(), "");
		/*
		Sprite* wallpainting = Sprite::create("res/sprites/objects/key_framed.png");
		wallpainting->getTexture()->setAliasTexParameters();
		wallpainting->setPosition(Vec2(320, 320));
		wallpainting->setScale(1.0f);
		levelsprites.push_back(wallpainting);
		puzzle.changePuzzle(level);
		*/
		tilestartpoint = Vec2(276, 48);
		puzzle.changePuzzle(level);



	}
	
	if (level == 2)
	{
		currentlevel = 2;
		levelsprites.clear();
		/*
		std::string file = "res//maps//key_room_big.tmx";
		auto str = String::createWithContentsOfFile(FileUtils::getInstance()->fullPathForFilename(file.c_str()).c_str());
		levelmap = cocos2d::TMXTiledMap::createWithXML(str->getCString(), "");

		Sprite* wallpainting = Sprite::create("res/sprites/objects/key_framed.png");
		wallpainting->getTexture()->setAliasTexParameters();
		wallpainting->setPosition(Vec2(320, 320));
		wallpainting->setScale(1.0f);
		levelsprites.push_back(wallpainting);
		puzzle.changePuzzle(level);
		tilestartpoint = Vec2(276, 48);
		*/

		std::string file = "res//maps//paint_sam.tmx";
		auto str = String::createWithContentsOfFile(FileUtils::getInstance()->fullPathForFilename(file.c_str()).c_str());
		levelmap = cocos2d::TMXTiledMap::createWithXML(str->getCString(), "");

		puzzle.changePuzzle(level);
		tilestartpoint = Vec2(180, 90);


	}
	else if (level == 3)
	{
		currentlevel = 3;
		levelsprites.clear();
		//std::string file = "res//maps//happy_sun_paint.tmx";
		//auto str = String::createWithContentsOfFile(FileUtils::getInstance()->fullPathForFilename(file.c_str()).c_str());
		//levelmap = cocos2d::TMXTiledMap::createWithXML(str->getCString(), "");

		//Sprite* wallpainting = Sprite::create("res/sprites/objects/tiny_sun_framed.png");
		//wallpainting->getTexture()->setAliasTexParameters();
		//wallpainting->setPosition(Vec2(320, 320));
		//wallpainting->setScale(1.5f);
		//levelsprites.push_back(wallpainting);
		//puzzle.changePuzzle(level);
		//tilestartpoint = Vec2(264, 90);

		std::string file = "res//maps//paint_candy.tmx";
		auto str = String::createWithContentsOfFile(FileUtils::getInstance()->fullPathForFilename(file.c_str()).c_str());
		levelmap = cocos2d::TMXTiledMap::createWithXML(str->getCString(), "");

		puzzle.changePuzzle(level);
		tilestartpoint = Vec2(134, 104);

	}
	else if (level == 4)
	{
		currentlevel = 4;
		levelsprites.clear();
		//std::string file = "res//maps//pteradactyl_room.tmx";
		std::string file = "res//maps//paint_ptera.tmx";
		auto str = String::createWithContentsOfFile(FileUtils::getInstance()->fullPathForFilename(file.c_str()).c_str());
		levelmap = cocos2d::TMXTiledMap::createWithXML(str->getCString(), "");

		//Sprite* wallpainting = Sprite::create("res/sprites/objects/pteradactyl_framed.png");
		//wallpainting->getTexture()->setAliasTexParameters();
		//wallpainting->setPosition(Vec2(370, 464));
		//wallpainting->setScale(1.0f);
		//levelsprites.push_back(wallpainting);

		puzzle.changePuzzle(level);
		tilestartpoint = Vec2(168, 64);
	}
	else if (level == 5)
	{
		currentlevel = 5;
		levelsprites.clear();
		//std::string file = "res//maps//pteradactyl_room.tmx";
		std::string file = "res//maps//paint_sun.tmx";
		auto str = String::createWithContentsOfFile(FileUtils::getInstance()->fullPathForFilename(file.c_str()).c_str());
		levelmap = cocos2d::TMXTiledMap::createWithXML(str->getCString(), "");

		//Sprite* wallpainting = Sprite::create("res/sprites/objects/pteradactyl_framed.png");
		//wallpainting->getTexture()->setAliasTexParameters();
		//wallpainting->setPosition(Vec2(370, 464));
		//wallpainting->setScale(1.0f);
		//levelsprites.push_back(wallpainting);

		puzzle.changePuzzle(level);
		tilestartpoint = Vec2(206, 232);

	}

}