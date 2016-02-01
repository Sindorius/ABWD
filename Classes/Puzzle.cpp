#include "Puzzle.hpp"

void Puzzle::changePuzzle(int level)
{

	if (level == 1)
	{
		//boost::multi_array<int, 2>::extent_gen extents;
		//currentarray.resize(extents[7][3]);
		//currentarray = keytilevalues;
		//solutionarray = keysolution;
		currenttilevector = keytilevectorvalues;
		currenttilevectorsolution = keytilevectorsolution;
	}
			
	if (level == 2)
	{
		//boost::multi_array<int, 2>::extent_gen extents;
		//currentarray.resize(extents[6][6]);
		//currentarray = suntilevalues;
		//solutionarray = sunsolution;
		currenttilevector = suntilevectorvalues;
		currenttilevectorsolution = suntilevectorsolution;
	}
	
}