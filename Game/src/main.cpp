#include "Game/Game.h"

int main()
{
	game::Game* newGame = new game::Game();
	newGame->Run();
	delete newGame;

	return 0;
}