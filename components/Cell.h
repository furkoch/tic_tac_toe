#ifndef CELL_H
#define CELL_H

#include <iostream>

class Cell {

public:
	Cell(int row, int col);
	
	inline int getRow() const { return mRow; }
	inline int getCol() const { return mCol; }

	void setChar(int val);

	void paint();

private:
	int mRow;
	int mCol;
	char character;
};

#endif