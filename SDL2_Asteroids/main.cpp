#include <cstdio>
#include "Game.h"

/*
* TODO List:
* 2. Implement a Scoring System.
* 3. Define a Victory Condition.
* 4. Incorporate Randomization to The Game.
* 5. Duplicated Asteroids Rotate The Same Direction Sometimes.
* 6. Tidy up code and Add Documentation to Everything.
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
