#pragma once

#include "State.h"
#include "Controller.h"
#include "UnitFactory.h"

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
	
	// Test Teams
	Team * team1 = new Team(Tablero);
	Team * team2 = new Team(Tablero);

	// Test Factory
	UnitFactory * factory = new UnitFactory();
	gameObjects_.push_back(factory->newSoldier(team1, Tablero->getBoxAt(0, 2), 10));
	gameObjects_.push_back(factory->newArcher(team1, Tablero->getBoxAt(0, 3), 10));
	gameObjects_.push_back(factory->newWizard(team1, Tablero->getBoxAt(0, 4), 10));
	gameObjects_.push_back(factory->newKnight(team1, Tablero->getBoxAt(0, 5), 10));
	gameObjects_.push_back(factory->newMonster(team1, Tablero->getBoxAt(0, 6), 10));

	gameObjects_.push_back(factory->newArcher(team2, Tablero->getBoxAt(11, 1), 10));
	gameObjects_.push_back(factory->newArcher(team2, Tablero->getBoxAt(11, 2), 10));
	gameObjects_.push_back(factory->newArcher(team2, Tablero->getBoxAt(11, 3), 10));
	gameObjects_.push_back(factory->newArcher(team2, Tablero->getBoxAt(11, 4), 10));
	gameObjects_.push_back(factory->newArcher(team2, Tablero->getBoxAt(11, 5), 10));
	gameObjects_.push_back(factory->newArcher(team2, Tablero->getBoxAt(11, 6), 10));

	// Turn Bar
	turnBar_ = new TurnBar(team1->getUnitList(), team2->getUnitList());

	auto exampleDialog = new DialogScene(game_, "dialog1_start", "Retron2000");
	gameObjects_.push_back(exampleDialog);
}

void State::_handleEvents(SDL_Event& e)
{
	while (!_exit && SDL_PollEvent(&e))
	{
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
