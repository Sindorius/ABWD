#ifndef __SERVER_CONNECTION__
#define __SERVER_CONNECTION__

#include "cocos2d.h"
#include <cstdlib>
#include "HowToPlay.h"

USING_NS_CC;

class ServerConnection : public cocos2d::Layer
{
private:
	Sprite* Directions;
	CCTMXTiledMap* serverScreen;

	Sprite* p1;
	Sprite* p1Chara;

	Sprite* p2;
	Sprite* p2Chara;

	Sprite* p3;
	Sprite* p3Chara;
	
	Sprite* p4;
	Sprite* p4Chara;

public:
	static cocos2d::Scene* createServerConnection();

	static cocos2d::Scene* createServerConnection(std::string ipa); // NEW CODE TO TRY

	virtual bool init();
	void menuCloseCallback(cocos2d::Ref * pSender);
	void beginGame(cocos2d::Ref* sSender);

	void player1(cocos2d::Ref* sSender);
	void player2(cocos2d::Ref* sSender);
	void player3(cocos2d::Ref* sSender);
	void player4(cocos2d::Ref* sSender);

	bool aPlayerChosen = false;
	int playerNum = 1;

	CREATE_FUNC(ServerConnection);

};


#endif // __SERVER_CONNECTION__
