#pragma once
#include "Game.h"
#include "Organism.h"
#include "Doodlebug.h"

const int antBreedingTime = 3; //Ant breeding time


class Ant :
    public Organism
{
private:


public:
	Ant() :Organism() {}
	Ant(GamePtr currGame, int x, int y);
	void breed();
	int organismType() { return 1; } //1 is an ant
};

