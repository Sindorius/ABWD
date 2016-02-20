#ifndef __SERVERMESSAGE_H__
#define __SERVERMESSAGE_H__

#include <cereal/archives/binary.hpp>
#include <cereal/archives/json.hpp>

class ServerMessage
{
private:
	friend class cereal::access;
	template<class Archive>
	void serialize(Archive & ar, const unsigned int version)
	{
		ar & messagechar;
		ar & xpos;
		ar & ypos;
		ar & status;
	}

public:
	char messagechar;
	float xpos;
	float ypos;
	char status;


	ServerMessage() {};
	ServerMessage(char a, float b, float c, char d) :
		messagechar(a), xpos(b), ypos(c), status(d)
	{}
};
#endif // SERVERMESSAGE_H