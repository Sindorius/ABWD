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
	std::vector<TCPSSession*> sessionvector;
	std::map<int, TCPSSession> clientsessionmap;
	std::vector<std::shared_ptr<tcp::socket>> socketvector;
	
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
	void do_receive();
	void do_read();
	void do_accept();
	void sendPacket(ServerPositionPacket p);
	void handle_accept(	const boost::system::error_code& error);
	/*UDPServer::UDPServer(boost::asio::io_service& io_service, short port, NetworkManager* mptr)
	: socket_(io_service, udp::endpoint(udp::v4(), port))
	{
	networkmanager = mptr;
	CCLOG("initialized");
	do_receive();

	}
	*/
	/*
	void do_send()
	{
	std::cout << "sending data back";
	CCLOG("sending data back");
	std::ostringstream os2;
	cereal::BinaryOutputArchive outar(os2);
	ServerPositionPacket packet1(1.2f, 2.3f, 3.4f, 4.5f, 5.6f, 6.7f, 1.1f,1.1f,1.1f,1.1f);
	outar(packet1);

	outstringbuffer = os2.str();
	for (auto& kv : clientmap)
	{

	socket_.async_send_to(
	boost::asio::buffer(outstringbuffer), kv.second,
	[this](boost::system::error_code , std::size_t )
	{
	do_receive();
	});
	}
	}*/



};

#endif // __UDPSERVER_H__