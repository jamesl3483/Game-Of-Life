#pragma once
#include "Organism.h"
class Doodlebug :
    public Organism
{
private:
	int starveTimer;

public:
	Doodlebug() :Organism(), starveTimer(0) {}
	Doodlebug(GamePtr currGame, int x, int y);
	vector<int> validMovesToAnts(int x, int y)const;
	bool starve() { return starveTimer == 0; }
	void move();
	void breed();
	int organismType() { return 2; }

};

