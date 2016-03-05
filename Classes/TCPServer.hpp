#ifndef __TCPSERVER_H__
#define __TCPSERVER_H__


#include <boost/asio.hpp>
#include <cereal/archives/binary.hpp>
#include <cereal/archives/json.hpp>
#include "ServerPositionPacket.hpp"
#include "PlayerInputPacket.hpp"
#include "ServerDemoScene.h"
#include "cocos2d.h"
#include "TCPSplitter.hpp"
#include "TCPSSession.hpp"

class ServerDemo;
class TCPSSession;

using boost::asio::ip::tcp;

class TCPServer
{

private:
	boost::asio::io_service* io_service_p;
	std::shared_ptr<tcp::socket> newsocket;
	tcp::socket socket_;
	tcp::acceptor acceptor_;
	std::list<TCPSSession*> sessionlist;
	
	enum { max_length = 1024 };
	char data_[max_length];
	std::string outstringbuffer;
	TCPSplitter tcpsplitter;

	int xmove[4] = { 0 };
	int ymove[4] = { 0 };

	ServerDemo* serverptr;
	

public:

	TCPServer::TCPServer(boost::asio::io_service& io_service, short port, ServerDemo* sptr);
	~TCPServer()
	{
		CCLOG("TCPServer deconstructor should not see");
	}
	//void do_receive();
	void do_read();
	void do_accept();
	void sendPacket(ServerPositionPacket p);
	void handle_accept(	const boost::system::error_code& error);
	
	void addPlayer(int playernum);
	void removePlayer(int playernum);
	void removeSession(TCPSSession* sptr);
};

#endif // __TCPSERVER_H__