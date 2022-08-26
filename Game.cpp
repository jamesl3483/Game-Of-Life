#include <iostream>
#include <vector>
#include<string>

#include "Game.h"
#include "Organism.h"
#include "Ant.h"
#include "Doodlebug.h"
using namespace std;
using namespace std;

Game::Game()
{
	//print grid
	for (int x = 0; x < griddim; x++)
	{
		for (int y = 0; y < griddim; y++)
		{
			worldGrid[x][y] = nullptr;
		}
	}
}

void Game::startGame() {
	int x, y;
	int doodlebugs = 0;
	int ants = 0;
	while (doodlebugs < 5)
	{
		x = RandNum(0, griddim - 1);
		y = RandNum(0, griddim - 1);
		if (worldGrid[x][y] != nullptr)
		{
			worldGrid[x][y] = new Doodlebug(this, x, y);
		}
		doodlebugs++;
	}
	while (ants < 100)
	{
		x = RandNum(0, griddim - 1);
		y = RandNum(0, griddim - 1);
		if (worldGrid[x][y] != nullptr)
		{
			worldGrid[x][y] = new Ant(this, x, y);
		}
		ants++;
	}

}


void Game::nextStepCount() {
	stepCount++;
	//organismType: 1 = Ants, 2 = Doodlebug
	//Doodlebug move
	for (int x = 0; x < griddim; x++)
	{
		for (int y = 0; y < griddim; y++)
		{
			if (worldGrid[x][y] == nullptr) continue;
			if (worldGrid[x][y]->organismType() == 2)
				worldGrid[x][y]->move();
		}
	}

	//Ants move
	for (int x = 0; x < griddim; x++)
	{
		for (int y = 0; y < griddim; y++)
		{
			if (worldGrid[x][y] == nullptr) continue;
			if (worldGrid[x][y]->organismType() == 1)
				worldGrid[x][y]->move();
		}
	}

	//breed
	for (int x = 0; x < griddim; x++)
	{
		for (int y = 0; y < griddim; y++)
		{
			if (worldGrid[x][y] == nullptr) continue;
			worldGrid[x][y]->breed();
		}
	}

	//Starve
	for (int x = 0; x < griddim; x++)
	{
		for (int y = 0; y < griddim; y++)
		{
			if (worldGrid[x][y] == nullptr) continue;
			if (worldGrid[x][y]->starve())
				worldGrid[x][y] = nullptr; //should I delete worldGrid to reset it?

		}
	}

}

int Game::RandNum(int start, int end) const {
	return rand() % (end - start + 1) + start;
}

void Game::printGrid() const {
	for (int x = 0; x < griddim; x++)
	{
		for (int y = 0; y < griddim; y++)
		{
			if (worldGrid[x][y] == nullptr)
				cout << '-';
			if (worldGrid[x][y]->organismType() == 1)
				cout << 'o';
			if (worldGrid[x][y]->organismType() == 2)
				cout << 'X';

		}
	}


}