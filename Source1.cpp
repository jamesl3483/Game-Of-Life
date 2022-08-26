#include <iostream>
#include <vector>
#include<string>

#include "Game.h"
#include "Organism.h"
#include "Ant.h"
#include "Doodlebug.h"
using namespace std;

//moves
/*
const int up = 1;
const int right = 2;
const int down = 3;
const int left = 4;
*/

const int antBreedingTime = 3; //Ant breeding time


const int doodleStarveTime = 3; //starve time of doodlebug
const int doodlebugBreedingTime = 8; //Doodlebug breeding time


const int griddim = 20;
typedef Organism* OrganismPtr;
typedef Game* GamePtr;





int main() {
	char input;

	Game play;
	play.startGame();
	play.printGrid();
	cin.get(input);
	while (input == '\n')
	{
		play.nextStepCount();
		play.printGrid();
		cin.get(input);

	}

	cout << "hel";
}

//
//
//
