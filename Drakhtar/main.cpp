
#include "SDL.h"
#include "SDL_image.h"
#include "Game.h"
#include "checkML.h"
#include <iostream>

using namespace std;

int main(int argc, char* argv[]){
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF); // Check Memory Leaks
	try
	{
		Game *game = new Game();
		game->run();
		delete game;
		return 0;
	}
	catch (exception e)
	{
		cout << e.what();
		return -1;
	}
}