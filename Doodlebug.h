#pragma once

#include "Game.h"
#include "Organism.h"
#include "Ant.h"


#include <iostream>
#include <vector>
#include<string>


//using namespace type_def;
using namespace std;



class Doodlebug : public Organism
{
private:
	int starveTimer;
	int breedTimeCount;

	vector<int> validMovesToAnts(int x, int y)const;

public:
	Doodlebug() :Organism(), starveTimer(0) {}
	Doodlebug(GamePtr currGame, int x, int y);
	bool starve() { return starveTimer == 0; }
	void move();
	void breed();
	int organismType() { return 2; }

};
