#ifndef PLAY_FIELD_H
#define PLAY_FIELD_H

#include <iostream>
#include <vector>
#include "Cell.h"
#include "PlayfieldState.h"

class Playfield {

public:
	Playfield(int boardSize);
	~Playfield();
	void paint();
	void update(int row, int col, char val);

private:
	int boardSize;
	std::vector<std::vector<Cell*>> cells;
};

#endif