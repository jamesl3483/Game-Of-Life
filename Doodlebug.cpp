#include "Doodlebug.h"




Doodlebug::Doodlebug(GamePtr currGame, int x, int y) :Organism(currGame, x, y)
{
	starveTimer = doodleStarveTime;
	breedTimeCount = doodleBreedTimer;
}

vector<int> Doodlebug::validMovesToAnts(int x, int y) const {
	vector<int> setOfMoves;
	int tempX, tempY;
	for (int move = 1; move <= 4; move++) {
		tempX = x;
		tempY = y;
		testCoordinate(tempX, tempY, move);
		if (!validCoordinate(tempX, tempY)) continue;
		if (currGame->worldGrid[tempX][tempY] == nullptr) continue;
		if (currGame->worldGrid[tempX][tempY]->organismType() == 1)
			setOfMoves.push_back(move);

	}
	return setOfMoves;
}

void Doodlebug::move() {
	if (stepCount == currGame->stepCount) return;
	vector<int> antEatingMove = validMovesToAnts(x, y);
	if (antEatingMove.size() == 0) {
		Organism::move();
		starveTimer--;
		return;
	}
	stepCount++;
	starveTimer = doodleStarveTime;
	int randomMove = antEatingMove[currGame->RandNum(0, antEatingMove.size() - 1)];
	// coordinate of the ant
	int newX = x;
	int newY = y;
	testCoordinate(newX, newY, randomMove);
	delete currGame->worldGrid[newX][newY];
	currGame->worldGrid[newX][newY] = this;
	currGame->worldGrid[x][y] = nullptr;
	x = newX;
	y = newY;
}

void Doodlebug::breed() {
	breedTimeCount--;
	if (breedTimeCount > 0) return;
	vector<int> validMoves = isMoveFree(x, y);
	if (validMoves.size() == 0) return;
	int randomMove = validMoves[currGame->RandNum(0, validMoves.size() - 1)];
	int newX = x;
	int newY = y;
	testCoordinate(newX, newY, randomMove);
	currGame->worldGrid[newX][newY] = new Doodlebug(currGame, newX, newY);
	breedTimeCount = doodleBreedTimer;
}