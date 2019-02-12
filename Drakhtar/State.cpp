#pragma once

#include "State.h"


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

void State::run()
{
	// Hardcoded stuff so this works
	gameObjects_.push_back(new GameObject(game_->getTextures()[1], 400, 300, 800.0, 600.0));
	gameObjects_.push_back(new GameObject(game_->getTextures()[0], 400.0, 300.0, 50.0, 50.0));
	gameObjects_.push_back(new Board(game_->getTextures()[2], 8, 12, 50));

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
		// for (auto gameObject : _gameObjects)
		// 	gameObject->handleEvents(event);
	}
};
void State::_afterUpdate() {};
void State::_events() {};
