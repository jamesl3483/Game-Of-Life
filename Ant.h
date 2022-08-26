#pragma once
#include "Organism.h"
class Ant :
    public Organism
{
public:
	Ant() :Organism() {}
	Ant(GamePtr currGame, int x, int y);
	void breed();
	int organismType() { return 1; } //1 is an ant
};

