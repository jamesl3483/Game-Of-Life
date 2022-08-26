#pragma once
#include "Organism.h"


class Game
{
	friend class Organism;
	friend class Doodlebug;
	friend class Ant;
private:
	OrganismPtr worldGrid[griddim][griddim];
	int stepCount = 0;
	int RandNum(int start, int end) const;

public:
	Game();
	void startGame();
	void nextStepCount();
	void printGrid() const;

};

