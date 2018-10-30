#include "Cell.h"

Cell::Cell(int row, int col): mRow(row), mCol(col) 
{
	character = '\0';
}

void Cell::setChar(int val) 
{
	character = val;
}

void Cell::paint() 
{
	std::cout<<character<<"\t";
}