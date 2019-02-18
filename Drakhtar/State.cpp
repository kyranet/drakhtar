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
	delete exampleDialog_;
	game_ = nullptr;
}

void State::_preload()
{
	auto Tablero = new Board(game_->getTextures()[CELL_FRAME], 8, 12, 50);
	//auto player = new GameObject(game_->getTextures()[RED], Vector2D<int>(225, 325), Vector2D<int>(50, 50));
	//player->addEventListener(new Controller(player));
	gameObjects_.push_back(new GameObject(game_->getTextures()[FIRST_BATTLE], Vector2D<int>(400, 300), Vector2D<int>(800, 600)));
	//gameObjects_.push_back(player);
	gameObjects_.push_back(Tablero);
	auto box = Tablero->getBoxAt(0, 0);
	auto test = new Unit(game_->getTextures()[RED], Vector2D<int>(box->getRect().x + box->getRect().w/2, box->getRect().y + box->getRect().h/2), Vector2D<int>(box->getRect().w, box->getRect().h), 2, 10, 5, 5, 5);
	test->addEventListener(new Controller(test));
	gameObjects_.push_back(test);
	Tablero->getBoxAt(0, 0)->setContent(test);
	
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
