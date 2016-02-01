#ifndef __SERVERPOSITIONPACKET_H__
#define __SERVERPOSITIONPACKET_H__

#include <cereal/archives/binary.hpp>
#include <cereal/archives/json.hpp>

#include <boost/multi_array.hpp>
#include <boost/serialization/array.hpp>
#include <cereal/types/array.hpp>
#include <cereal/types/valarray.hpp>
#include <cereal/types/vector.hpp>
#include <cereal/types/string.hpp>

class ServerPositionPacket
{
private:
	friend class cereal::access;
	template<class Archive>
	void serialize(Archive & ar, const unsigned int version)
	{
		ar & vx;
		ar & vy;
		ar & vanim;
		ar & p1x;
		ar & p1y;
		ar & p1anim;
		ar & p2x;
		ar & p2y;
		ar & p2anim;
		ar & p3x;
		ar & p3y;
		ar & p3anim;
		ar & p4x;
		ar & p4y;
		ar & p4anim;
		//ar & tilevalues;
		ar & tilevector;
	}

public:
	float vx;
	float vy;
	int vanim;
	float p1x;
	float p1y;
	int p1anim;
	float p2x;
	float p2y;
	int p2anim;
	float p3x;
	float p3y;
	int p3anim;
	float p4x;
	float p4y;
	int p4anim;
	//std::array<std::array<int, 6>, 6> tilevalues;
	std::vector<std::vector<int>> tilevector;
	//boost::multi_array<int, 2> currenttilevalues;

	ServerPositionPacket(){};
	ServerPositionPacket(float va, float vb, int vc, float p1a, float p1b, int p1c, float p2a, float p2b, int p2c, float p3a, float p3b, int p3c, float p4a, float p4b, int p4c, std::vector<std::vector<int>> veca) :
		vx(va), vy(vb), vanim(vc), p1x(p1a), p1y(p1b), p1anim(p1c), p2x(p2a), p2y(p2b), p2anim(p2c), p3x(p3a), p3y(p3b), p3anim(p3c), p4x(p4a), p4y(p4b), p4anim(p4c), tilevector(veca)
	{}
};

#endif //  __SERVERPOSITIONPACKET_H__