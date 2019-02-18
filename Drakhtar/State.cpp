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
	auto player = new GameObject(game_->getTextures()[BLUE_ARCHER], vector2d{ 400, 300 }, vector2d{ 50, 50 });
	player->addEventListener(new Controller(player));
	gameObjects_.push_back(new GameObject(game_->getTextures()[FIRST_BATTLE], vector2d{ 400, 300 }, vector2d{ 800, 600 }));
	gameObjects_.push_back(player);
	gameObjects_.push_back(new Board(game_->getTextures()[CELL_FRAME], 8, 12, 50));

	exampleDialog_ = new DialogScene(game_, "dialog1_start", "Retron2000");
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

	exampleDialog_->render();

	

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

		exampleDialog_->handleEvents(event);

	}
};
void State::_afterUpdate() {};
void State::_events() {};
