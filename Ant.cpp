#include "Ant.h"


Ant::Ant(GamePtr currGame, int x, int y) :Organism(currGame, x, y)
{
	breedTimer = antBreedingTime;
}

void Ant::breed() {
	if (breedTimer > 0) return;
	vector<int> validMoves = isMoveFree(x, y);
	if (validMoves.size() == 0) return;
	int randomMove = validMoves[currGame->RandNum(0, validMoves.size() - 1)];
	int newX = x;
	int newY = y;
	testCoordinate(newX, newY, randomMove);
	currGame->worldGrid[newX][newY] = new Ant(currGame, newX, newY);
	breedTimer = antBreedingTime;
}