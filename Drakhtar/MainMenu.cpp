#include "MainMenu.h"

MainMenu::MainMenu(Game* game, SDL_Renderer* renderer) : GameState(game,renderer), game_(game)
{
}


MainMenu::~MainMenu()
{
	for (auto gameObject : gameObjects_)
		delete gameObject;
	game_ = nullptr;
}

void MainMenu::_preload()
{
	Play = new Button(TextureManager::get("Button-Play"), 200, 200, 150, 50, Play_game, game_);
	gameObjects_.push_back(Play);
}

void MainMenu::Play_game(Game * game)
{
	cout << "Play";
}
