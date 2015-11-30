#ifndef __SERVERPOSITIONPACKET_H__
#define __SERVERPOSITIONPACKET_H__

#include <cereal/archives/binary.hpp>
#include <cereal/archives/json.hpp>

#include <cereal/types/array.hpp>

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
		ar & p3x;
		ar & p3y;
		ar & p4x;
		ar & p4y;
		ar & tilevalues;
	}

public:
	float vx;
	float vy;
	float p1x;
	float p1y;
	float p2x;
	float p2y;
	float p3x;
	float p3y;
	float p4x;
	float p4y;
	std::array<std::array<int, 6>, 6> tilevalues;
	
	ServerPositionPacket(){};
	ServerPositionPacket(float a, float b, float c, float d, float e, float f, float g, float h, float i, float j, std::array<std::array<int, 6>, 6> k) :
		vx(a), vy(b), p1x(c), p1y(d), p2x(e), p2y(f), p3x(g), p3y(h), p4x(i), p4y(j), tilevalues(k)
	{}
};

#endif //  __SERVERPOSITIONPACKET_H__