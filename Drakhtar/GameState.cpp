#include "GameState.h"


void GameState::_render() {
	// Clear the screen
	SDL_RenderClear(renderer_);

	// Render each game object
	for (auto gameObject : gameObjects_)
		gameObject->render();

	// Render the new frame
	SDL_RenderPresent(renderer_);
}

void GameState::_preload()
{

}

void GameState::_create()
{
}

void GameState::_update() {
	
}

void GameState::_handleEvents(SDL_Event& e) {
	// Listen to SDL events
	while (!_exit && SDL_PollEvent(&e))
	{
		// If the event type is quit, change state to GAMEOVER for cleanup
		if (e.type == SDL_QUIT)
		{
			_exit = true;
			// TODO: Change State
		}
	}

	for (auto listener : eventListeners_)
		listener->run(e);
}

void GameState::_afterUpdate()
{
}

void GameState::_events()
{
}

void GameState::_destroy()
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

GameState::~GameState()
{
	for (auto gameObject : gameObjects_)
		delete gameObject;
	game_ = nullptr;
}

void GameState::run() {
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

	uint lastTick = SDL_GetTicks();
	uint elapsedTicks = 0;
	uint requiredTicks = 1000 / ANIMATION_TICKS_PER_SECOND;
	while (!_exit)
	{
		_create();
		_handleEvents(event);
		_update();

		elapsedTicks = SDL_GetTicks() - lastTick;
		if (elapsedTicks >= requiredTicks)
		{
			lastTick += elapsedTicks;
			TextureManager::getInstance()->tick();
		}
		_afterUpdate();
		_render();
		_events();
		_destroy();
	}
	_end();
}

GameState* GameState::addEventListener(EventListener* eventListener)
{
	eventListeners_.push_back(eventListener);
	return this;
};