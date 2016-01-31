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
//#include "UDPServer.hpp"
#include "TCPServer.hpp"
#include "PaintTile.h"
#include "AnimationManager.hpp"

class TCPServer;


class ServerDemo : public cocos2d::Layer
{
private:
	//cocos2d::CCTMXTiledMap* tileMap;

	//cocos2d::experimental::TMXTiledMap* tileMap;
	//cocos2d::experimental::TMXLayer* bucketlayer;
	/////////////////////////////////////////////////////////////////////////////////////////// NEW ADDED CODE
	cocos2d::CCTMXTiledMap* tileMap;
	cocos2d::CCTMXLayer* bucketlayer;

	cocos2d::CCTMXLayer* blockage;
	cocos2d::CCTMXObjectGroup* spawnObjs;
	cocos2d::Sprite* redBucket;
	cocos2d::Sprite* blueBucket;
	cocos2d::Sprite* yellowBucket;
	cocos2d::Sprite* orangeBucket;
	//////////////////////////////////////////////////////////////////////////////////////////////////////////

	//cocos2d::CCTMXLayer* blueBucket;
	//cocos2d::CCTMXLayer* redBucket;
	//cocos2d::CCTMXLayer* yellowBucket;
	//cocos2d::CCTMXLayer* orangeBucket;
	//cocos2d::CCTMXLayer* colorTiles;

	Player* player1;
	Player* player2;
	Player* player3;
	Player* player4;
	std::vector<Player*> players;
	Villain* villain;

	std::vector<cocos2d::Sprite*> objects;


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
	float xmove[4] = { 0 };
	float ymove[4] = { 0 };
	

	ConfigFileInput setupdata;

	boost::asio::io_service* io_service_p;
	//UDPServer* myudpserverp;
	TCPServer* mytcpserverp;


	~ServerDemo();

	void processPlayerPacket(PlayerInputPacket p);

	cocos2d::CCPoint p1pos;
	cocos2d::CCPoint p2pos;
	cocos2d::CCPoint p3pos;
	cocos2d::CCPoint p4pos;
	cocos2d::CCPoint vpos;

	PaintTile* tileptrarray[6][6];
	std::array<std::array<int, 6>, 6> tilevalues = 
	{{
		{ 1,1,1,1,1,1 },
		{ 1,1,1,1,1,1 },
		{ 1,1,1,1,1,1 },
		{ 1,1,1,1,1,1 },
		{ 1,1,1,1,1,1 },
		{ 1,1,1,1,1,1 }

		} };
	std::array<std::array<int, 6>, 6> solution = 
	{{
			/*
		{ 2,2,4,1,2,2 },
		{ 2,1,3,3,4,2 },
		{ 4,3,3,3,3,1 },
		{ 1,3,3,3,3,4 },
		{ 2,4,3,3,1,2 },
		{ 2,2,1,4,2,2 }
		*/
		{ 3,3,5,2,3,3 },
		{ 3,2,4,4,5,3 },
		{ 5,4,4,4,4,2 },
		{ 2,4,4,4,4,5 },
		{ 3,5,4,4,2,3 },
		{ 3,3,2,5,3,3 }

	}};
	std::array<std::array<int, 6>, 6> whichplayertiles =
	{ {
		{ 0,0,0,0,0,0 },
		{ 0,0,0,0,0,0 },
		{ 0,0,0,0,0,0 },
		{ 0,0,0,0,0,0 },
		{ 0,0,0,0,0,0 },
		{ 0,0,0,0,0,0 }

		} };

	// Paint on the floor
	void space(int playernum);
	// Paint on the floor
	////////////////////////////////////////////////////////////////////////////////////////////////////// NEW CODE ADDED
	void space(int playernum, cocos2d::CCPoint tileCoord, float dxmove, float dymove);
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	bool checkSolution();
	AnimationManager animationmanager;

};

#endif // __SERVERDEMO_SCENE_H__
