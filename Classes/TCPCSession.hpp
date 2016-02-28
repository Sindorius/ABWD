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
#include "ClientDemoScene.h"

using boost::asio::ip::tcp;

class ClientDemo;

class TCPCSession  
{
private:
public:

	std::shared_ptr<tcp::socket> socketptr;
	TCPSplitter tcpsplitterin;
	TCPSplitter tcpsplitterout;
	enum { max_length = 1024 };
	char indata[max_length];
	char outdata[max_length];
	ClientDemo* clientptr;

	TCPCSession()
	{
		socketptr = nullptr;
		clientptr = nullptr;
	};

	TCPCSession(std::shared_ptr<tcp::socket> sptr, ClientDemo* cptr) : socketptr(sptr), clientptr(cptr)
	{
		socketptr->set_option(tcp::no_delay(true));
	};

	std::string readString();
	void setClientPtr(ClientDemo* cptr);
	void do_read_header();
	void do_read_body();
	void writewithstringbuffer(std::string s);
	void handle_write(const boost::system::error_code& error,
		size_t bytes_transferred);



};