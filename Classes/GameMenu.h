#ifndef __GAME_MENU_H__
#define __GAME_MENU_H__

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include "cocos2d.h"
#include "ServerConnection.h"
#include "PlayerConnection.h"

USING_NS_CC;

class GameMenu : public cocos2d::Layer
{
private:
	Sprite* background;
	Sprite* left_selector;
	Sprite* right_selector;
	Menu* menu;
	std::vector<MenuItemImage*> buttons;
	//MenuItemImage* music_button;
	//MenuItemImage* sfx_button;
	//MenuItemImage* resume_button;
	//MenuItemImage* exit_button;
	unsigned int current_button = 0;
	EventListenerJoystick* joyListener1;
	//EventListenerKeyboard* keyListener1;

	bool button1 = false;
	bool button_selected = false;
	int timeDelay = 0;
	float zoomFactor = Director::getInstance()->getOpenGLView()->getFrameZoomFactor();

	//menu values
	bool bMusic;
	bool bSFX;
	bool bResume;
	bool bExit;

public:
	static GameMenu* createGameMenu();
	virtual bool init();
	void menuCloseCallback(Ref * pSender);
	void ShowGameMenu();
	void HideGameMenu();
	void music(Ref* pSender);
	void sfx(Ref* pSender);
	void resume(Ref* pSender);
	void video(Ref* pSender);
	void exit(Ref* pSender);

	bool isMusicOn() { return bMusic; }
	bool isSFXOn() { return bSFX; }
	float checkVideo() { return zoomFactor; }
	bool checkResume() { return bResume; }
	bool checkExit() { return bExit; }

	void setMusic(bool b) { bMusic = b; }
	void setSFX(bool b) { bSFX = b; }
	void setResume(bool b) { bResume = b; }
	void setExit(bool b) { bExit = b; }
	void setVideo(int i) { zoomFactor = i; }

	void CycleButtonsUp(void);
	void CycleButtonsDown(void);

	void SetMenuCamera(Vec2 pos);

	//void KeyDown(EventKeyboard::KeyCode keyCode, Event* event);
	//void KeyRelease(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
	void Joystick(Event*);

	CREATE_FUNC(GameMenu);
};


#endif // __GAME_MENU_H__


