#include "Pause.h"



Pause::Pause(SDL_Renderer* renderer) : GameState(renderer), renderer_(renderer)
{
}


Pause::~Pause()
{
}

void Pause::_preload()
{
	gameObjects_.push_back(new GameObject(TextureManager::get("Maps-Test"), Vector2D<int>(WIN_WIDTH / 2, WIN_HEIGHT / 2), Vector2D<int>(WIN_WIDTH, WIN_HEIGHT)));
	Play = new Button(TextureManager::get("Button-Play"), WIN_WIDTH / 2, 250, 200, 75, Play_game, game_, renderer_);
	gameObjects_.push_back(Play);
	Options = new Button(TextureManager::get("Button-Options"), WIN_WIDTH / 2, 350, 200, 75, Options_game, game_, renderer_);
	gameObjects_.push_back(Options);
}

void Pause::Play_game(Game * game, SDL_Renderer* renderer)
{
	cout << "Play";
}

void Pause::Options_game(Game * game, SDL_Renderer* renderer)
{
	cout << "Options";
}
