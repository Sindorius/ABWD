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
	if (level == 5)
	{

		currenttilevector = keytilevectorvalues;
		currenttilevectorsolution = keytilevectorsolution;
		whichplayertilesvector = keyplayertilesvector;
		drytilevector = keydrytilesvector;

	}
}