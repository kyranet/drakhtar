#pragma once

#include "State.h"
#include "Controller.h"

State::State(Game* game, SDL_Renderer* renderer)
	: game_(game), renderer_(renderer)
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
	auto Tablero = new Board(TextureManager::get("UI-cellFrame"), 8, 12, 50);
	//auto player = new GameObject(TextureManager::get("Units-BlueArcher"), Vector2D<int>(225, 325), Vector2D<int>(50, 50));
	//player->addEventListener(new Controller(player));
	gameObjects_.push_back(new GameObject(TextureManager::get("Maps-FirstBattle"), Vector2D<int>(WIN_WIDTH / 2, WIN_HEIGHT / 2), Vector2D<int>(WIN_WIDTH, WIN_HEIGHT)));
	//gameObjects_.push_back(player);
	gameObjects_.push_back(Tablero);
	auto box = Tablero->getBoxAt(0, 0);
	auto box2 = Tablero->getBoxAt(5, 5);

	auto exampleDialog = new DialogScene(game_, "dialog1_start", "Retron2000");
	gameObjects_.push_back(exampleDialog);

}

void State::run()
{
	// Preload the state before running
	_preload();

	// The event loop follows this scheme:
	// → Create all pending-to-create game objects
	// → Handle SDL events (provided by SDL's event poll)
	// → Handle updates (updates all game objects of the game)
	// → Handle after updates (called after all the updates have run)
	// → Render all the game objects from the scene
	// → Run all the pending events of this tick from the stack
	// → Destroy all the elements that are pending to destroy
	// Once all tasks are done, exit loop, perform cleanup, and finish
	while (!_exit)
	{
		_create();
		_handleEvents();
		_update();
		_afterUpdate();
		_render();
		_events();
		_destroy();
	}
	_end();
}

void State::_create()
{
	
};
void State::_render() const
{
	// Clear the screen
	SDL_RenderClear(renderer_);

	// Render each game object
	for (auto gameObject : gameObjects_)
	 	gameObject->render();

	// Render the new frame
	SDL_RenderPresent(renderer_);
};

void State::_update() {};
void State::_handleEvents()
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

		// For each game object, run the event handler
		for (auto gameObject : gameObjects_)
			gameObject->handleEvents(event);
	}
}

void State::_afterUpdate() {}

void State::_events() {}

void State::_destroy()
{
	for (auto gameObject : pendingOnDestroy_)
	{
		// If the gameObject was already deleted from memory,
		// skip this search
		if (gameObject == nullptr) continue;

		auto it = gameObjects_.begin();
		while (it != gameObjects_.end())
		{
			if (*it == gameObject)
			{
				gameObjects_.erase(it);
				delete gameObject;
				break;
			}
			it++;
		}
	}

	pendingOnDestroy_.clear();
}

void State::addGameObject(GameObject* gameObject)
{
	gameObjects_.push_back(gameObject);
}

void State::removeGameObject(GameObject* gameObject)
{
	pendingOnDestroy_.push_back(gameObject);
	
}
