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


////////////////////////////////////////////////////
///   ServerMessage Number Assignments
/////////////////////////////////////////////////////

/*
character messagechar, float xpos, float ypos, char status
0. Assign Player Number, unused, unused, new player number
1. Player 1 pos, xpos, ypos, animation #
2. Player 2 pos, xpos, ypos, animation #
3. Player 3 pos, xpos, ypos, animation #
4. Player 4 pos, xpos, ypos, animation #
5. Sam pos, xpos, ypos, animation #
6. Ptera pos, xpos, ypos, animmation #
7. Candy pos, xpos, ypos, unused
8. Got candy, unused, unused, player #
9. Candy wore off, unused, unused, player #
10. Change Level, unused, unused, new level #
11. Drop Player, unused, unused, player #
12. Player Joined, unused, unused, player #
13. Sam hit player, unused, unused, player #
14. Ptero hit player, unused, unused, player #
15. Go to win game, unused, unused, unused
16. Player got bucket, player number, unused, color # 
17. Player already taken, unused, unused, player #
18. Paint tile dried, row, column, unused








*/