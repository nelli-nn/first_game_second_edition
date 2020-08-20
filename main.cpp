#include "Project.h"
#include "Game.h"

int main()
{
	std::srand(static_cast<unsigned int>(time(nullptr)));
	Game game;
	game.Run();
	return 0;
}