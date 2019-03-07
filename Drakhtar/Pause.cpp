#include "Pause.h"



Pause::Pause(SDL_Renderer* renderer) : GameState(renderer), renderer_(renderer)
{
	_preload();
}


Pause::~Pause()
{
}

void Pause::_preload()
{
	//Resume = new Button(TextureManager::get("Button-Play"), WIN_WIDTH / 2, 250, 200, 75, Play_game, game_, renderer_);
	Resume = new Button(TextureManager::get("Button-Play"), WIN_WIDTH / 2, 250, 200, 75,resumeGame, renderer_);
	gameObjectsPause_.push_back(Resume);
	//Options = new Button(TextureManager::get("Button-Options"), WIN_WIDTH / 2, 350, 200, 75, Options_game, game_, renderer_);
	Options = new Button(TextureManager::get("Button-Options"), WIN_WIDTH / 2, 350, 200, 75, optionsGame,renderer_);
	gameObjectsPause_.push_back(Options);
}

void Pause::_render()
{
	// Render each game object
	for (auto gameObject : gameObjectsPause_)
		gameObject->render();

	// Render the new frame
	SDL_RenderPresent(renderer_);
}

void Pause::_handleEvents(SDL_Event & e)
{
	Resume->handleEvents(e);
	Options->handleEvents(e);
}

void Pause::resumeGame( SDL_Renderer* renderer)
{
	cout << "Play";
}

void Pause::optionsGame(SDL_Renderer* renderer)
{
	cout << "Options";
}
