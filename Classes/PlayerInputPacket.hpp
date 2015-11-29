#ifndef __PLAYERINPUTPACKET_H__
#define __PLAYERINPUTPACKET_H__

#include <cereal/archives/binary.hpp>
#include <cereal/archives/json.hpp>

class PlayerInputPacket
{
private:
	friend class cereal::access;
	template<class Archive>
	void serialize(Archive & ar, const unsigned int version)
	{
		ar & playernum;
		ar & dx;
		ar & dy;
		ar & button1;
	}

public:
	int playernum;
	float dx;
	float dy;
	bool button1;


	PlayerInputPacket(){};
	PlayerInputPacket(int a, float b, float c,bool button1) :
		playernum(a), dx(b), dy(c), button1(button1)
	{}
};
#endif // PLAYERINPUTPACKET_H