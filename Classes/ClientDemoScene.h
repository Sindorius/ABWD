#ifndef __CLIENTDEMO_SCENE_H__
#define __CLIENTDEMO_SCENE_H__

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
#include "PlayerInputPacket.hpp"
#include "PaintTile.h"

USING_NS_CC;
using boost::asio::ip::udp;

class ClientDemo : public cocos2d::Layer
{
private:
	cocos2d::CCTMXTiledMap* tileMap;

	Player* player1;
	Player* player2;
	Player* player3;
	Player* player4;
	std::vector<Player*> players;
	std::string state1, state2, state3, state4;
	bool anim1a = true;
	bool anim1b = true;
	bool anim1c = true;
	bool anim1d = true;
	
	bool anim2a = true;
	bool anim2b = true;
	bool anim2c = true;
	bool anim2d = true;


	Villain* villain;

	bool sam1a = true;
	bool sam1b = true;
	bool sam1c = true;
	bool sam1d = true;

	std::vector<cocos2d::Sprite*> objects;

	//temp//
	cocos2d::Animate* walkupanim;
	cocos2d::Animate* walkdownanim;
	cocos2d::Animate* walkleftanim;
	cocos2d::Animate* walkrightanim;
	cocos2d::Animate* paintanim;

	cocos2d::Animate* walkupanim1;
	cocos2d::Animate* walkdownanim1;
	cocos2d::Animate* walkleftanim1;
	cocos2d::Animate* walkrightanim1;
	cocos2d::Animate* paintanim1;

	cocos2d::Animate* samupanim;
	cocos2d::Animate* samdownanim;
	cocos2d::Animate* samleftanim;
	cocos2d::Animate* samrightanim;


public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(ClientDemo);

	void KeyDown(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
	void KeyRelease(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
	void update(float dt);
	float xmove = 0;
	float ymove = 0;
	bool button1 = false;
	int playernum;
	ConfigFileInput setupdata;

	boost::asio::io_service* io_service_p;
	boost::asio::io_service io_service_;
	//UDPInterface* myudpinterfacep;
	udp::socket* myudpsocketp;
	
	udp::endpoint myendpoint;

	void processPacket(ServerPositionPacket p);
	void doReceive();

	enum { max_length = 1024 };
	char indata[max_length];
	char outdata[max_length];
	std::string outstringbuffer;


	PaintTile* tileptrarray[6][6];
	std::array<std::array<int, 6>, 6> tilevalues = { 1 };

	~ClientDemo();
	
};

#endif // __CLIENTDEMO_SCENE_H__
