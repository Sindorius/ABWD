#pragma once

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <boost/multi_array.hpp>
#include <cereal/types/array.hpp>
#include "cocos2d.h"

class Puzzle
{
public:

	
	std::vector<std::vector<char>> keytilevectorvalues =
	{ {
		{ 1,1,1,1,1 },
		{ 1,1,1,1,1 },
		{ 1,1,1,1,1 },
		{ 1,1,1,1,1 },
		{ 1,1,1,1,1 },
		{ 1,1,1,1,1 },
		{ 1,1,1,1,1 },
		{ 1,1,1,1,1 },
		{ 1,1,1,1,1 }
	} };
	std::vector<std::vector<char>> keytilevectorsolution =
	{ {
		{ 6,6,6,6,6 },
		{ 6,6,5,5,6 },
		{ 6,6,4,6,6 },
		{ 6,6,4,5,6 },
		{ 6,6,4,6,6 },
		{ 6,5,5,5,6 },
		{ 6,4,6,5,6 },
		{ 6,4,4,5,6 },
		{ 6,6,6,6,6 }
	} };

	std::vector<std::vector<char>> keyplayertilesvector =
	{ {
		{ 0,0,0,0,0 },
		{ 0,0,0,0,0 },
		{ 0,0,0,0,0 },
		{ 0,0,0,0,0 },
		{ 0,0,0,0,0 },
		{ 0,0,0,0,0 },
		{ 0,0,0,0,0 },
		{ 0,0,0,0,0 },
		{ 0,0,0,0,0 }

	} };

	std::vector<std::vector<char>> suntilevectorvalues =
	{ {
		{ 1,1,1,1,1,1 },
		{ 1,1,1,1,1,1 },
		{ 1,1,1,1,1,1 },
		{ 1,1,1,1,1,1 },
		{ 1,1,1,1,1,1 },
		{ 1,1,1,1,1,1 }
	} };
	std::vector<std::vector<char>> suntilevectorsolution =
	{ {
		{ 3,3,5,2,3,3 },
		{ 3,2,4,4,5,3 },
		{ 5,4,4,4,4,2 },
		{ 2,4,4,4,4,5 },
		{ 3,5,4,4,2,3 },
		{ 3,3,2,5,3,3 }
	} };

	std::vector<std::vector<char>> sunplayertilesvector =
	{ {
		{ 0,0,0,0,0,0 },
		{ 0,0,0,0,0,0 },
		{ 0,0,0,0,0,0 },
		{ 0,0,0,0,0,0 },
		{ 0,0,0,0,0,0 },
		{ 0,0,0,0,0,0 }
	} };
	
	std::vector<std::vector<char>> ptertilevectorvalues =
	{ {
		{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
		{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
		{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
		{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
		{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
		{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
		{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
		{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
		{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
		{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
		{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
		{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 }
	} };

	std::vector<std::vector<char>> ptertilevectorsolution =
	{ {
		{ 4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4 },
		{ 4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4 },
		{ 4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4 },
		{ 4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4 },
		{ 4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4 },
		{ 4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4 },
		{ 4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4 },
		{ 4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4 },
		{ 4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4 },
		{ 4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4 },
		{ 4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4 },
		{ 4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4 },
		{ 4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4 }
	} };

	std::vector<std::vector<char>> pterplayertilesvector =
	{ {
		{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
		{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
		{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
		{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
		{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
		{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
		{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
		{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
		{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
		{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
		{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
		{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 }
	} };


	std::vector<std::vector<char>> currenttilevector = keytilevectorvalues;
	std::vector<std::vector<char>> currenttilevectorsolution = keytilevectorsolution;
	std::vector<std::vector<char>> whichplayertilesvector = keyplayertilesvector;

	//boost::multi_array<int, 2> currentarray;
	//boost::multi_array<int, 2> solutionarray;

	bool isSolved()
	{
		for (int i = 0; i < currenttilevector.size(); i++)
		{
			for (int j = 0; j < currenttilevector[i].size(); j++)
			{
				if (currenttilevector[i][j] != currenttilevectorsolution[i][j])
				{
					CCLOG(std::to_string(i).c_str());
					CCLOG(std::to_string(j).c_str());
					CCLOG("solution not equal");
					CCLOG(std::to_string(currenttilevector[i][j]).c_str());
					CCLOG(std::to_string(currenttilevectorsolution[i][j]).c_str());
					return false;
				}
			}

		}
		return true;
	}


	bool compareTile(int x, int y, int num)
	{
		if (currenttilevectorsolution[x][y] == num) {
			return true;
		}
		return false;
	}


	void changePuzzle(int level);

};