#include "Playfield.h"

Playfield::Playfield(int pBoardSize):boardSize(pBoardSize) 
{	
	// Initialize cells
	cells.resize(boardSize, std::vector<Cell*>(boardSize, nullptr));
	for(int i=0; i<boardSize*boardSize; i++) {
		cells[i/boardSize][i%boardSize] = new Cell(i/boardSize, i%boardSize);
	}

	std::cout<<"Playfield of size "<<boardSize<<"x"<<boardSize<<" is created"<<std::endl;
}

void Playfield::update(int row, int col, char val)
{
	cells[row][col]->setChar(val);
}

void Playfield::paint() 
{
	for(int i=0; i<boardSize; i++) {
		for(int j=0; j<boardSize; j++) {
			cells[i][j]->paint();	
		}
		std::cout<<std::endl;
	}
}

Playfield::~Playfield()
{
	for(int i=0; i<boardSize*boardSize; i++)
		delete cells[i/boardSize][i%boardSize];
	cells.clear();
}