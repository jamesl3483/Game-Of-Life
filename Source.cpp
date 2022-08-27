#include <iostream>
#include <vector>
#include<string>


using namespace std;

class Game;
class Organism;
class Doodlebug;
class Ant;

//moves
/*
const int up = 1;
const int right = 2;
const int down = 3;
const int left = 4;
*/



const int doodleStarveTime = 3; //starve time of doodlebug
const int doodleBreedTimer = 8; //Doodlebug breeding time

const int antBreedTimer = 3; //Ant breeding time


const int griddim = 20;
typedef Organism* OrganismPtr;
typedef Game* GamePtr;

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
	void nextStepCount();
	void printGrid();
	void startGame();

};


class Organism {

protected:
	GamePtr currGame;
	int x;
	int y;
	int breedTimeCount;
	int stepCount;
	bool validCoordinate(int x, int y) const;
	void testCoordinate(int& x, int& y, int move) const;
	vector<int> isMoveFree(int x, int y);
public:
	Organism() :currGame(nullptr), x(0), y(0), breedTimeCount(0), stepCount(0) {}
	Organism(GamePtr currGame, int x, int y);
	virtual void breed() = 0;
	virtual void move();
	virtual bool starve() { return false; }
	virtual int organismType() = 0;
};



class Ant :public Organism
{
public:
	Ant() :Organism() {}
	Ant(GamePtr currGame, int x, int y);
	void breed();
	int organismType() { return 1; } //1 is an ant
private:
	int breedTimeCount;

};

class Doodlebug : public Organism
{
private:
	int starveTimer;
	int breedTimeCount;

public:
	Doodlebug() :Organism(), starveTimer(0) {}
	Doodlebug(GamePtr currGame, int x, int y);
	vector<int> validMovesToAnts(int x, int y)const;
	bool starve() { return starveTimer == 0; }
	void move();
	void breed();
	int organismType() { return 2; }

};




Game::Game()
{
	srand(time(NULL));
	//print grid
	for (int x = 0; x < griddim; x++)
	{
		for (int y = 0; y < griddim; y++)
		{
			worldGrid[x][y] = nullptr;
		}
	}
}

void Game::startGame() {
	int x, y;
	int doodlebugs = 0;
	int ants = 0;
	while (doodlebugs < 5)
	{
		x = RandNum(0, griddim - 1);
		y = RandNum(0, griddim - 1);
		if (worldGrid[x][y] != nullptr) continue;
		worldGrid[x][y] = new Doodlebug(this, x, y);

		doodlebugs++;
	}
	while (ants < 100)
	{
		x = RandNum(0, griddim - 1);
		y = RandNum(0, griddim - 1);
		if (worldGrid[x][y] != nullptr) continue;

		worldGrid[x][y] = new Ant(this, x, y);

		ants++;
	}

}


void Game::nextStepCount() {
	stepCount++;
	//organismType: 1 = Ants, 2 = Doodlebug
	//Doodlebug move
	for (int x = 0; x < griddim; x++)
	{
		for (int y = 0; y < griddim; y++)
		{
			if (worldGrid[x][y] == nullptr) continue;
			if (worldGrid[x][y]->organismType() == 2)
				worldGrid[x][y]->move();
		}
	}

	//Ants move
	for (int x = 0; x < griddim; x++)
	{
		for (int y = 0; y < griddim; y++)
		{
			if (worldGrid[x][y] == nullptr) continue;
			if (worldGrid[x][y]->organismType() == 1)
				worldGrid[x][y]->move();

		}
	}

	//breed
	for (int x = 0; x < griddim; x++)
	{
		for (int y = 0; y < griddim; y++)
		{
			if (worldGrid[x][y] == nullptr) continue;
			worldGrid[x][y]->breed();
		}
	}

	//Starve
	for (int x = 0; x < griddim; x++)
	{
		for (int y = 0; y < griddim; y++)
		{
			if (worldGrid[x][y] == nullptr) continue;
			if (worldGrid[x][y]->starve()) {
				delete worldGrid[x][y];
				worldGrid[x][y] = nullptr; 
			}

		}
	}

}

int Game::RandNum(int start, int end) const {
	return rand() % (end - start + 1) + start;
}

void Game::printGrid() {
	for (int x = 0; x < griddim; x++)
	{
		for (int y = 0; y < griddim; y++)
		{
			if (worldGrid[x][y] == nullptr)
				cout << '-';
			else if (worldGrid[x][y]->organismType() == 1)
				cout << 'o';
			else
				cout << 'X';

		}
		cout << "\n";
	}


}




Organism::Organism(GamePtr currGame, int x, int y) {
	this->currGame = currGame;
	this->x = x;
	this->y = y;
	stepCount = currGame->stepCount;
	breedTimeCount = 0;
}

void Organism::move() {
	if (stepCount == currGame->stepCount) return;
	stepCount++;
	int randomMove = currGame->RandNum(1, 4);
	int newX = x;
	int newY = y;
	testCoordinate(newX, newY, randomMove);
	if (validCoordinate(newX, newY)) {
		if (currGame->worldGrid[newX][newY] != nullptr) return;
		currGame->worldGrid[x][y] = nullptr;
		currGame->worldGrid[newX][newY] = this;
		x = newX;
		y = newY;
	}

}

void Organism::testCoordinate(int& x, int& y, int move) const  {
	/*
	const int up = 1;
	const int right = 2;
	const int down = 3;
	const int left = 4;
	*/
	if (move == 1) y++;
	if (move == 2) x++;
	if (move == 3) y--;
	if (move == 4) x--;

}

vector<int> Organism::isMoveFree(int x, int y)  {
	vector<int> setOfMoves;
	int tempX, tempY;
	for (int move = 1; move <= 4; move++) {
		tempX = x;
		tempY = y;
		testCoordinate(tempX, tempY, move);
		if (!validCoordinate(tempX, tempY)) continue;
		if (currGame->worldGrid[tempX][tempY] == nullptr) {
			setOfMoves.push_back(move);
		}
	}
	return setOfMoves;
}

bool Organism::validCoordinate(int x, int y) const {
	if (x < 0 || x >= griddim || y<0 || y >= griddim) {
		return false;
	}
	return true;
}

Ant::Ant(GamePtr currGame, int x, int y) :Organism(currGame, x, y)
{
	breedTimeCount = antBreedTimer;
}

void Ant::breed() {
	breedTimeCount--;
	if (breedTimeCount > 0) return;
	vector<int> validMoves = isMoveFree(x, y);
	if (validMoves.size() == 0) return;
	int randomMove = validMoves[currGame->RandNum(0, validMoves.size() - 1)];
	int newX = x;
	int newY = y;
	testCoordinate(newX, newY, randomMove);
	currGame->worldGrid[newX][newY] = new Ant(currGame, newX, newY);
	breedTimeCount = antBreedTimer;
}





Doodlebug::Doodlebug(GamePtr currGame, int x, int y) :Organism(currGame, x, y)
{
	starveTimer = doodleStarveTime;
	breedTimeCount = doodleBreedTimer;
}

vector<int> Doodlebug::validMovesToAnts(int x, int y) const {
	vector<int> setOfMoves;
	int tempX, tempY;
	for (int move = 1; move <= 4; move++) {
		tempX = x;
		tempY = y;
		testCoordinate(tempX, tempY, move);
		if (!validCoordinate(tempX, tempY)) continue;
		if (currGame->worldGrid[tempX][tempY] == nullptr) continue;
		if (currGame->worldGrid[tempX][tempY]->organismType() == 1)
			setOfMoves.push_back(move);

	}
	return setOfMoves;
}

void Doodlebug::move() {
	if (stepCount == currGame->stepCount) return;
	vector<int> antEatingMove = validMovesToAnts(x, y);
	if (antEatingMove.size() == 0) {
		Organism::move();
		starveTimer--;
		return;
	}
	stepCount++;
	starveTimer = doodleStarveTime;
	int randomMove = antEatingMove[currGame->RandNum(0, antEatingMove.size() - 1)];
	// coordinate of the ant
	int newX = x;
	int newY = y;
	testCoordinate(newX, newY, randomMove);
	delete currGame->worldGrid[newX][newY];
	currGame->worldGrid[newX][newY] = this;
	currGame->worldGrid[x][y] = nullptr;
	x = newX;
	y = newY;
}

void Doodlebug::breed() {
	breedTimeCount--;
	if (breedTimeCount > 0) return;
	vector<int> validMoves = isMoveFree(x, y);
	if (validMoves.size() == 0) return;
	int randomMove = validMoves[currGame->RandNum(0, validMoves.size() - 1)];
	int newX = x;
	int newY = y;
	testCoordinate(newX, newY, randomMove);
	currGame->worldGrid[newX][newY] = new Doodlebug(currGame, newX, newY);
	breedTimeCount = doodleBreedTimer;
}


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

}



