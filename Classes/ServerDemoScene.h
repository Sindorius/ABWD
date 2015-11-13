#ifndef __SERVERDEMO_SCENE_H__
#define __SERVERDEMO_SCENE_H__

#include "cocos2d.h"
#include "Player.h"
#include "Villain.h"
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <fstream>
#include <string>
#include <boost/asio.hpp>
#include <cereal/archives/binary.hpp>
#include <cereal/archives/json.hpp>
#include <boost/thread/thread.hpp>
#include "ConfigFileInput.hpp"
#include "ServerPositionPacket.hpp"
#include "UDPServer.hpp"

class ServerDemo : public cocos2d::Layer
{
private:
	cocos2d::experimental::TMXTiledMap* tileMap;

	Player* player1;
	Player* player2;
	std::vector<Player*> players;
	Villain* villain;

	std::vector<cocos2d::Sprite*> objects;


	cocos2d::Animate* walkanim;
	cocos2d::Animate* walkanim2;

public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(ServerDemo);

	void KeyDown(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
	void KeyRelease(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
	void update(float dt);
	float x1move = 0;
	float y1move = 0;
	float x2move = 0;
	float y2move = 0;

	ConfigFileInput setupdata;

	boost::asio::io_service* io_service_p;
	UDPServer* myudpserverp;

	~ServerDemo();
};

#endif // __HELLOWORLD_SCENE_H__
