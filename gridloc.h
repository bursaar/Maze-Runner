#pragma once

#include <iostream>

using namespace std;


// GRIDLOC
// The grid location type – a co-ordinate type used when
// defining location of an object within a maze. A simple
// cartesian co-ordinate.

struct gridloc {
	int xloc;										// X location
	int yloc;										// Y location
	gridloc();										// Default constructor
	gridloc(int pX, int pY);
	void gridloc::printLoc(gridloc location);
};