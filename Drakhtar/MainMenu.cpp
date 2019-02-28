#include "MainMenu.h"



MainMenu::MainMenu(Game* game, SDL_Renderer* renderer) : GameState(game,renderer), game_(game), renderer_(renderer)
{
}


MainMenu::~MainMenu()
{
}

void MainMenu::run()
{
	// Preload the state before running
	
	while (!_exit)
	{
		
		_handleEvents();
		_update();		
		_render();
		
	}
}


void MainMenu::_render() const
{
	// Clear the screen
	SDL_RenderClear(renderer_);

	// Render each game object
	

	// Render the new frame
	SDL_RenderPresent(renderer_);
};

void MainMenu::_update() {};
void MainMenu::_handleEvents()
{
	// Listen to SDL events
	SDL_Event event;
	while (!_exit && SDL_PollEvent(&event))
	{
		// If the event type is quit, change state to GAMEOVER for cleanup
		if (event.type == SDL_QUIT)
		{
			_exit = true;
			// TODO: Change State
		}
		switch (event.key.keysym.sym)
		{
		case SDLK_ESCAPE:
			cout << "Pasar";
			
			break;
		case SDLK_s:
			cout << "save";
			break;
		}
	}
}