#ifndef __CONFIGFILEINPUT_H__
#define __CONFIGFILEINPUT_H__


#include <string>
#include <boost/asio.hpp>
#include <cereal/archives/binary.hpp>
#include <cereal/archives/json.hpp>

class ConfigFileInput
{
private:
	friend class cereal::access;
	template<class Archive>
	void serialize(Archive & ar, const unsigned int version)
	{
		ar & ipaddress;
		ar & port;
		ar & level;

	}
public:
	std::string ipaddress;
	int port;
	int level;


	ConfigFileInput(){ ipaddress = "127.0.0.1"; port = 10001; level = 1; };
	ConfigFileInput(std::string a, int b, int c) :
		ipaddress(a), port(b), level(c)
	{}
};


#endif //__CONFIGFILEINPUT_H__