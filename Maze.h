//
//  Maze.h
//  Maze Runner
//
//  Created by Ben Keenan on 06/01/2014.
//  Copyright (c) 2014 Ben Keenan. All rights reserved.
//

#ifndef __Maze_Runner__Maze__
#define __Maze_Runner__Maze__

#include "Cell.h"
#include "nodes.h"

using namespace std;

class cMaze {
public:
	cMaze(const bool gencode[338]);	// Constructor

	void MazeMaker(const bool gencode[338]);

	// The UI title of the maze, if applicable.
	char title[25];

	// Was the maze generated (0) automatically or loaded
	// from a saved (1) state?
	enum state { generated, saved };
    
    // 0 = generated, 1 = saved
	state origin;
    
	// The gendode used to generate the maze, a 338-digit long binary sequence.
	bool gencode[338];

	cCell mCurrentMaze[26][26];          // Creates a maze of a particular size.
    
	FILE * mCurrentFile;	// The current file being read from.

	void print();

	// The contents of the cell; open(0), closed(1), gap(3), blocked(4)
	enum CONTENTS { OPEN, CLOSED, GAP = 3, BLOCKED };

private:
    
	// The limit for the conditional to catch the algorithm if it goes over the edge of the grid.
	static const int overflowLimit = 27;
													    
 
	/*
		These are the static numerical definitions of the different states of each
		cell.
	*/

    static const int i_cellOpen = 0;
    static const int i_cellClosed = 1;
    static const int i_cellGap = 3;
    static const int i_cellBlocked = 4;

// ===============================================================
// Odd or even?
// Checks whether an int passed is odd or even. 0 = even, 1 = odd
// ===============================================================
    
    bool oddOrEven(int check) {
        if (check % 2 == 0 || check == 0) {
            return 0;
        };
        
        return 1;
    };
    
// ===============================================================
// Print Maze Indicies - Print the maze's index to the screen.
// Useful for debugging.
// ===============================================================

void printIndex() {
    int xpos = 0;   // Create a variable to track the x axis
    int ypos = 0;   // Create a variable to track the y axis
    
    
    
    // Next is a while loop that prints one horizontal line at a time, moving
    // down the grid vertically as each lines completes, left to right.
    
    while (ypos < 25) {
        
        // First it runs another while loop that prints from left to right.
        
        while (xpos < 25) {
            
            // It takes the current X & Y co-ordinates and prints the state, followed by a space,
            
            cout<<mCurrentMaze[xpos][ypos].index<<" ";
            
            // Then it increments the X co-ordinate by one and loops again, moving to the next one on the right.
            
            xpos++;
        }
        
        // Once the X loop has gone all the way to the right, it attempts to go one more, then jumps out to this point.
        
        // Here we print a carriage return
        cout<<endl;
        
        // Then we reset the X co-ordinate to 0 to start us off again on the left.
        xpos = 0;
        
        // Then we increment the Y co-ordinate by one and loop again, being caught by the X loop again.
        ypos++;
    }
    
    return;
}
    
    // ===================================================================================
    // Print Maze To Solve - Print the maze to the screen in a solveable, presentable way.
    // ===================================================================================
    
    void printToSolve() {
        int xpos = 0;   // Create a variable to track the x axis
        int ypos = 0;   // Create a variable to track the y axis
        
        
        
        // Next is a while loop that prints one horizontal line at a time, moving
        // down the grid vertically as each lines completes, left to right.
        
        while (ypos < 25) {
            
            // First it runs another while loop that prints from left to right.
            
            while (xpos < 25) {
                
                // It takes the current X & Y co-ordinates and prints the state, followed by a space,
                
                switch (mCurrentMaze[xpos][ypos].state)
                {
                    case 3:
                        cout<<" ";
                        break;
                        
                    case 0:
                        cout<<" ";
                        break;
                        
                    case 4:
                        cout<<"X";
                        break;
                        
                    case 1:
                        cout<<"X";
                        break;
                }
                
                cout<<" ";
                
                // Then it increments the X co-ordinate by one and loops again, moving to the next one on the right.
                
                xpos++;
            }
            
            // Here we print a carriage return
            cout<<endl;
            
            // Then we reset the X co-ordinate to 0 to start us off again on the left.
            xpos = 0;
            
            // Then we increment the Y co-ordinate by one and loop again, being caught by the X loop again.
            ypos++;
        }
        
        return;
    }

	/*
		Set Title of maze
	*/

	void SetTitle(char newname[25]) {
		strcpy_s(title, newname);
		return;
	}


	/*
		Create new game - passing level by reference.
		Will print by default. Will not print with a 0 included 
		at the end of the argument list.
		Will include title with another one again at the end.
		To get the title without the level printing, 
		include 0, 1 at the end of the list.
	*/
/*	void NewGame(cMaze &thislevel,char newtitle[25], const bool b_gencode[338], bool printToScreen = 1, bool printTitleToScreen = 0) {

		thislevel.SetTitle(newtitle);

		thislevel(b_gencode);

		if (printToScreen == 1)
		{
			if (printTitleToScreen == 1)
			{
				cout << "Title: " << thislevel.title << endl;
			}
			thislevel.printToSolve();
		}

		return;
	}
	*/
};

#endif /* defined(__Maze_Runner__Maze__) */
