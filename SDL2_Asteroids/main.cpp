#include <cstdio>
#include "Game.h"

int main(int argc, char* argv[])
{
	auto game = Game::Getinstance();
	
	if(!game->Init("MTN95-AsteroidsRemake", false))
		printf("Failed to initialize game!");

	game->RunEngine();
	
	game->Clean();
	return 0;
}
