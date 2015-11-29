#include "UDPServer.hpp"


UDPServer::UDPServer(boost::asio::io_service& io_service, short port, ServerDemo* sptr)
	: socket_(io_service, udp::endpoint(udp::v4(), port))
{
	serverptr = sptr;
	CCLOG("initialized");
	do_receive();

}

void UDPServer::do_receive()
{
	socket_.async_receive_from(
		boost::asio::buffer(data_, max_length), sender_endpoint_,
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


void UDPServer::sendPacket(ServerPositionPacket p)
{
	std::cout << "sending data back";
	CCLOG("sending data back");
	std::ostringstream os2;
	cereal::BinaryOutputArchive outar(os2);

	outar(p);

	outstringbuffer = os2.str();
	socket_.async_send_to(
		boost::asio::buffer(outstringbuffer), sender_endpoint_,
		[this](boost::system::error_code /*ec*/, std::size_t /*bytes_sent*/)
	{

	});
}
