#ifndef __SERVERDEMO_SCENE_H__
#define __SERVERDEMO_SCENE_H__

#include "cocos2d.h"
#include "Player.h"
#include "Villain.h"
#include "Pterodactyl.h"
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
#include "Puzzle.hpp"
#include "LevelManager.hpp"

class TCPServer;


class ServerDemo : public cocos2d::Layer
{
private:

	//cocos2d::CCTMXTiledMap* tileMap;
	cocos2d::CCTMXLayer* bucketlayer;

	cocos2d::CCTMXLayer* blockage;
	cocos2d::CCTMXObjectGroup* spawnObjs;

	Player* player1;
	Player* player2;
	Player* player3;
	Player* player4;
	std::vector<Player*> players;
	Villain* villain;
	Pterodactyl* pterodactyl;

	std::vector<cocos2d::Sprite*> objects;
	//Puzzle puzzle;

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
	cocos2d::CCPoint ppos;

	//PaintTile* tileptrarray[6][6];

	std::vector<std::vector<PaintTile*>> tilespritevector;
	/*
	std::array<std::array<int, 6>, 6> whichplayertiles =
	{ {
	{ 0,0,0,0,0,0 },
	{ 0,0,0,0,0,0 },
	{ 0,0,0,0,0,0 },
	{ 0,0,0,0,0,0 },
	{ 0,0,0,0,0,0 },
	{ 0,0,0,0,0,0 }
	} };
	*/

	// Paint on the floor
	void space(int playernum, cocos2d::CCPoint tileCoord, float dxmove, float dymove);

	AnimationManager animationmanager;
	LevelManager levelmanager;
	void loadLevel(int level);
	void setupPaintTiles();
	int idle1, idle2, idle3, idle4;
	std::vector<std::vector<char>> blankvector;
	bool sendmap = false;
	ServerPositionPacket createPacket();
	void addPlayerToGame(int playernum);
	void removePlayerFromGame(int playernum);
};

#endif // __SERVERDEMO_SCENE_H__