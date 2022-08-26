#pragma once

#include "Game.h"
#include "Organism.h"
#include "Ant.h"
#include "Doodlebug.h"



class Organism {

public:
	typedef Game* GamePtr;
	Organism() :currGame(nullptr), x(0), y(0), breedTimer(0), stepCount(0) {}
	Organism(GamePtr currGame, int x, int y);
	virtual void breed() = 0;
	virtual void move();
	virtual bool starve() { return false; }
	virtual int organismType() = 0;

protected:
	GamePtr currGame;
	int x;
	int y;
	int breedTimer;
	int stepCount;
	bool validCoordinate(int x, int y) const;
	vector<int> isMoveFree(int x, int y) const;
	void testCoordinate(int& x, int& y, int move) const;
};

