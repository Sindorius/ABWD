#pragma once

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <boost/multi_array.hpp>
#include <cereal/types/array.hpp>

class Puzzle
{
public:

	//int width = 3;
	//int height = 7;;
	/*
	std::array<std::array<int,6>,6> tilevalues =
	{ {
		{ 1,1,1,1,1,1 },
		{ 1,1,1,1,1,1 },
		{ 1,1,1,1,1,1 },
		{ 1,1,1,1,1,1 },
		{ 1,1,1,1,1,1 },
		{ 1,1,1,1,1,1 }

		} };
	std::array<std::array<int, 6>, 6> solution =
	{ {

		{ 3,3,5,2,3,3 },
		{ 3,2,4,4,5,3 },
		{ 5,4,4,4,4,2 },
		{ 2,4,4,4,4,5 },
		{ 3,5,4,4,2,3 },
		{ 3,3,2,5,3,3 }

		} };



	std::array<std::array<int, 3>, 7> keytilevalues =
	{ {
		{ 1,1,1 },
		{ 1,1,1 },
		{ 1,1,1 },
		{ 1,1,1 },
		{ 1,1,1 },
		{ 1,1,1 },
		{ 1,1,1 }
	} };
	std::array<std::array<int, 3>, 7> keysolution =
	{ {

		{ 2,2,3 },
		{ 2,1,3 },
		{ 3,3,3 },
		{ 1,2,1 },
		{ 1,2,3 },
		{ 1,2,1 },
		{ 1,3,3 }
	} };
	std::array<std::array<int, 6>, 6> suntilevalues =
	{ {
		{ 1,1,1,1,1,1 },
		{ 1,1,1,1,1,1 },
		{ 1,1,1,1,1,1 },
		{ 1,1,1,1,1,1 },
		{ 1,1,1,1,1,1 },
		{ 1,1,1,1,1,1 }
	} };
	std::array<std::array<int, 6>, 6> sunsolution =
	{ {
		{ 3,3,5,2,3,3 },
		{ 3,2,4,4,5,3 },
		{ 5,4,4,4,4,2 },
		{ 2,4,4,4,4,5 },
		{ 3,5,4,4,2,3 },
		{ 3,3,2,5,3,3 }
	} };
	*/
	std::vector<std::vector<int>> keytilevectorvalues =
	{ {
		{ 1,1,1 },
		{ 1,1,1 },
		{ 1,1,1 },
		{ 1,1,1 },
		{ 1,1,1 },
		{ 1,1,1 },
		{ 1,1,1 }
	} };
	std::vector<std::vector<int>> keytilevectorsolution =
	{ {

		{ 2,2,3 },
		{ 2,1,3 },
		{ 3,3,3 },
		{ 1,2,1 },
		{ 1,2,3 },
		{ 1,2,1 },
		{ 1,3,3 }
	} };

	std::vector<std::vector<int>> keyplayertilesvector =
	{ {
		{ 0,0,0 },
		{ 0,0,0 },
		{ 0,0,0 },
		{ 0,0,0 },
		{ 0,0,0 },
		{ 0,0,0 },
		{ 0,0,0 }

	} };

	std::vector<std::vector<int>> suntilevectorvalues =
	{ {
		{ 1,1,1,1,1,1 },
		{ 1,1,1,1,1,1 },
		{ 1,1,1,1,1,1 },
		{ 1,1,1,1,1,1 },
		{ 1,1,1,1,1,1 },
		{ 1,1,1,1,1,1 }
	} };
	std::vector<std::vector<int>> suntilevectorsolution =
	{ {
		{ 3,3,5,2,3,3 },
		{ 3,2,4,4,5,3 },
		{ 5,4,4,4,4,2 },
		{ 2,4,4,4,4,5 },
		{ 3,5,4,4,2,3 },
		{ 3,3,2,5,3,3 }
	} };

	std::vector<std::vector<int>> sunplayertilesvector =
	{ {
		{ 0,0,0,0,0,0 },
		{ 0,0,0,0,0,0 },
		{ 0,0,0,0,0,0 },
		{ 0,0,0,0,0,0 },
		{ 0,0,0,0,0,0 },
		{ 0,0,0,0,0,0 }
		} };
	
	


	std::vector<std::vector<int>> currenttilevector = keytilevectorvalues;
	std::vector<std::vector<int>> currenttilevectorsolution = keytilevectorsolution;
	std::vector<std::vector<int>> whichplayertilesvector = keyplayertilesvector;

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
					//CCLOG(std::to_string(i).c_str());
					//CCLOG(std::to_string(j).c_str());
					//CCLOG("solution not equal");
					//CCLOG(std::to_string(tilevalues[i][j]).c_str());
					//CCLOG(std::to_string(solution[i][j]).c_str());
					return false;
				}
			}

		}
		return true;

	}
	void changePuzzle(int level);

};