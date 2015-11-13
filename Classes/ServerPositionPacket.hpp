#ifndef __SERVERPOSITIONPACKET_H__
#define __SERVERPOSITIONPACKET_H__

#include <cereal/archives/binary.hpp>
#include <cereal/archives/json.hpp>

class ServerPositionPacket
{
private:
	friend class cereal::access;
	template<class Archive>
	void serialize(Archive & ar, const unsigned int version)
	{
		ar & vx;
		ar & vy;
		ar & p1x;
		ar & p1y;
		ar & p2x;
		ar & p2y;
	}

public:
	float vx;
	float vy;
	float p1x;
	float p1y;
	float p2x;
	float p2y;

	ServerPositionPacket(){};
	ServerPositionPacket(float a, float b, float c, float d, float e, float f) :
		vx(a), vy(b), p1x(c), p1y(d), p2x(e), p2y(f)
	{}
};

#endif //  __SERVERPOSITIONPACKET_H__