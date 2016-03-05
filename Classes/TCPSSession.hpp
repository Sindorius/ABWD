#pragma once
#include <boost/asio.hpp>
#include <cereal/archives/binary.hpp>
#include <cereal/archives/json.hpp>
#include "ServerPositionPacket.hpp"
#include "PlayerInputPacket.hpp"
#include "cocos2d.h"
#include "TCPSplitter.hpp"
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include "ServerDemoScene.h"

using boost::asio::ip::tcp;

class ServerDemo;
class TCPServer;

class TCPSSession
{
private:
public:

	std::shared_ptr<tcp::socket> socketptr;
	TCPSplitter tcpsplitterin;
	TCPSplitter tcpsplitterout;
	enum { max_length = 1024 };
	char indata[max_length];
	char outdata[max_length];
	ServerDemo* serverptr;
	TCPServer* tcpserverptr;

	TCPSSession()
	{
		socketptr = nullptr;
		serverptr = nullptr;
		tcpserverptr = nullptr;
	};

	TCPSSession(std::shared_ptr<tcp::socket> sptr, ServerDemo* sdptr, TCPServer* tcpsptr) : socketptr(sptr), serverptr(sdptr), tcpserverptr(tcpsptr)
	{
	socketptr->set_option(tcp::no_delay(true));
	};
	~TCPSSession()
	{
		CCLOG("deconstructor - should not happen");

	}

	std::string readString();
	void setServerPtr(ServerDemo* cptr);
	void do_read_header();
	void do_read_body();
	void handle_read_header(boost::system::error_code ec, std::size_t bytes_recvd);
	void handle_read_body(boost::system::error_code ec, std::size_t bytes_recvd);

	void writewithstringbuffer(std::string s);
	void handle_write(const boost::system::error_code& error,
		size_t bytes_transferred);



};