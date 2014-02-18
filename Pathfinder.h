#pragma once
#include "Cell.h"
#include "gridloc.h"
#include "Maze.h"

class cPathfinder
{
public:

	/*
	===	Member Variables ===
	*/

	cCell cell_currentNodeMap[25][25];
	gridloc	mGl_playerPos;
	gridloc mGl_enemyPos;
	gridloc mGl_goalPos;

	/*
	===	Member Functions ===
	*/

	//==========================================================================================================
	// CREATE NODE MAP
	// Create the nodemap given an argument of an exsiting generated maze.
	// The current workflow would be:
	// Create maze object -> Populate maze from serialised gencode -> Create pathfinding layer
	void create(cMaze m_MazeToMap, gridloc pGl_playerPos, gridloc pGl_enemyPos, gridloc pGl_goalPos);

	//========================================================================================================== 
	// LOOK AROUND																								
	// This function will return a gridloc array with a maximum of four elements. These (max) four locations	
	// are the only legal moves left to the entity in the given cell.											
	//==========================================================================================================
	void LookAround(gridloc gl_whereAmI, gridloc(&gl_clearToMove)[4]);

	//==========================================================================================================
	// PRINT MAZE
	// Print the maze to the screen. Pass an argument of 1 to print a label on the nodemap.
	//==========================================================================================================
	void Print(bool b_printLabel = 0);

	void CalculateH(gridloc pGl_playerPos, gridloc pGl_enemyPos, bool print = 0);	// Overloaded version that takes arguments of current/proposed locations.
	void CalculateH(gridloc pGl_playerPos, gridloc pGl_enemyPos, gridloc pGl_goalPos, bool print = 0);	// Overloaded version that takes arguments of current/proposed locations, incl. goal
	gridloc NextMove(gridloc pFrom, gridloc pTo);
	
private: 
	// ==============================
	// Private member variables
	// ==============================

	// Open and closed lists for pathfinding algorithm
	cCell cell_nodeList_open[625];					// Open list of nodes
	cCell cell_nodeList_closed[625];				// Closed list of nodes
	
	// ===============================
	// Calculate current H value
	// ===============================
	void CalculateH(bool print = 0);
};