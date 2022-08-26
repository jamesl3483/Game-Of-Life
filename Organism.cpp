#include "Organism.h"

#include <iostream>
#include <vector>
#include<string>

#include "Game.h"
#include "Ant.h"
#include "Doodlebug.h"
using namespace std;

Organism::Organism(GamePtr currGame, int x, int y) {
	this->currGame = currGame;
	this->x = x;
	this->y = y;
	breedTimer = 0;
	stepCount = currGame->stepCount;
}

void Organism::move() {
	if (stepCount == currGame->stepCount) return;
	stepCount++;
	breedTimer--;
	int randomMove = currGame->RandNum(1, 4);
	int newX = x;
	int newY = y;
	testCoordinate(newX, newY, randomMove);
	if (validCoordinate(newX, newY)) {
		if (currGame->worldGrid[newX][newY] != nullptr) return;
		currGame->worldGrid[x][y] = nullptr;
		currGame->worldGrid[newX][newY] = this;
		x = newX;
		y = newY;
	}

}

vector<int> Organism::isMoveFree(int x, int y) const {
	vector<int> setOfMoves;
	int tempX, tempY;
	for (int move = 1; move <= 4; move++) {
		tempX = x;
		tempY = y;
		testCoordinate(tempX, tempY, move);
		if (!validCoordinate(tempX, tempY)) continue;
		if (currGame->worldGrid[tempX][tempY] == nullptr) {
			setOfMoves.push_back(move);
			cout << "valid" << endl;
		}
	}
	return setOfMoves;
}

bool Organism::validCoordinate(int x, int y) const {
	if (x > 0 || x < griddim || y>0 || y < griddim) {
		return true;
	}
	return false;
}

void Organism::testCoordinate(int& x, int& y, int move) const {
	/*
	const int up = 1;
	const int right = 2;
	const int down = 3;
	const int left = 4;
	*/
	if (move == 1) y++;
	if (move == 2) x++;
	if (move == 3) y--;
	if (move == 4) x--;

}