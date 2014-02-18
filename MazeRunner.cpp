#include "Movement.h"
#include "Serialise.h"
#include "DefaultValues.h"

int main(int argn, char * args[])
{
	/*
	// Serialisation test/demo //
	Serialise Saver(DefaultCode);
	Saver.mFilename = "LevelOneTest";
	Saver.mGl_player.xloc = 1;
	Saver.mGl_player.yloc = 0;
	Saver.mGl_enemy.xloc = 15;
	Saver.mGl_enemy.yloc = 7;
	Saver.mGl_goal.xloc = 15;
	Saver.mGl_goal.yloc = 0;
	Saver.Save(Serialise::LEVEL);
	*/

	Serialise Loader;
	Loader.mFilename = "LevelOneTest";
	Loader.Load(Serialise::LEVEL);

	cMaze MazeOne(Loader.mLoadedLevel);						// Creates a maze instance from the loaded level.
	cPathfinder PathOne;									// Creates a pathfinder instance from the maze instance.
	PathOne.create(MazeOne, Loader.mGl_player, Loader.mGl_enemy, Loader.mGl_goal);								// Populates the nodemap for the pathfinding instance.

	// Load sprites as SDL surfaces
	SDL_Surface * spr_cells = SDL_LoadBMP("../Sprites/redsquare.bmp");
	SDL_Surface * spr_player = SDL_LoadBMP("../Sprites/bluesquare.bmp");
	SDL_Surface * spr_goal = SDL_LoadBMP("../Sprites/goal.bmp");
	SDL_Surface * spr_enemy = SDL_LoadBMP("../Sprites/enemy.bmp");
	
	// Create window with render surface
	SDL_Init(SDL_INIT_VIDEO);
	SDL_Window * window = SDL_CreateWindow("Train2Game Developer Course Portfolio 1 Project 2 - Ben Keenan | CD9000002O", 50, 80, spr_cells->w * 25, spr_cells->h * 25, SDL_WINDOW_SHOWN);
	SDL_Surface * renderSurface = SDL_GetWindowSurface(window);

	// Set up variables for event pipe
	SDL_Event event;
	bool quit = false;
	enum GAMESTATES { LOSE, PLAYING, WIN, QUIT };
	GAMESTATES gamestate = PLAYING;

	// Assign values for the player.
	gridloc gl_player = Loader.mGl_player;
	float fl_playerX = gl_player.xloc * spr_cells->w;
	float fl_playerY = gl_player.yloc * spr_cells->w;

	// Assign values for the enemy.
	gridloc gl_enemy = Loader.mGl_enemy;
	float fl_enemyX = gl_enemy.xloc * spr_enemy->w;
	float fl_enemyY = gl_enemy.yloc * spr_enemy->h;

	// Assign values for the goal.
	gridloc gl_goal = Loader.mGl_goal;
	float fl_goalX = gl_goal.xloc * spr_goal->w;
	float fl_goalY = gl_goal.yloc * spr_goal->h;

	// Assign variables to track the timing of the updates
	float fl_lastFrameTime = 0.0f;
	fl_lastFrameTime = SDL_GetTicks();

	//	float speed = 50.0f;			// TODO - Remove line


	// =========================== //
	//			Main loop	       //
	// =========================== //

	while (!quit)
	{
		// ============ //
		//  DRAW STAGE  //
		// ============ //

		// Temporary!! TODO fix blit solution
		SDL_FillRect(renderSurface, NULL, 0xffffffff);

		// Draw out maze from nodemap
		for (int y = 0; y < 25; y++)
		{
			for (int x = 0; x < 25; x++)
			{
				if (MazeOne.mCurrentMaze[x][y].state == cMaze::CLOSED || MazeOne.mCurrentMaze[x][y].state == cMaze::BLOCKED)
				{
					SDL_Rect rect_cells;

					rect_cells.x = x * spr_cells->w;
					rect_cells.y = y * spr_cells->h;
					rect_cells.w = spr_cells->w;
					rect_cells.h = spr_cells->h;

					SDL_BlitSurface(spr_cells, NULL, renderSurface, &rect_cells);
				}
			}
		}

		// Draw player
		SDL_Rect rect_player;
		rect_player.h = spr_player->h;
		rect_player.w = spr_player->w;
		rect_player.x = (int)fl_playerX;
		rect_player.y = (int)fl_playerY;

		// Draw enemy
		SDL_Rect rect_enemy;
		rect_enemy.h = spr_enemy->h;
		rect_enemy.w = spr_enemy->w;
		rect_enemy.x = (int)fl_enemyX;
		rect_enemy.y = (int)fl_enemyY;

		// Draw goal
		SDL_Rect rect_goal;
		rect_goal.h = spr_goal->h;
		rect_goal.w = spr_goal->w;
		rect_goal.x = (int)fl_goalX;
		rect_goal.y = (int)fl_goalY;

		SDL_BlitSurface(spr_player, NULL, renderSurface, &rect_player);
		SDL_BlitSurface(spr_enemy, NULL, renderSurface, &rect_enemy);
		SDL_BlitSurface(spr_goal, NULL, renderSurface, &rect_goal);

		SDL_UpdateWindowSurface(window);


		// ============ //
		//    UPDATE    //
		// ============ //

		float fl_newFrameTime = SDL_GetTicks();
		float fl_timeSinceLastFrame = ((fl_newFrameTime - fl_lastFrameTime) / 1000.0f);	// The time the graphics update took, measured in seconds.

		// Hard clamping.
		if (fl_playerX < 0)
		{
			fl_playerX = 0.0f;
		}
		if (fl_playerY < 0)
		{
			fl_playerY = 0.0f;
		}
		if (fl_playerX >(rect_player.w * 25))
		{
			fl_playerX = (rect_player.w * 24);
		}
		if (fl_playerY > (rect_player.h * 25))
		{
			fl_playerY = (rect_player.h * 24);
		}


		// Keyboard input //
		const Uint8 * KeyboardState = SDL_GetKeyboardState(NULL);


			if (int_movement == NONE && bl_freeToMove)
			{
				if (KeyboardState[SDL_SCANCODE_RIGHT] || KeyboardState[SDL_SCANCODE_D])
				{
					int_movement = RIGHT;
				}
				if (KeyboardState[SDL_SCANCODE_DOWN] || KeyboardState[SDL_SCANCODE_S])
				{
					int_movement = DOWN;
				}
				if (KeyboardState[SDL_SCANCODE_LEFT] || KeyboardState[SDL_SCANCODE_A])
				{
					int_movement = LEFT;
				}
				if (KeyboardState[SDL_SCANCODE_UP] || KeyboardState[SDL_SCANCODE_W])
				{
					int_movement = UP;
				}
			}
			
				if (int_movement == UP
					&& fl_playerY > 0												
					&& TestForCollision((int)fl_playerX, (int)fl_playerY, PathOne, rect_player, UP)
					)								
				{
					fl_playerY -= rect_player.h;						// Up
					int_movement = NONE;
					bl_freeToMove = false;
					gridloc gl_playerCurrentPos((fl_playerX / rect_player.w), (fl_playerY / rect_player.h));
					PathOne.CalculateH(gl_playerCurrentPos, gl_enemy, gl_goal);
				}

				if (int_movement == RIGHT
					&& fl_playerX < (rect_player.w * 25)
					&& TestForCollision((int)fl_playerX, (int)fl_playerY, PathOne, rect_player, RIGHT)
					)																	
				{
					fl_playerX += rect_player.w;							// Right
					int_movement = NONE;
					bl_freeToMove = false;
					gridloc gl_playerCurrentPos((fl_playerX / rect_player.w), (fl_playerY / rect_player.h));
					PathOne.CalculateH(gl_playerCurrentPos, gl_enemy, gl_goal);
				}

				if (int_movement == DOWN
					&& fl_playerY < (rect_player.h * 25)
					&& TestForCollision((int)fl_playerX, (int)fl_playerY, PathOne, rect_player, DOWN)
					)								
				{
					fl_playerY += rect_player.h;						// Down
					int_movement = NONE;
					bl_freeToMove = false;
					gridloc gl_playerCurrentPos((fl_playerX / rect_player.w), (fl_playerY / rect_player.h));
					PathOne.CalculateH(gl_playerCurrentPos, gl_enemy, gl_goal);
				}

				if (int_movement == LEFT
					&& fl_playerX > 0
					&& TestForCollision((int)fl_playerX, (int)fl_playerY, PathOne, rect_player, LEFT)
					)								
				{
					fl_playerX -= rect_player.w;						// Left
					int_movement = NONE;
					bl_freeToMove = false;
					gridloc gl_playerCurrentPos((fl_playerX / rect_player.w), (fl_playerY / rect_player.h));
					PathOne.CalculateH(gl_playerCurrentPos, gl_enemy, gl_goal);
				}
			

			if (
				!KeyboardState[SDL_SCANCODE_UP]
				&& !KeyboardState[SDL_SCANCODE_W]
				&& !KeyboardState[SDL_SCANCODE_RIGHT]
				&& !KeyboardState[SDL_SCANCODE_D]
				&& !KeyboardState[SDL_SCANCODE_DOWN]
				&& !KeyboardState[SDL_SCANCODE_S]
				&& !KeyboardState[SDL_SCANCODE_LEFT]
				&& !KeyboardState[SDL_SCANCODE_A]
				)
			{
				bl_freeToMove = true;
			}


			// Check if player and enemy are colliding.
			if (fl_playerX == fl_enemyX
				&& fl_playerY == fl_enemyY)
			{
				gamestate = LOSE;
			}

			if (fl_playerX == fl_goalX
				&& fl_playerY == fl_goalY)
			{
				gamestate = WIN;
			}


			if (KeyboardState[SDL_SCANCODE_ESCAPE])
			{
				gamestate = QUIT;
			}

		fl_lastFrameTime = fl_newFrameTime;


		// Check for changes in the state of the game.
		switch (gamestate)
		{
		case LOSE:
		{
						quit = true;
		}
			break;
		case PLAYING:
		{
						quit = false;
		}
			break;
		case WIN:
		{
						quit = true;
		}
			break;
		case QUIT:
		{
					 quit = true;
		}
		}

		// ============ //
		//    EVENTS    //
		// ============ //

		while (SDL_PollEvent(&event) != 0)

		{
			if (event.type == SDL_QUIT)
			{
				quit = true;
			}
		}

	}

	SDL_Quit();

	return 0;
}