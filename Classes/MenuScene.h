#ifndef __MENU_SCENE_H__
#define __MENU_SCENE_H__

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include "cocos2d.h"
#include "ServerConnection.h"
#include "PlayerConnection.h"

USING_NS_CC;

class MenuScene : public cocos2d::Layer
{
private:
	Sprite* title;
	CCTMXTiledMap* menuScreen;

public:
	static cocos2d::Scene* createMenu();
	virtual bool init();
	void menuCloseCallback(cocos2d::Ref * pSender);
	void server(cocos2d::Ref* sSender);
	void player(cocos2d::Ref* pSender);

	CREATE_FUNC(MenuScene);
};


#endif // __MENU_SCENE_H__


