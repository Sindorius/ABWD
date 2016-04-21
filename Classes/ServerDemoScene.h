#ifndef __SERVERDEMO_SCENE_H__
#define __SERVERDEMO_SCENE_H__

#include "cocos2d.h"
#include "AudioEngine.h"
#include "Player.h"
#include "ServerSam.h"
#include "Pterodactyl.h"
#include "Candy.h"
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
#include "ServerMessage.hpp"
//#include "UDPServer.hpp"
#include "TCPServer.hpp"
#include "TCPSSession.hpp"
#include "PaintTile.h"
#include "AnimationManager.hpp"
#include "Puzzle.hpp"
#include "LevelManager.hpp"

#define EVENTS_ON 1 //turns scripted events on/off

class TCPServer;
class ServerSam;

class ServerDemo : public cocos2d::Layer
{
private:
	bool alternate = false;
	int swapframes = 1;
	int swapframecounter = 1;
	int dry_time = 0;
	int dry_x = 0;
	int dry_y = 0;
	int transitionTimer = 0;
	int dried = 10;
	bool eventActive = false; //true when scripted game events are happening
	Vec2 samTile;
	Vec2 samInitPos;
	std::vector<Sprite*> pSprites;
	int opacity = 0;
	std::string samHitWall;
	int wallYCoord;

	struct scriptEvent {
		int eventTimer = 0;
		bool isActive = false;
		bool phase1 = false;
		bool phase2 = false;
		bool phase3 = false;
		bool init = false;
	};
	scriptEvent paintEvent; //new level sam painting event
	bool solved_timer_start = false;
	int solved_timer = 60;
	//cocos2d::CCTMXTiledMap* tileMap;
	
	cocos2d::CCTMXLayer* bucketlayer;
	cocos2d::CCTMXLayer* blockage;
	cocos2d::CCTMXLayer* blankCanvas;
	cocos2d::CCTMXObjectGroup* spawnObjs;

	Player* player1;
	Player* player2;
	Player* player3;
	Player* player4;
	std::vector<Player*> players;
	ServerSam* serversam;
	Pterodactyl* pterodactyl;
	Candy* candy;

	std::vector<cocos2d::Sprite*> objects;
	std::vector<ServerMessage> servermessagequeue;

	//Puzzle puzzle;

public:
	// there's no 'id' in cpp, so we recommend returning the class instance pointer
	static cocos2d::Scene* createScene();

	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();

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

	void processPlayerPacket(PlayerInputPacket p, TCPSSession* sessionptr);

	std::vector<std::vector<PaintTile*>> tilespritevector;

	// Paint on the floor
	void space(int playernum, cocos2d::CCPoint tileCoord, float dxmove, float dymove);

	AnimationManager animationmanager;
	LevelManager levelmanager;
	void loadLevel(int level);
	void setupPaintTiles();
	void updatePaintTiles(int playernum);
	int idle1 = 0, idle2 = 0, idle3 = 0, idle4 = 0;
	std::vector<std::vector<char>> blankvector;
	bool sendmap = false;
	ServerPositionPacket createPacket();
	void addPlayerToGame(int playernum);
	void removePlayerFromGame(TCPSSession* sessionptr);
	
	void enqueueMessage(ServerMessage msg);

	boost::bimap<TCPSSession*, int> sessionmap;
	bool sessionmapped[5] = { false };
	char getActiveChars();

	void runEvent(int e);
	bool runPaintEvent(void);
};

#endif // __SERVERDEMO_SCENE_H__