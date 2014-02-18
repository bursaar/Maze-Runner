#pragma once
#include <fstream>
#include <string>
#include <iostream>
#include <stdio.h>
#include "nodes.h"

using namespace std;

class Serialise
{
public:
	// Constructors
	Serialise();
	Serialise(bool pLevel[338]);				// Overloaded constructor for passing in a level data object.

	// Enums
	enum FILETYPES { LEVEL };					// Different file types. Right now, there's only LEVEL(0).
	enum MODES { LOAD, SAVE };					// Different modes - LOAD(0) aka read and SAVE(1) aka write.
	enum ENTITIES { PLAYER, ENEMY, GOAL};		// Different types of entities in the game.

	// ==== - MEMBER VARIABLES - ==== //
		
		int mode = LOAD;
		int type = LEVEL;

		// Setting filenames and extensions
		string mExtension;						// Set extension manually. It will be set by the member functions by default.
		string mFilename;						// Set filename. When called by a member function it will automatically append the correct file extension.

		// Data populated by calling member functions. 
		bool mLoadedLevel[338];

		// Data populated manually for saving to files.
		bool mSavedLevel[338];

		// Data for either loading or saving
		gridloc mGl_player;
		gridloc mGl_enemy;
		gridloc mGl_goal;

	// ==== - MEMBER FUNCTOINS - ==== //

		void Save(int pType);
		void Load(int pType);
//		void Positions(string pInput, int pEntity);

		~Serialise();

private:
	void LoadLevel();
//	int NumberInString(string pInput);
};

