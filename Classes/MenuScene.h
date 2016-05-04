#ifndef __MENU_SCENE_H__
#define __MENU_SCENE_H__

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include "cocos2d.h"
#include "ServerConnection.h"
#include "PlayerConnection.h"

#define MUSIC_ON 1

USING_NS_CC;

class MenuScene : public cocos2d::Layer
{
private:
	Sprite* title;
	CCTMXTiledMap* menuScreen;
	cocos2d::MenuItemImage* server_button;
	cocos2d::MenuItemImage* player_button;
	EventListenerJoystick* joyListener;
	EventListenerKeyboard* keyListener;

	bool button1 = false;

public:
	static cocos2d::Scene* createMenu();
	virtual bool init();
	void menuCloseCallback(cocos2d::Ref * pSender);
	void server(cocos2d::Ref* sSender);
	void player(cocos2d::Ref* pSender);

	void KeyDown(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
	//void KeyRelease(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
	void Joystick(cocos2d::Event*);

	CREATE_FUNC(MenuScene);
};


#endif // __MENU_SCENE_H__


