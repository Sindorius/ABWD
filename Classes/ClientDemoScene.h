#ifndef __CLIENTDEMO_SCENE_H__
#define __CLIENTDEMO_SCENE_H__

#pragma warning(disable : 4996)

#include "cocos2d.h"
#include "Player.h"
#include "Villain.h"
#include "Pterodactyl.h"
#include "Candy.h"
#include "AudioEngine.h"
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
#include "TCPSplitter.hpp"
#include "TCPCSession.hpp"
#include "AnimationManager.hpp"
#include "LevelManager.hpp"
#include "TransitionManager.h" // NEW CODE ADDED
#include "MenuScene.h"
#include "GameOver.h"
#include "GameMenu.h"


#define CURRENT_GRID levelmanager.puzzle.currenttilevector
#define SPRITE_GRID levelmanager.puzzle.tilespritevector
#define DRY_GRID levelmanager.puzzle.drytilevector
#define PLAYER_GRID levelmanager.puzzle.whichplayertilesvector

USING_NS_CC;
using boost::asio::ip::udp;
using boost::asio::ip::tcp;

class TCPCSession;
class Villain;
class GameMenu;

class ClientDemo : public cocos2d::Layer
{
private:
	bool alternate = false;
	int swapframes = 1;
	int swapframecounter = 1;

	TMXLayer* bucketlayer;
	TMXLayer* blockage;
	TMXLayer* blankCanvas;
	TMXObjectGroup* spawnObjs;

	Sprite* tileHighlight;
	Sprite* bucketHighlight;
	
	Player* player1;
	Player* player2;
	Player* player3;
	Player* player4;
	std::vector<Player*> players;
	Villain* villain;
	Pterodactyl* pterodactyl;
	Candy* candy;

	AnimationManager animationmanager;
	struct paintEvent {
		bool canvasFade = false;
		bool init = false;
		std::vector<Sprite*> tileSprites;
	};

	paintEvent pEvent;

	GameMenu* gameMenuLayer;

	bool isPaused = false;

	int eventActive = 0;


public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();
	static cocos2d::Scene* createScene(std::string ipA, int playerNum);
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // implement the "static create()" method manually
    CREATE_FUNC(ClientDemo);

	void KeyDown(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
	void KeyRelease(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
	void update(float dt);
	float xmove = 0;
	float ymove = 0;
	bool button1 = false;
	bool button2 = false; 
	bool button3 = false;
	bool needssync = false;
	int playernum;
	int gameTimer = 65; //prevents camera jerking at start
	bool alreadyPressed = false;
	int opacity = 255;
	ConfigFileInput setupdata;

	boost::asio::io_service* io_service_p;
	boost::asio::io_service io_service_;
	//UDPInterface* myudpinterfacep;
	//udp::socket* myudpsocketp;
	std::shared_ptr<tcp::socket> mytcpsocketp;

	//udp::endpoint myendpoint;
	tcp::endpoint myendpoint;

	void processPacket(ServerPositionPacket p);
	void processServerMessage(ServerMessage msg);
	//void doReceive();

	enum { max_length = 1024 };
	char indata[max_length];
	char outdata[max_length];
	std::string outstringbuffer;
	TCPSplitter tcpsplitter;
	TCPCSession* tcpsessionptr;
	
	std::vector<unsigned int> soundIDList; //keeps list of unique sound IDs
	std::vector<bool> isSFXPlaying; //bools that check whether a certain sfx is playing
	//std::vector<std::string> soundFilePaths;
	//isSFXPlaying indexes correspond to soundIDList indexes, 
	//i.e. isSFXPlaying[0] corresponds to the sound whose sound ID is in soundIDList[0].

	//struct of audio trigger checks for players
	struct playerSFX {
		bool onGrid = false;
		bool onBucket = false;
		bool hasPainted = false;
		bool gotCandy = false;
		bool lostCandy = false;
		bool samCollide = false;
		bool ptCollide = false;
	};
	//all game triggers 
	struct SFXTriggers {
		bool levelChange = false;
		bool musicOn = true;
		bool sfxOn = true;
		bool audioOn = true;
		float oldMVol = 0.4f; //used to remember music volume before it was toggled off
		float oldSVol = 0.7f; //used to remember sfx volume before it was toggled off
		float mVolume = 0.4f;
		float sVolume = 0.7f;
		playerSFX pTrigs[4];
	};
	SFXTriggers gSound;
	void processSound(ServerPositionPacket &p);
	void initializeSound();

	Vec2 pos;

	void highlightBuckets(void);

	void PauseGame(void);
	void ResumeGame(void);
	void updateFromMenu(void);
	void runEvents();

	void playSound(int id, std::string& filePath);

	void space();
	Point plyrCoordToTileCoord(int playerNum);
	int getTileProperties(TMXLayer* mapLayer, Point tileCoord);
	void changeLabelColor(int bTile, int playerNum);

	LevelManager levelmanager;
	TransitionManager transitionManager;
	bool NotInTransition = true;
	float winSizeWidth;
	float winSizeHeight;

	bool playerOneActive = false;
	bool playerTwoActive = false;
	bool playerThreeActive = false;
	bool playerFourActive = false;
	ValueMap playerOneSP;
	ValueMap playerTwoSP;
	ValueMap playerThreeSP;
	ValueMap playerFourSP;

	void loadLevel(int level);
	void setupPaintTiles();
	void centerCamera();
	bool smoothCamera = false;
	void updateTilesFromPacket(ServerPositionPacket p);
	
	void goToMainMenu(cocos2d::Ref* pSender);

	void Joystick(cocos2d::Event*);
	void ClientDemo::setVisiblePlayers(char activechars);
	char activechars = 0;

	~ClientDemo();
	
};

#endif // __CLIENTDEMO_SCENE_H__
