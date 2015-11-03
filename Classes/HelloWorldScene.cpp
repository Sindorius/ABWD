#include "HelloWorldScene.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    	 

	std::string file = "res//demoroom.tmx";
	auto str = String::createWithContentsOfFile(FileUtils::getInstance()->fullPathForFilename(file.c_str()).c_str());
	tileMap = cocos2d::experimental::TMXTiledMap::createWithXML(str->getCString(), "");
	
	addChild(tileMap, -1);


	player1 = Player::create();
	player1->setPlayernum(1);
	player1->getTexture()->setAliasTexParameters();
	player1->setPosition(Vec2(100, 100));
	player1->setScale(1.5);
	addChild(player1,0);

	player2 = Player::create();
	player2->setPlayernum(2);
	player2->getTexture()->setAliasTexParameters();
	player2->setPosition(Vec2(200, 300));
	player2->setScale(1.5);
	addChild(player2, 0);

	players.push_back(player1);
	players.push_back(player2);

	villain = Villain::create();
	villain->getTexture()->setAliasTexParameters();
	villain->setPosition(Vec2(500, 300));
	villain->setScale(1.5);
	addChild(villain, 0);


	Vector<SpriteFrame*> animFrames;
	animFrames.reserve(4);

	animFrames.pushBack(SpriteFrame::create("\\res\\man1_0.png", Rect(0, 0, 64, 128)));
	animFrames.pushBack(SpriteFrame::create("\\res\\man1_1.png", Rect(0, 0, 64, 128)));
	animFrames.pushBack(SpriteFrame::create("\\res\\man1_2.png", Rect(0, 0, 64, 128)));
	animFrames.pushBack(SpriteFrame::create("\\res\\man1_1.png", Rect(0, 0, 64, 128)));

	animFrames.at(0)->getTexture()->setAliasTexParameters();
	animFrames.at(1)->getTexture()->setAliasTexParameters();
	animFrames.at(2)->getTexture()->setAliasTexParameters();

	// create the animation out of the frames
	Animation* animation = Animation::createWithSpriteFrames(animFrames, 0.2f);
	walkanim = Animate::create(animation);
	walkanim2 = Animate::create(animation);
	player1->runAction(RepeatForever::create(walkanim));
	player2->runAction(RepeatForever::create(walkanim2));

	auto keyListener = EventListenerKeyboard::create();
	keyListener->onKeyPressed = CC_CALLBACK_2(HelloWorld::KeyDown, this);
	keyListener->onKeyReleased = CC_CALLBACK_2(HelloWorld::KeyRelease, this);

	_eventDispatcher->addEventListenerWithFixedPriority(keyListener, 2);

	this->scheduleUpdate();
    return true;
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}



void HelloWorld::KeyDown(EventKeyboard::KeyCode keyCode, Event* event)
{
	
	switch (keyCode){
	case EventKeyboard::KeyCode::KEY_UP_ARROW:
		y1move += 2;
		break;
	case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
		y1move -= 2;
		break;
	case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
		x1move -= 2;
		break;
	case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
		x1move += 2;
		break;
	case EventKeyboard::KeyCode::KEY_W:
		y2move += 2;
		break;
	case EventKeyboard::KeyCode::KEY_S:
		y2move -= 2;
		break;
	case EventKeyboard::KeyCode::KEY_A:
		x2move -= 2;
		break;
	case EventKeyboard::KeyCode::KEY_D:
		x2move += 2;
		break;

	}
	event->stopPropagation();
}

void HelloWorld::KeyRelease(EventKeyboard::KeyCode keyCode, Event* event)
{

	switch (keyCode){
	case EventKeyboard::KeyCode::KEY_UP_ARROW:
		y1move = 0;
		break;
	case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
		y1move = 0;
		break;
	case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
		x1move = 0;
		break;
	case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
		x1move = 0;
		break;
	
	
	case EventKeyboard::KeyCode::KEY_W:
		y2move = 0;
		break;
	case EventKeyboard::KeyCode::KEY_S:
		y2move = 0;
		break;
	case EventKeyboard::KeyCode::KEY_A:
		x2move = 0;
		break;
	case EventKeyboard::KeyCode::KEY_D:
		x2move = 0;
		break;
	}
	event->stopPropagation();

}

void HelloWorld::update(float dt)
{
	player1->setPositionX(player1->getPositionX() + x1move);
	player1->setPositionY(player1->getPositionY() + y1move);
	player2->setPositionX(player2->getPositionX() + x2move);
	player2->setPositionY(player2->getPositionY() + y2move);

	villain->runAI(&players);


}