#include "Cell.h"

// Note the default constructor, it's important for the
// Maze class to be able to create a 26 x 26 grid of empty
// cells.

void cCell::setCell(int pCellIndex, int pCellState)
{
	index = pCellIndex;
	state = pCellState;
}


bool cCell::operator<(const cCell& other)
{
	if (fValue < other.fValue)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool cCell::operator>(const cCell& other)
{
	if (fValue > other.fValue)
	{
		return true;
	}
	else
	{
		return false;
	}
}


void PrintCoOrds(gridloc list[4])
{
	int xlist = 0;

	while (xlist < 4)
	{
		cout << "(" << list[xlist].xloc << ", " << list[xlist].yloc << ")" << endl;
		xlist++;
	}

}