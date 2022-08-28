#pragma once
#include "Organism.h"
#include "Ant.h"
#include "Doodlebug.h"

#include <iostream>
#include <vector>
#include<string>

using namespace std;


extern const int griddim = 20;

class Game
{
	friend class Organism;
	friend class Doodlebug;
	friend class Ant;

private:

typedef Organism* OrganismPtr;
	OrganismPtr worldGrid[griddim][griddim];
	int stepCount = 0;
	int RandNum(int start, int end) const;

public:
	Game();
	void startGame();
	void nextStepCount();
	void printGrid() const;

};

