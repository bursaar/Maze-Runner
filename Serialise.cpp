#include "Serialise.h"

Serialise::Serialise()
{

}

Serialise::Serialise(bool pLevel[338])
{
	mode = LOAD;
	type = LEVEL;

	for (int copyIndex = 0; copyIndex < 338; copyIndex++)
	{
		mSavedLevel[copyIndex] = pLevel[copyIndex];
	}
}

/* void Serialise::LoadLevel(){
	std::ifstream loadedData(mFilename);				// This will only ever be called after mFilename has been combined.
	int arrayIndex = 0;									// Position in the array
	string line;
	if (loadedData.is_open())
	{
		while (getline(loadedData, line))
		{
			if (line == "***")
			{
				return;
			}
			if (line == "0")
			{
				Serialise::mLoadedLevel[arrayIndex] = 0;
				arrayIndex++;
			}
			if (line == "1")
			{
				Serialise::mLoadedLevel[arrayIndex] = 1;
				arrayIndex++;
			}
			if (arrayIndex > 330)
			{
				if (line.find("p", 0))
				{
					Serialise::Positions(line, PLAYER);
				}
				if (line.find("e", 0))
				{
					Serialise::Positions(line, ENEMY);
				}
				if (line.find("g", 0))
				{
					Serialise::Positions(line, GOAL);
				}
			}

		}

		loadedData.close();								// Clean up after loading function.

		return;

	}
}


void Serialise::Positions(string pInput, int pEntity)
{
	switch (pEntity)
	{
	case PLAYER:
	{
				   if (pInput.find("x", 1))
				   {
					   mGl_player.xloc = NumberInString(pInput);
					   cout << "Player - Find X" << pInput << endl;
				   }
				   if (pInput.find("y", 1))
				   {
					   mGl_player.yloc = NumberInString(pInput);
					   cout << "Player - Find Y" << pInput << endl;
				   }
	}
		break;
	case ENEMY:
	{
				   if (pInput.find("x", 1))
				   {
					   mGl_enemy.xloc = NumberInString(pInput);
					   cout << "Enemy - Find X" << pInput << endl;
				   }
				   if (pInput.find("y", 1))
				   {
					   mGl_enemy.yloc = NumberInString(pInput);
					   cout << "Enemy - Find Y" << pInput << endl;
				   }
	}
		break;
	case GOAL:
	{
				   if (pInput.find("x", 1))
				   {
					   mGl_goal.xloc = NumberInString(pInput);
					   cout << "Goal - Find X" << pInput << endl;
				   }
				   if (pInput.find("y", 1))
				   {
					   mGl_goal.yloc = NumberInString(pInput);
					   cout << "Goal - Find Y" << pInput << endl;
				   }
	}
		break;
	}
}
*/

void Serialise::Load(int pType)
{
	switch (pType)
	{
	case LEVEL:
		mExtension = ".lvl";
	}

	mFilename.append(mExtension);

	std::ifstream loadedData(mFilename);

	int arrayIndex = 0;
	int lineIndex = 0;
	string line;
	if (loadedData.is_open())
	{

		while (getline(loadedData, line))				// Takes the line in loadedData, puts that into the line, loops and increases.
		{
			if (line == "***")							// Check for end of file as marked by ***
			{
				return;
			}
			if (line == "LEVEL")						// Set the type of data being loaded
			{
				Serialise::type = LEVEL;
			}
			if (line == "0")							// Check for 0, load a boolean 0 to the array
			{
				mLoadedLevel[arrayIndex] = 0;
				arrayIndex++;
			}
			if (line == "1")							// Check for 1, load a boolean 1 to the array
			{
				mLoadedLevel[arrayIndex] = 1;
				arrayIndex++;
			}
			switch (lineIndex)							// Once we've reached line 340, start checking for positions
			{
			case 345:
			{mGl_goal.yloc = line.find("1"); }
				break;
			case 344:
			{mGl_goal.xloc = line.find("1"); }
				break;
			case 343:
			{mGl_enemy.yloc = line.find("1"); }
				break;
			case 342:
			{mGl_enemy.xloc = line.find("1"); }
				break;
			case 341:
			{mGl_player.yloc = line.find("1"); }
				break;
			case 340:
			{mGl_player.xloc = line.find("1"); }
				break;
			}
			lineIndex++;

		}
	}

	return;
}

void Serialise::Save(int pType)
{
	switch (pType)
	{
	case LEVEL:
		mExtension = ".lvl";
	}

	mFilename.append(mExtension);

	std::fstream savedData(mFilename, std::ios::app);



	if (savedData.is_open())						// Check that file opened properly.
	{
		savedData << "LEVEL" << endl;				// Write the type to the top of the file on the first line and return to the next line.
		int arrayIndex = 0;							// Set first position in the 1D boolean array.
		int lineCount = 0;							// Skipping the first line for the full data write.

		while (lineCount < 339)
		{
			savedData << mSavedLevel[arrayIndex] << endl;
			arrayIndex++;
			lineCount++;
		}
		if (mGl_player.xloc != 0 || mGl_player.yloc != 0)
		{
			int poscount = 0;
			while (poscount < mGl_player.xloc)
			{
				savedData << 0;
				poscount++;
			}
			savedData << 1 << endl;
			poscount = 0;
			while (poscount < mGl_player.yloc)
			{
				savedData << 0;
				poscount++;
			}
			savedData << 1 << endl;
			lineCount += 2;
		}
		if (mGl_enemy.xloc != 0 || mGl_enemy.yloc != 0)
		{
			int poscount = 0;
			while (poscount < mGl_enemy.xloc)
			{
				savedData << 0;
				poscount++;
			}
			savedData << 1 << endl;
			poscount = 0;
			while (poscount < mGl_enemy.yloc)
			{
				savedData << 0;
				poscount++;
			}
			savedData << 1 << endl;
			lineCount += 2;
		}
		if (mGl_goal.xloc != 0 || mGl_goal.yloc != 0)
		{
			int poscount = 0;
			while (poscount < mGl_goal.xloc)
			{
				savedData << 0;
				poscount++;
			}
			savedData << 1 << endl;
			poscount = 0;
			while (poscount < mGl_goal.yloc)
			{
				savedData << 0;
				poscount++;
			}
			savedData << 1 << endl;
			lineCount += 2;
		}
		savedData << "***";					// Writes a *** terminator to the end of the file.
		savedData.close();					// Clean up by closing data stream.
	}
}

/*
int Serialise::NumberInString(string pInput)
{
	string digit;
	digit = str pInput;			
	return stoi(pInput);

}
*/

Serialise::~Serialise()
{
}
