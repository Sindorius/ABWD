#include "TCPServer.hpp"


TCPServer::TCPServer(boost::asio::io_service& io_service, short port, ServerDemo* sptr)
	: io_service_p(&io_service), socket_(io_service), acceptor_ ( io_service, tcp::endpoint(tcp::v4(), port) )
{
//	socket_ = boost::asio::basic_stream_socket( io_service, tcp::endpoint(tcp::v4(), port) );
	
	serverptr = sptr;
	CCLOG("initialized");
	do_accept();
//	do_receive();

}
void TCPServer::do_accept()
{
	CCLOG("in do_accept");
	newsocket = std::make_shared<tcp::socket>(boost::ref(*io_service_p));
	
	acceptor_.async_accept(*newsocket,
		boost::bind(&TCPServer::handle_accept, this,
			boost::asio::placeholders::error));
}

void TCPServer::handle_accept(
	const boost::system::error_code& error)
{
	CCLOG("in accept");
	if (!error)
	{
		CCLOG("no error adding to socketlist");
		CCLOG("starting socket read header");
		
		sessionvector.push_back(TCPSSession(newsocket,serverptr));
		sessionvector.at(sessionvector.size() - 1).do_read_header();
		
		CCLOG(std::to_string(sessionvector.size()).c_str());
		//socketvector.push_back(newsocket);
		//CCLOG(std::to_string(socketvector.size()).c_str());
	}
	else
	{
		CCLOG("error value");
		CCLOG(std::to_string(error.value()).c_str());
	}

	do_accept();
}

void TCPServer::do_receive()
{
}


void TCPServer::sendPacket(ServerPositionPacket p)
{
	std::cout << "sending data back";
	CCLOG("sending data back");
	std::ostringstream os2;
	cereal::BinaryOutputArchive outar(os2);

	outar(p);

	outstringbuffer = os2.str();
	for each(TCPSSession s in sessionvector)
	{
	//	s.socketptr->async_write_some(boost::asio::buffer(outstringbuffer),
	//		[this](boost::system::error_code /*ec*/, std::size_t /*bytes_sent*/)
	//	{
	//		CCLOG("wrote to client");
	//	});

		s.writewithstringbuffer(outstringbuffer);
		
	}
	
}
