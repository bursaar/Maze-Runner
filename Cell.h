//
//  Cell.h
//  Maze Runner
//
//  Created by Ben Keenan on 06/01/2014.
//  Copyright (c) 2014 Ben Keenan. All rights reserved.
//

#ifndef __Maze_Runner__Cell__
#define __Maze_Runner__Cell__


#include "nodes.h"

using namespace std;

class cCell {

public:
    int index;						// Unique register.
    int state;						// Contents - passable (0) or solid (1)
	int gValue;						// Movement cost to move from the starting point to this one. 
	int hValue;						// Heuristic cost - distance
	int fValue;						// Sum of movement cost + heuristic cost
	bool checked = false;			// Has it been checked by the pathfinder?
	cCell *parent;					// Pointer to the parent cell
	gridloc mGl_location;			// Location on the map.
    
	// Assign the instance of the cell an index and a state.
	void setCell(int pCellIndex, int pCellState);

};


//===============================================================================================
// Functions that exist outside of the class but are useful for operations involving the class
// or similar.
//===============================================================================================

// PRINT CO-ORDS
// Pass a four-element array of grid locations and get an on-screen printout of the array.
void PrintCoOrds(gridloc list[4]);

#endif /* defined(__Maze_Runner__Cell__) */
