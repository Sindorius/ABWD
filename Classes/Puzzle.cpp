#include "Puzzle.hpp"

void Puzzle::changePuzzle(int level)
{

	if (level == -1)
	{
		currenttilevector = keytilevectorvalues;
		currenttilevectorsolution = keytilevectorsolution;
		whichplayertilesvector = keyplayertilesvector;
		drytilevector = keydrytilesvector;
	}
			
	if (level == 1)
	{
		currenttilevector = samtilevectorvalues;
		currenttilevectorsolution = samtilevectorsolution;
		whichplayertilesvector = samplayertilesvector;
		drytilevector = samdrytilesvector;
	}
	if (level == 2)
	{
		currenttilevector = candytilevectorvalues;
		currenttilevectorsolution = candytilevectorsolution;
		whichplayertilesvector = candyplayertilesvector;
		drytilevector = candydrytilesvector;
	}
	if (level == 3)
	{
		currenttilevector = ptertilevectorvalues;
		currenttilevectorsolution = ptertilevectorsolution;
		whichplayertilesvector = pterplayertilesvector;
		drytilevector = pterdrytilesvector;
	}
	if (level == 4)
	{
		currenttilevector = suntilevectorvalues;
		currenttilevectorsolution = suntilevectorsolution;
		whichplayertilesvector = sunplayertilesvector;
		drytilevector = sundrytilesvector;
	}
	totalTiles = currenttilevector.size() * currenttilevector[0].size();
	tilesCompleted = 0;
}

bool Puzzle::checkTile(int x, int y)
{
	if (currenttilevectorsolution[x][y] == currenttilevector[x][y]) {
		return true;
	}
	return false;
}

bool Puzzle::checkTile(int x, int y, int num)
{
	if (currenttilevectorsolution[x][y] == num) {
		return true;
	}
	return false;
}

//OLD IMPLEMENTATION
/*bool Puzzle::isSolved()
{
	OLD IMPLEMENTATION
	for (unsigned int i = 0; i < currenttilevector.size(); i++)
	{
		for (unsigned int j = 0; j < currenttilevector[i].size(); j++)
		{
			if (currenttilevector[i][j] != currenttilevectorsolution[i][j])
			{
				//log(std::to_string(i).c_str());
				//log(std::to_string(j).c_str());
				//log("solution not equal");
				//log(std::to_string(currenttilevector[i][j]).c_str());
				//log(std::to_string(currenttilevectorsolution[i][j]).c_str());
				return false;
			}
		}

	}
	return true;
}*/
