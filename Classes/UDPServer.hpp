#ifndef __UDPSERVER_H__
#define __UDPSERVER_H__


#include <boost/asio.hpp>
#include <cereal/archives/binary.hpp>
#include <cereal/archives/json.hpp>
#include "ServerPositionPacket.hpp"
#include "PlayerInputPacket.hpp"

using boost::asio::ip::udp;

class UDPServer
{
public:
	UDPServer(boost::asio::io_service& io_service, short port)
		: socket_(io_service, udp::endpoint(udp::v4(), port))
	{
		CCLOG("initialized");
		do_receive();
		
	}

	void do_receive()
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
				PlayerInputPacket inpacket(0, 0.0f, 0.0f);
				inar(inpacket);
				std::cout << "input from player " << std::to_string(inpacket.playernum).c_str() << std::endl;
				CCLOG("input from player");
				CCLOG(std::to_string(inpacket.playernum).c_str());
				CCLOG(std::to_string(inpacket.dx).c_str());
				CCLOG(std::to_string(inpacket.dy).c_str());
				if (inpacket.playernum == 1)
				{
					x1move = inpacket.dx;
					y1move = inpacket.dy;
				}
				else
				{
					x2move = inpacket.dx;
					y2move = inpacket.dy;
				}
				//s.send_to(boost::asio::buffer(os2.str()), endpoint);
				do_receive();
			}
			else
			{
				do_receive();
			}
		});
	}

	void do_send()
	{
		std::cout << "sending data back";
		CCLOG("sending data back");
		std::ostringstream os2;
		cereal::BinaryOutputArchive outar(os2);
		ServerPositionPacket packet1(1.2f, 2.3f, 3.4f, 4.5f, 5.6f, 6.7f);
		outar(packet1);

		outstringbuffer = os2.str();
		socket_.async_send_to(
			boost::asio::buffer(outstringbuffer), sender_endpoint_,
			[this](boost::system::error_code /*ec*/, std::size_t /*bytes_sent*/)
		{
			do_receive();
		});
	}

	void sendPacket(ServerPositionPacket p)
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
			do_receive();
		});
	}

	PlayerInputPacket getPlayer1Packet()
	{
		return PlayerInputPacket(1, x1move, y1move);
	}
	PlayerInputPacket getPlayer2Packet()
	{
		return PlayerInputPacket(2, x2move, y2move);
	}

private:
	udp::socket socket_;
	udp::endpoint sender_endpoint_;
	enum { max_length = 1024 };
	char data_[max_length];
	std::string outstringbuffer;
	int x1move= 0;
	int x2move= 0;
	int y1move = 0;
	int y2move= 0;

};

#endif // __UDPSERVER_H__