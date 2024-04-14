#include <Game0/G/VGame0.h>

int main()
{	
	Game0* game = new Game0();
	game->Start();
	while (true) 
	{
		game->Update();
	}
}