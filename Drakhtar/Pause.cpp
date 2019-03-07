#include "Pause.h"



Pause::Pause(SDL_Renderer* renderer) : GameState(renderer), renderer_(renderer)
{
}


Pause::~Pause()
{
}

void Pause::_preload()
{
	Resume = new Button(TextureManager::get("Button-Play"), WIN_WIDTH / 2, 250, 200, 75, Play_game, game_, renderer_);
	Options = new Button(TextureManager::get("Button-Options"), WIN_WIDTH / 2, 350, 200, 75, Options_game, game_, renderer_);
}

void Pause::_render()
{
	Resume->render();
	Options->render();
}

void Pause::Play_game(Game * game, SDL_Renderer* renderer)
{
	cout << "Play";
}

void Pause::Options_game(Game * game, SDL_Renderer* renderer)
{
	cout << "Options";
}
