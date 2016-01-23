#include "TCPCSession.hpp"

void TCPCSession::setClientPtr(ClientDemo* cptr)
{

	clientptr = cptr;
}


void TCPCSession::do_read_header()
{

	CCLOG("inreadheader");
	boost::asio::async_read(*socketptr,
		boost::asio::buffer(tcpsplitterin.data(), tcpsplitterin.header_length),
		[this](boost::system::error_code ec, std::size_t bytes_recvd)
	{
		if (!ec && tcpsplitterin.decode_header())
		{
			do_read_body();
		}
		else
		{
			//socket_.close();
			CCLOG("error");
		}
	});
}

void TCPCSession::do_read_body()
{
	CCLOG("inreadbody");
	boost::asio::async_read(*socketptr,
		boost::asio::buffer(tcpsplitterin.body(), tcpsplitterin.body_length()),
		[this](boost::system::error_code ec, std::size_t bytes_recvd)
	{

		if (!ec && bytes_recvd > 0)
		{

			//std::cout.write(tcpsplitterin.body(), tcpsplitterin.body_length());
			CCLOG(tcpsplitterin.body());



			CCLOG("received data");
			std::stringstream is2;
			cereal::BinaryInputArchive inar(is2);
			for (size_t i = 0; i < bytes_recvd; i++)
			{
				// there has to be a better way vectorized? than using for loop!!!
				is2 << tcpsplitterin.body()[i];
			}
			ServerPositionPacket inpacket;
			inar(inpacket);
			CCLOG("input from server");
			CCLOG(std::to_string(inpacket.p1x).c_str());
			CCLOG(std::to_string(inpacket.p1y).c_str());
			//s.send_to(boost::asio::buffer(os2.str()), endpoint);
			clientptr->processPacket(inpacket);

			do_read_header();
		}
		else
		{
			//socket_.close();
			CCLOG("error");
		}
	});
}




void TCPCSession::writewithstringbuffer(std::string s)
{
	std::memcpy(tcpsplitterout.body(), s.c_str(), s.length());
	CCLOG("s length");
	CCLOG(std::to_string(s.length()).c_str());

	tcpsplitterout.body_length(s.length());
	//tcpsplitterout.decode_header();
	tcpsplitterout.encode_header();
	CCLOG("splitterlength");
	CCLOG(std::to_string(tcpsplitterout.length()).c_str());
	CCLOG("string");
	CCLOG(s.c_str());
	CCLOG("bodylength");
	CCLOG(std::to_string(tcpsplitterout.body_length()).c_str());
	CCLOG("body");
	CCLOG(tcpsplitterout.body());
	std::string bodystring = std::string(tcpsplitterout.body());
	CCLOG(bodystring.c_str());
	CCLOG("Sending packet");
	OutputDebugStringW(L"My output string.");
	//OutputDebugStringA(bodystring.c_str());
	//OutputDebugStringA(s.c_str());

	//std::stringstream is2;
	//cereal::BinaryInputArchive inar(is2);
	//for (size_t i = 0; i < tcpsplitterout.body_length(); i++)
	//{
	// there has to be a better way vectorized? than using for loop!!!
	//	is2 << tcpsplitterout.body()[i];
	//}
	//PlayerInputPacket inpacket(0, 0.0f, 0.0f, false);
	//inar(inpacket);
	//std::ofstream file2("out2.json");
	//cereal::JSONOutputArchive archive2(file2);
	//archive2(inpacket);

	//myudpsocketp->async_send_to(boost::asio::buffer(outstringbuffer), myendpoint, [this](boost::system::error_code /*ec*/, std::size_t /*bytes_sent*/)
	//{
	//CCLOG("Sent packet");

	//});
	boost::asio::async_write(*socketptr, boost::asio::buffer(tcpsplitterout.data(), tcpsplitterout.length()),
		boost::bind(&TCPCSession::handle_write, this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));

	//socketptr->async_write_some(boost::asio::buffer(tcpsplitter.data(), tcpsplitter.length()), [this](boost::system::error_code /*ec*/, std::size_t /*bytes_sent*/)
	//{
	//	CCLOG("Sent packet");

	//		});
	//CCLOG("sentplayerpacket");
	//CCLOG(std::to_string(xmove).c_str());
	//CCLOG(std::to_string(ymove).c_str());
}
void TCPCSession::handle_write(const boost::system::error_code& error,
	size_t bytes_transferred)
{
	CCLOG("wrote packet");
	CCLOG(std::to_string(bytes_transferred).c_str());
}



std::string TCPCSession::readString()
{
	return std::string(tcpsplitterin.body());

}
