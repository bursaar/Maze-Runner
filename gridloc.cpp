#include "gridloc.h"

gridloc::gridloc()										// Default constructor
{

}

gridloc::gridloc(int pX, int pY)							// Overloaded constructor that assigns the X and Y
{
	xloc = pX;
	yloc = pY;
}

void gridloc::printLoc(gridloc location) {		// Print location to the console
	cout << "(";

	cout << location.xloc << ", " << location.yloc;

	cout << ")";

	return;
}