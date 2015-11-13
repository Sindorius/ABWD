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
	}

public:
	int playernum;
	float dx;
	float dy;

	PlayerInputPacket(){};
	PlayerInputPacket(int a, float b, float c) :
		playernum(a), dx(b), dy(c)
	{}
};
#endif // PLAYERINPUTPACKET_H