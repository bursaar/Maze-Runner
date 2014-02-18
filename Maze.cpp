#include "Maze.h"


cMaze::cMaze(const bool gencode[338])
{

	// We set the initial variables:
	int xindex;             // This is the X co-ordinate in the 2D array of cells.
	int yindex = 0;         // This is given a starting value of zero that will be augmented within the yindex while loop.
	int genindex = 0;       // This is the index of the element to be pulled from the gencode.
	int cellindex = 0;      // Each cell has its own index, this is provided in case it's useful for pathfinding later.


	// Now we create two nested while loops to create pairs of lines (yindex)
	// from 0 & 1 up to 24 & 25. We won't be printing or using line 25 (the 26th line).

	while (yindex < 26) {

		xindex = 0;     // This is set to 0 to start us off at the beginning and givs us a starting point for our yindex loop.

		// First we set the top left cell of the line pair.
		mCurrentMaze[xindex][yindex].setCell(cellindex, i_cellBlocked);

		// Advance the cell index to make sure the next cell is given the right index.
		cellindex++;

		xindex++;    // At the start of each yindex loop we advance right by one and then run the xindex loop.

		while (xindex < 24) {

			// Is the xindex position odd or even? For the method called, zero is the same as even.

			if (oddOrEven(xindex) == 1){
				//**IF THE xindex IS ODD**
				// We create the generated cell with the right element from the gencode.
				mCurrentMaze[xindex][yindex].setCell(cellindex, gencode[genindex]);

				// Then we advance the genindex by one, to make sure the next one taken from the gencode is the right one.
				genindex++;

				// We advance the cell's index by one.
				cellindex++;

				// Then we fill in the cell to the bottom left of this one.
				mCurrentMaze[xindex - 1][yindex + 1].setCell(cellindex, gencode[genindex]);

				// Then we advance the genindex by one again, to make sure the next one taken from the gencode is the right one.
				genindex++;

				// We advance the cell's index by one.
				cellindex++;

				// We move to the next cell on the right.
				xindex++;

			}
			else{
				//**IF THE xindex IS NOT ODD (i.e. even or zero)**
				// We create the generated cell with the right element based on the grid's structure.
				mCurrentMaze[xindex][yindex].setCell(cellindex, i_cellBlocked);

				// We advance the cell's index by one.
				cellindex++;

				// We now leave the xindex as it is, but create the right cell to the bottom left, diagonally.
				mCurrentMaze[xindex - 1][yindex + 1].setCell(cellindex, i_cellGap);

				// We advance the cell's index by one.
				cellindex++;

				// We move to the next cell to the right.
				xindex++;

			}

		}

		// This leaves us out of the X loop, so we perform a little end of line assignment and carriage return.
		// We create the generated cell with the right element based on the grid's structure.
		mCurrentMaze[xindex][yindex].setCell(cellindex, i_cellBlocked);

		// We advance the cell's index by one.
		cellindex++;

		// We now leave the xindex as it is, but create the next cell to the bottom left, diagonally.
		mCurrentMaze[xindex - 1][yindex + 1].setCell(cellindex, i_cellOpen);

		// We advance the cell's index by one.
		cellindex++;

		// We move right by one.
		xindex++;

		// Assign a value from the gencode.
		mCurrentMaze[xindex][yindex].setCell(cellindex, gencode[genindex]);

		// Advance the index by one:
		cellindex++;

		// Advance the genindex by one:
		genindex++;

		// Move again to the last assigned cell of this line pair.
		xindex--;    // Move left one...
		yindex++;    // ...and down one.

		// Assign a value from the gencode.
		mCurrentMaze[xindex][yindex].setCell(cellindex, gencode[genindex]);

		// Advance the index by one:
		cellindex++;

		// Advance the genindex by one:
		genindex++;

		// Move down to the next line
		yindex++;
	}

	return;
}


// ===============================================================
// Print Maze - Print the maze to the screen.
// ===============================================================

void cMaze::print()
{
		int xpos = 0;   // Create a variable to track the x axis
		int ypos = 0;   // Create a variable to track the y axis

		// Next is a while loop that prints one horizontal line at a time, moving
		// down the grid vertically as each lines completes, left to right.

		while (ypos < 25) {

			// First it runs another while loop that prints from left to right.

			while (xpos < 25) {

				// It takes the current X & Y co-ordinates and prints the state, followed by a space,

				cout << mCurrentMaze[xpos][ypos].state << " ";

				// Then it increments the X co-ordinate by one and loops again, moving to the next one on the right.

				xpos++;
			}

			// Once the X loop has gone all the way to the right, it attempts to go one more, then jumps out to this point.

			// Here we print a carriage return
			cout << endl;

			// Then we reset the X co-ordinate to 0 to start us off again on the left.
			xpos = 0;

			// Then we increment the Y co-ordinate by one and loop again, being caught by the X loop again.
			ypos++;
		}

		return;
}