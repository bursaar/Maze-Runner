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

Serialise::~Serialise()
{
}
