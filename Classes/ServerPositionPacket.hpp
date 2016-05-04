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

#include "ServerMessage.hpp"

class ServerPositionPacket
{
private:
	friend class cereal::access;
	template<class Archive>
	void serialize(Archive & ar, const unsigned char version)
	{
		ar & activeplayers;
		ar & level;
		ar & candyx;
		ar & candyy;
		ar & ptx;
		ar & pty;
		ar & ptanim;
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
		ar & tilevector;
		ar & messagevector;
	}

public:
	char activeplayers;
	char level;
	float candyx;
	float candyy;
	float ptx;
	float pty;
	char ptanim;
	float vx;
	float vy;
	char vanim;
	float p1x;
	float p1y;
	char p1anim;
	float p2x;
	float p2y;
	char p2anim;
	float p3x;
	float p3y;
	char p3anim;
	float p4x;
	float p4y;
	char p4anim;
	std::vector<std::vector<char>> tilevector;
	//boost::multi_array<char, 2> currenttilevalues;
	std::vector<ServerMessage> messagevector;
	ServerPositionPacket() {};
	ServerPositionPacket(char actp, char lev, float candya, float candyb, float pta, float ptb, char ptc, float va, float vb, char vc, float p1a, float p1b, char p1c, float p2a, float p2b, char p2c, float p3a, float p3b, char p3c, float p4a, float p4b, char p4c, std::vector<std::vector<char>> veca, std::vector<ServerMessage> vecm) :
		activeplayers(actp),level(lev),candyx(candya), candyy(candyb), ptx(pta), pty(ptb), ptanim(ptc), vx(va), vy(vb), vanim(vc), p1x(p1a), p1y(p1b), p1anim(p1c), p2x(p2a), p2y(p2b), p2anim(p2c), p3x(p3a), p3y(p3b), p3anim(p3c), p4x(p4a), p4y(p4b), p4anim(p4c), tilevector(veca), messagevector(vecm)
	{}
	//ServerPositionPacket(float pta, float ptb, char ptc, float va, float vb, char vc, float p1a, float p1b, char p1c, float p2a, float p2b, char p2c, float p3a, float p3b, char p3c, float p4a, float p4b, char p4c, std::vector<std::vector<char>> veca) :
	//	ptx(pta), pty(ptb), ptanim(ptc), vx(va), vy(vb), vanim(vc), p1x(p1a), p1y(p1b), p1anim(p1c), p2x(p2a), p2y(p2b), p2anim(p2c), p3x(p3a), p3y(p3b), p3anim(p3c), p4x(p4a), p4y(p4b), p4anim(p4c), tilevector(veca)
	//{}
};

#endif //  __SERVERPOSITIONPACKET_H__