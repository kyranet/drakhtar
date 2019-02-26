#pragma once

#include "State.h"
#include "Controller.h"

State::State(Game* game, SDL_Renderer* renderer)
	: GameState(game,renderer), game_(game)
{
}

State::~State()
{
	for (auto gameObject : gameObjects_)
		delete gameObject;
	game_ = nullptr;
}

void State::_preload()
{
	// TextureManager
	gameObjects_.push_back(new GameObject(TextureManager::get("Maps-FirstBattle"), Vector2D<int>(WIN_WIDTH / 2, WIN_HEIGHT / 2), Vector2D<int>(WIN_WIDTH, WIN_HEIGHT)));

	// Board
	Board * Tablero = new Board(TextureManager::get("UI-cellFrame"), 8, 12, 50);
	gameObjects_.push_back(new GameObject(TextureManager::get("Maps-FirstBattle"), Vector2D<int>(WIN_WIDTH / 2, WIN_HEIGHT / 2), Vector2D<int>(WIN_WIDTH, WIN_HEIGHT)));
    gameObjects_.push_back(Tablero);
	
	// Test units
	Box * box = Tablero->getBoxAt(0, 0);
	Box * box2 = Tablero->getBoxAt(5, 5);
	Unit * test = new Unit(TextureManager::get("Units-BlueArcher"), box, 2, 10, 5, 5, 5);
	Unit * test2 = new Unit(TextureManager::get("Units-BlueArcher"), box2, 2, 10, 5, 5, 5);
	gameObjects_.push_back(test);
	gameObjects_.push_back(test2);

	Prueba = new Button(TextureManager::get("Units-Abeizhul"), 200, 200, 200, 200, startGame, game_);
	gameObjects_.push_back(Prueba);
	auto exampleDialog = new DialogScene(game_, "dialog1_start", "Retron2000");
	gameObjects_.push_back(exampleDialog);
}

void State::startGame(Game* game) {
	cout << "Boton on";
}

void State::_handleEvents(SDL_Event& e)
{
	/*if (event.type == SDL_KEYDOWN && (event.key.keysym.sym == SDLK_ESCAPE || event.key.keysym.sym == SDLK_s))
		while (!SDL_PollEvent(&e)) {
			Prueba->handleEvents(e);
			if (event.type == SDL_KEYDOWN) {
				switch (event.key.keysym.sym)
				{
				case SDLK_ESCAPE:
					cout << "save";
					break;
				}
			}
			GameState::_handleEvents(e);
		}	*/
	while (!_exit && SDL_PollEvent(&e))
	{
		Prueba->handleEvents(e);

		if (event.type == SDL_KEYDOWN) {
			switch (event.key.keysym.sym)
			{
			case SDLK_e:
				cout << "Pause";
				break;
			}
		}

		// For each game object, run the event handler
		for (auto gameObject : gameObjects_)
			gameObject->handleEvents(e);

		GameState::_handleEvents(e);
	}
}

void State::addGameObject(GameObject* gameObject)
{
	gameObjects_.push_back(gameObject);
}

void State::removeGameObject(GameObject* gameObject)
{
	pendingOnDestroy_.push_back(gameObject);	
}
