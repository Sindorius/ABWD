#include "TCPServer.hpp"


TCPServer::TCPServer(boost::asio::io_service& io_service, short port, ServerDemo* sptr)
	: socket_(io_service, tcp::endpoint(tcp::v4(), port)), acceptor_(io_service, tcp::endpoint(tcp::v4(), port))

{
	serverptr = sptr;
	CCLOG("initialized");
	do_receive();

}

void TCPServer::do_receive()
{
	socket_.async_receive(boost::asio::buffer(data_, max_length),
		[this](boost::system::error_code ec, std::size_t bytes_recvd)
	{
		if (!ec && bytes_recvd > 0)
		{
			CCLOG("received data");
			std::stringstream is2;
			cereal::BinaryInputArchive inar(is2);
			for (size_t i = 0; i < bytes_recvd; i++)
			{
				// there has to be a better way vectorized? than using for loop!!!
				is2 << data_[i];
			}
			PlayerInputPacket inpacket(0, 0.0f, 0.0f, false);
			inar(inpacket);
			std::cout << "input from player " << std::to_string(inpacket.playernum).c_str() << std::endl;
			CCLOG("input from player");
			CCLOG(std::to_string(inpacket.playernum).c_str());
			CCLOG(std::to_string(inpacket.dx).c_str());
			CCLOG(std::to_string(inpacket.dy).c_str());
			if (clientmap.find(inpacket.playernum) == clientmap.end())
			{
				clientmap.emplace(inpacket.playernum, sender_endpoint_);
			}
			//s.send_to(boost::asio::buffer(os2.str()), endpoint);
			serverptr->processPlayerPacket(inpacket);
			do_receive();
		}
		else
		{
			do_receive();
		}
	});
}


void TCPServer::sendPacket(ServerPositionPacket p)
{
	std::cout << "sending data back";
	CCLOG("sending data back");
	std::ostringstream os2;
	cereal::BinaryOutputArchive outar(os2);

	outar(p);

	outstringbuffer = os2.str();
	socket_.async_write_some(
		boost::asio::buffer(outstringbuffer), 
		[this](boost::system::error_code /*ec*/, std::size_t /*bytes_sent*/)
	{

	});
}
