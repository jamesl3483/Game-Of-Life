#pragma once
#include "Organism.h"
#include "Ant.h"
#include "Doodlebug.h"

const int griddim = 20;

class Game
{
	friend class Organism;
	friend class Doodlebug;
	friend class Ant;

public:
	typedef Organism* OrganismPtr;

	Game();
	void startGame();
	void nextStepCount();
	void printGrid() const;
private:
	OrganismPtr worldGrid[griddim][griddim];
	int stepCount = 0;
	int RandNum(int start, int end) const;

};

