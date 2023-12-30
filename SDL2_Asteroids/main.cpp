#include <cstdio>
#include "Game.h"

/*
* TODO List:
* 
* 1: Some SFX are too loud.
* 2: Game Needs a Score Count.
* 3: Game Needs a Win Condition.
* 4: A Way To Randomize the game a little.
* 5: Duplicated asteroids rotate the same way sometimes
* 6: Tidy up code and add documentation to everything.
*/ 

int main(int argc, char* argv[])
{
	auto game = Game::Getinstance();
	
	if(!game->Init("MTN95-AsteroidsRemake", false))
		printf("Failed to initialize game!");

	game->RunEngine();
	
	game->Clean();
	return 0;
}
