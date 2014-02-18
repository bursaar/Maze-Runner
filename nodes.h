//
//  nodes.h
//  Maze Runner
//
//  Created by Ben Keenan on 06/01/2014.
//  Copyright (c) 2014 Ben Keenan. All rights reserved.
//

#ifndef __Maze_Runner__nodes__
#define __Maze_Runner__nodes__

#include <iostream>
#include "gridloc.h"

using namespace std;

// === New type definitions === //

// GRIDNODE
// A type for declaring the nodes. This may be refactored later
// into a more complete class structure, but it will suffice for
// now while I'm creating the bubble sort algorithm that will be
// used to sort the f-value of nodes.

class cNode {

public:
    gridloc nodeloc;        // location on the grid
    int hval;               // heuristic value - delta between target & start location
    int gval;               // movement cost - total cost on this node to move over
    int fval;               // "f" value – sum of heuristic cost and movement cost
    bool calc;              // calculated flag – has this instance been calculated? 1 yes, 0 no
    
// ===============================================================
// Calculate the "f" value – the sum of the heuristic cost and the
// movement cost.
// ===============================================================
    int getf(){
        return gval + hval;
    }

// ===============================================================
// Print Node Location – output in text the location of this node
// instance.
// ===============================================================
    void PrintNodeLoc () {
        cout << this -> nodeloc.xloc<<", "<<this -> nodeloc.yloc <<endl;
        
        return;
    }
// ===============================================================
// Sort node list
//
// ===============================================================
    
    
    
};




#endif /* defined(__Maze_Runner__nodes__) */
