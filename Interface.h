//
//  Interface.h
//  Maze Runner
//
//  Created by Ben Keenan on 06/01/2014.
//  Copyright (c) 2014 Ben Keenan. All rights reserved.
//

#ifndef __Maze_Runner__interface__
#define __Maze_Runner__interface__

#include <iostream>

using namespace std;

// This is a cleaner, tidier way of doing multiple line jumps. The default argument is 1, but a blank list ( ) must still be included.
void SkipLine(int linesToSkip = 1){		

	// Loop the lines to skip down to 1
	while (linesToSkip > 0)
	{
		cout << endl;
		linesToSkip--;
	}

	return;

}


#endif /* defined(__Maze_Runner__interface__) */
