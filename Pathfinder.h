#pragma once
#include "Cell.h"
#include "gridloc.h"
#include "Maze.h"
#include <algorithm>
#include <vector>

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
	const enum enemyMovement {ENEMYUP, ENEMYRIGHT, ENEMYDOWN, ENEMYLEFT};

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

	int CalculateH(gridloc pGl_playerPos, gridloc pGl_enemyPos);	// Overloaded version that takes arguments of current/proposed locations.
	gridloc NextMove();
	// void CalculateF(int pIndex = 0);
	
private: 
	// ==============================
	// Private member variables
	// ==============================

	const enum gVal { NODEOPEN = 10, NODECLOSED = 500 };
	cCell node_start;				// The enemy's current position
	cCell node_goal;				// The player's current position
	cCell node_current;				// The node currently being evaluated


	// Open and closed lists for pathfinding algorithm
	// cCell cell_nodeList_open[625];					// Open list of nodes
	// cCell cell_nodeList_closed[625];				// Closed list of nodes

	vector<cCell> cell_nodeList_open;
	vector<cCell> cell_nodeList_closed;
	
	bool swapflag;
	
	// ===============================
	// Calculate current H value
	// ===============================
	// void CalculateH(bool print = 0);
	// void CalculateG(bool print = 0);
	// void NodesOpenToClosed(int &pClosedListIndex, gridloc pPosToCheck, gridloc pPosCheckFrom, int pFlag);
	// void SetInitialValues(bool print = 0);

	// Bubble sort function - taken from the example in T2G Developer S1PB, Lesson 7, Page 107
	// void SortNodesByFValue(int index = 0);
	void SortOpenList(int index = 0);
};