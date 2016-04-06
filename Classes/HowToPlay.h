#ifndef __HOW_TO_PLAY__
#define __HOW_TO_PLAY__

#include "cocos2d.h"
#include <cstdlib>
#include <iostream>
#include <fstream>
#include "ClientDemoScene.h"

USING_NS_CC;

class HowToPlay : public cocos2d::Layer
{
private:
	Sprite* Directions;
	Sprite* PaintBuckets;
	Sprite* HTP_D1;
	Sprite* HTP_D2;
	Sprite* HTP_D3;
	Sprite* HTP_D4;
	CCTMXTiledMap* HTPScreen;

	cocos2d::MenuItemImage* begin_button;
	EventListenerJoystick* joyListener;
	EventListenerKeyboard* keyListener;

	bool button1 = false;

public:
	static cocos2d::Scene* createHowToPlay();
	static cocos2d::Scene* createHowToPlay(std::string ipa, int playernum); 
	virtual bool init();
	void menuCloseCallback(cocos2d::Ref * pSender);
	void begin(cocos2d::Ref* sSender);

	void Joystick(cocos2d::Event*);
	void KeyDown(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);

	//int timeDelay = 20;

	CREATE_FUNC(HowToPlay);

};


#endif // __HOW_TO_PLAY__
