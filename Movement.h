#pragma once
#include "Pathfinder.h"

enum MOVEMENT { NONE, UP, RIGHT, DOWN, LEFT };

// Movement controller
int int_movement = NONE;
int int_enemyMovement = NONE;
bool bl_freeToMove = true;
bool bl_enemyFreeToMove = true;

// Function to help clip to array co-ordinates
bool TestForCollision(int pX, int pY, cPathfinder pNodes, SDL_Rect pRect, int pDirection)
{
	switch (pDirection)
	{
	case RIGHT:
	{
				  int newX = pX;
				  int newY = pY;
				  newX = (pX + pRect.w) / pRect.w;
				  newY = (pY) / pRect.h;
				  bl_freeToMove = true;
				  int_movement = NONE;
				  return !(bool)pNodes.cell_currentNodeMap[newX][newY].state; }
		break;


	case UP:
	{
			   int newX = pX;
			   int newY = pY;
			   newX = (pX) / pRect.w;
			   newY = (pY - pRect.h) / pRect.h;
			   bl_freeToMove = true;
			   int_movement = NONE;
			   return !(bool)pNodes.cell_currentNodeMap[newX][newY].state; }
		break;

	case DOWN:
	{		int newX = pX;
	int newY = pY;

	newX = (pX) / pRect.w;
	newY = (pY + pRect.h) / pRect.h;
	bl_freeToMove = true;
	int_movement = NONE;
	return !(bool)pNodes.cell_currentNodeMap[newX][newY].state; }
		break;

	case LEFT:
	{		int newX = pX;
	int newY = pY;

	newX = (pX - pRect.w) / pRect.w;
	newY = (pY) / pRect.h;
	bl_freeToMove = true;
	int_movement = NONE;
	return !(bool)pNodes.cell_currentNodeMap[newX][newY].state; }
		break;
	}

	return 0;
}