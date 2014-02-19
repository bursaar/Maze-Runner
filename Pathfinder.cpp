#include "Pathfinder.h"


void cPathfinder::create(cMaze m_MazeToMap, gridloc pGl_playerPos, gridloc pGl_enemyPos, gridloc pGl_goalPos)

{
	// We set the initial variables:
	int xindex = 0;             // This is the X co-ordinate in the 2D array of cells.
	int yindex = 0;			    // This is given a starting value of zero that will be augmented within the yindex while loop.
	int cellindex = 0;		    // Each node has its own index, this is provided in case it's useful for pathfinding later.

	// Now we create two nested while loops to create pairs of lines (yindex)
	// from 0 & 1 up to 24 & 25. We won't be printing or using line 25 (the 26th line).

	while (yindex < 25)
	{
		while (xindex < 25)
		{
			switch (m_MazeToMap.mCurrentMaze[xindex][yindex].state)
			{
			case 0:
				cell_currentNodeMap[xindex][yindex].state = 0;
				cell_currentNodeMap[xindex][yindex].index = cellindex;
				cell_nodeList_open[cellindex] = cell_currentNodeMap[xindex][yindex];
				cellindex++;
				break;

			case 1:
				cell_currentNodeMap[xindex][yindex].state = 1;
				cell_currentNodeMap[xindex][yindex].index = cellindex;
				cell_nodeList_open[cellindex] = cell_currentNodeMap[xindex][yindex];
				cellindex++;
				break;

			case 3:
				cell_currentNodeMap[xindex][yindex].state = 0;
				cell_currentNodeMap[xindex][yindex].index = cellindex;
				cell_nodeList_open[cellindex] = cell_currentNodeMap[xindex][yindex];
				cellindex++;
				break;

			case 4:
				cell_currentNodeMap[xindex][yindex].state = 1;
				cell_currentNodeMap[xindex][yindex].index = cellindex;
				cell_nodeList_open[cellindex] = cell_currentNodeMap[xindex][yindex];
				cellindex++;
				break;
			}

			xindex++;

		}

		xindex = 0;
		yindex++;


	}

	// Assign positions

	// Player:
	mGl_playerPos.xloc = pGl_playerPos.xloc;
	mGl_playerPos.yloc = pGl_playerPos.yloc;
	// Enemy:
	mGl_enemyPos.xloc = pGl_enemyPos.xloc;
	mGl_enemyPos.yloc = pGl_enemyPos.yloc;
	// Goal:
	mGl_goalPos.xloc = pGl_goalPos.xloc;
	mGl_goalPos.yloc = pGl_goalPos.yloc;

	CalculateH();

	return;

}

void cPathfinder::LookAround(gridloc gl_whereAmI, gridloc(&gl_clearToMove)[4]) {

	/*
	The idea here is to give the function a variable and an array.

	It will calculate where around the gl_whereAmI is free to move
	and will pass the answers by reference to a user-supplied
	2 x 2 array (N, E, S, W) which will essentially contain the next
	legal moves available to the player.

	N	[0]
	E	[1]
	S	[2]
	W	[3]

	If the element contains the origin (0, 0) then it is considered blank.

	*/

	if (cell_currentNodeMap[gl_whereAmI.xloc][gl_whereAmI.yloc - 1].state == 0)		//North check (0, -1) to go into [0]
	{
		gl_clearToMove[0].xloc = gl_whereAmI.xloc;
		gl_clearToMove[0].yloc = gl_whereAmI.yloc - 1;
	}
	else {
		gl_clearToMove[0].xloc = 0;
		gl_clearToMove[0].yloc = 0;
	}

	if (cell_currentNodeMap[gl_whereAmI.xloc + 1][gl_whereAmI.yloc].state == 0)		//East check (1, 0) to go into [1]
	{
		gl_clearToMove[1].xloc = gl_whereAmI.xloc + 1;
		gl_clearToMove[1].yloc = gl_whereAmI.yloc;
	}
	else {
		gl_clearToMove[1].xloc = 0;
		gl_clearToMove[1].yloc = 0;
	}

	if (cell_currentNodeMap[gl_whereAmI.xloc][gl_whereAmI.yloc + 1].state == 0)		//South check (0, +1) to go into [2]
	{
		gl_clearToMove[2].xloc = gl_whereAmI.xloc;
		gl_clearToMove[2].yloc = gl_whereAmI.yloc + 1;
	}
	else {
		gl_clearToMove[2].xloc = 0;
		gl_clearToMove[2].yloc = 0;
	}

	if (cell_currentNodeMap[gl_whereAmI.xloc - 1][gl_whereAmI.yloc].state == 0)		//West check (-1, 0) to go into [3]
	{
		gl_clearToMove[3].xloc = gl_whereAmI.xloc - 1;
		gl_clearToMove[3].yloc = gl_whereAmI.yloc;
	}
	else {
		gl_clearToMove[3].xloc = 0;
		gl_clearToMove[3].yloc = 0;
	}

	{

	}


}

void cPathfinder::Print(bool b_printLabel) {
	int xpos = 0;   // Create a variable to track the x axis
	int ypos = 0;   // Create a variable to track the y axis

	// If the argument 1 is passed, it prints a label, otherwise it remains unwritten.
	if (b_printLabel = 1) {
		cout << "Node Map." << endl;
	}

	// Next is a while loop that prints one horizontal line at a time, moving
	// down the grid vertically as each lines completes, left to right.

	while (ypos < 25) {

		// First it runs another while loop that prints from left to right.

		while (xpos < 25) {

			// It takes the current X & Y co-ordinates and prints the state, followed by a space,

			cout << cell_currentNodeMap[xpos][ypos].state << " ";

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

// Calculate the current H-Value
void cPathfinder::CalculateH(bool print)
{
	for (int y = 0; y < 25; y++)
	{
		for (int x = 0; x < 25; x++)
		{
			gridloc currentLoc(x, y);
			int xdiff = currentLoc.xloc - mGl_enemyPos.xloc;
			int ydiff = currentLoc.yloc - mGl_enemyPos.yloc;
			if (xdiff < 0) { xdiff *= -1; }
			if (ydiff < 0) { ydiff *= -1; }
			cell_nodeList_open[(x * 25) + y].hValue = xdiff + ydiff;
		}
	}

	if (print == 1)
	{
		// Enable for debugging
		cout << "Open nodelist: " << endl;
		for (int cellindex = 0; cellindex < 625; cellindex++)
		{
			cout
				<< "Hval: "
				<< cell_nodeList_open[cellindex].hValue
				<< ", "
				<< cell_nodeList_open[cellindex].index
				<< ", Fval: "
				<< cell_nodeList_open[cellindex].fValue
				<< ", State: "
				<< cell_nodeList_open[cellindex].state
				<< endl;
		}
	}
}

// Overload for calculating the current H value, takes argument of gridloc positions.
void cPathfinder::CalculateH(gridloc pGl_playerPos, gridloc pGl_enemyPos, gridloc pGl_goalPos, bool print)
{

	// Assign positions

	// Player:
	mGl_playerPos.xloc = pGl_playerPos.xloc;
	mGl_playerPos.yloc = pGl_playerPos.yloc;
	// Enemy:
	mGl_enemyPos.xloc = pGl_enemyPos.xloc;
	mGl_enemyPos.yloc = pGl_enemyPos.yloc;
	// Goal:
	mGl_goalPos.xloc = pGl_goalPos.xloc;
	mGl_goalPos.yloc = pGl_goalPos.yloc;

	for (int y = 0; y < 25; y++)
	{
		for (int x = 0; x < 25; x++)
		{
			gridloc currentLoc(x, y);
			int xdiff = currentLoc.xloc - mGl_enemyPos.xloc;
			int ydiff = currentLoc.yloc - mGl_enemyPos.yloc;
			if (xdiff < 0) { xdiff *= -1; }
			if (ydiff < 0) { ydiff *= -1; }
			cell_nodeList_open[(x * 25) + y].hValue = xdiff + ydiff;
		}
	}

	if (print == 1)
	{
		// Enable for debugging
		cout << "Open nodelist: " << endl;
		for (int cellindex = 0; cellindex < 625; cellindex++)
		{
			cout
				<< "Hval: "
				<< cell_nodeList_open[cellindex].hValue
				<< ", "
				<< cell_nodeList_open[cellindex].index
				<< ", Fval: "
				<< cell_nodeList_open[cellindex].fValue
				<< ", State: "
				<< cell_nodeList_open[cellindex].state
				<< endl;
		}
	}
}

// Overload for calculating the current H value, takes argument of gridloc positions.
void cPathfinder::CalculateH(gridloc pGl_playerPos, gridloc pGl_enemyPos, bool print)
{

	// Assign positions

	// Player:
	mGl_playerPos.xloc = pGl_playerPos.xloc;
	mGl_playerPos.yloc = pGl_playerPos.yloc;
	// Enemy:
	mGl_enemyPos.xloc = pGl_enemyPos.xloc;
	mGl_enemyPos.yloc = pGl_enemyPos.yloc;

	for (int y = 0; y < 25; y++)
	{
		for (int x = 0; x < 25; x++)
		{
			gridloc currentLoc(x, y);
			int xdiff = currentLoc.xloc - mGl_enemyPos.xloc;
			int ydiff = currentLoc.yloc - mGl_enemyPos.yloc;
			if (xdiff < 0) { xdiff *= -1; }
			if (ydiff < 0) { ydiff *= -1; }
			cell_nodeList_open[(x * 25) + y].hValue = xdiff + ydiff;
		}
	}

	if (print == 1)
	{
		// Enable for debugging
		cout << "Open nodelist: " << endl;
		for (int cellindex = 0; cellindex < 625; cellindex++)
		{
			cout
				<< "Hval: "
				<< cell_nodeList_open[cellindex].hValue
				<< ", "
				<< cell_nodeList_open[cellindex].index
				<< ", Fval: "
				<< cell_nodeList_open[cellindex].fValue
				<< ", State: "
				<< cell_nodeList_open[cellindex].state
				<< endl;
		}
	}
}


gridloc cPathfinder::NextMove(gridloc pFrom, gridloc pTo)
{
	// Default grid reference for return of member function,
	// (0, 0) cannot be a valid gridloc value, so it is a failstate.
	gridloc gl_default(0, 0);

	CalculateH(pFrom, pTo);

	const enum gVal { NODEOPEN = 10, NODECLOSED = 500 };

	gridloc gl_up = gl_default;
	gridloc gl_right = gl_default;
	gridloc gl_down = gl_default;
	gridloc gl_left = gl_default;

	if (pFrom.yloc > 0)	{ gridloc gl_up(pFrom.xloc, (pFrom.yloc - 1)); }
	if (pFrom.xloc < 25) { gridloc gl_right(pFrom.xloc + 1, pFrom.yloc); }
	if (pFrom.yloc < 25) { gridloc gl_down(pFrom.xloc, pFrom.yloc + 1); }
	if (pFrom.xloc > 0) { gridloc gl_left(pFrom.xloc - 1, pFrom.yloc); }

	int openListIndex = 0;
	int closedListIndex = 0;

	// Check the state of the cell above
	if (gl_up.xloc != 0 && gl_up.yloc != 0)
	{
		switch (cell_nodeList_open[(gl_up.yloc * 25) + gl_up.xloc].state)
		{
		case 0:	// Is the node open?
		{
					NodesOpenToClosed(closedListIndex, gl_up, pFrom, NODEOPEN);
		} break;
		case 1:	// Is the node closed?
		{
					NodesOpenToClosed(closedListIndex, gl_up, pFrom, NODECLOSED);
		} break;
		}
	}

	// Check the state of the cell to the right
	if (gl_right.xloc != 0 && gl_right.yloc != 0)
	{
		switch (cell_nodeList_open[(gl_right.yloc * 25) + gl_right.xloc].state)
		{
		case 0:	// Is the node open?
		{
					NodesOpenToClosed(closedListIndex, gl_right, pFrom, NODEOPEN);
		} break;
		case 1:	// Is the node closed?
		{
					NodesOpenToClosed(closedListIndex, gl_right, pFrom, NODECLOSED);
		} break;
		}
	}

	// Check the state of the cell below
	if (gl_down.xloc != 0 && gl_down.yloc != 0)
	{
		switch (cell_nodeList_open[(gl_down.yloc * 25) + gl_down.xloc].state)
		{
		case 0:	// Is the node open?
		{
					NodesOpenToClosed(closedListIndex, gl_up, pFrom, NODEOPEN);
		} break;
		case 1:	// Is the node closed?
		{
					NodesOpenToClosed(closedListIndex, gl_up, pFrom, NODECLOSED);
		} break;
		}
	}

	// Check the state of the cell below
	if (gl_left.xloc != 0 && gl_left.yloc != 0)
	{
		switch (cell_nodeList_open[(gl_left.yloc * 25) + gl_left.xloc].state)
		{
		case 0:	// Is the node passable?
		{
					NodesOpenToClosed(closedListIndex, gl_left, pFrom, NODEOPEN);
		} break;
		case 1:	// Is the node blocked?
		{
					NodesOpenToClosed(closedListIndex, gl_left, pFrom, NODECLOSED);
		} break;
		}
	}




	cout << "Error returned from cPathfinder::NextMove();" << endl;
	return gl_default;
}


void cPathfinder::NodesOpenToClosed(int &pClosedListIndex, gridloc pPosToCheck, gridloc pPosCheckFrom, int pFlag)
{
	cell_nodeList_closed[pClosedListIndex] = cell_nodeList_open[(pPosToCheck.yloc * 25) + pPosToCheck.xloc];
	cell_nodeList_closed[pClosedListIndex].gValue = pFlag;
	if (cell_nodeList_open[(pPosToCheck.yloc * 25) + pPosToCheck.xloc].gValue > 0)
	{
		cell_nodeList_closed[pClosedListIndex].gValue += cell_nodeList_open[(pPosToCheck.yloc * 25) + pPosToCheck.xloc].gValue;
	}
	cell_nodeList_closed[pClosedListIndex].parent = &cell_nodeList_closed[(pPosCheckFrom.yloc * 25) + pPosCheckFrom.xloc];
	pClosedListIndex++;
	return;
}

void cPathfinder::SortNodesByFValue(int index)
{
	cCell tempcell;
	if (index == 625)							// Does this need to be 624
	{
		if (swapflag == false)
		{
			return;
		}

		index = 0;
		swapflag = false;
	}

	if (cell_nodeList_open[index].fValue > cell_nodeList_open[index + 1].fValue)
	{
		tempcell = cell_nodeList_open[index];
		cell_nodeList_open[index] = cell_nodeList_open[index + 1];
		cell_nodeList_open[index + 1] = tempcell;
		swapflag = true;
	}
	SortNodesByFValue(index + 1);
}