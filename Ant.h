#pragma once

#include "Game.h"
#include "Organism.h"


#include <iostream>
#include <vector>
#include<string>


using namespace std;




class Ant :
	public Organism
{
private:
	const int antBreedingTime = 3; //Ant breeding time

public:
	Ant(GamePtr currGame, int x, int y):Organism(){}

	void breed();
	int organismType() { return 1; } //1 is an ant
};

