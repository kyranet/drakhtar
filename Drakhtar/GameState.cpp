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

bool GameState::getexit()
{
	return _exit;
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
GameState* GameState::addEventListener(EventListener* eventListener)
{
	eventListeners_.push_back(eventListener);
	return this;
};

void GameState::addGameObject(GameObject* gameObject)
{
	gameObjects_.push_back(gameObject);
}

void GameState::removeGameObject(GameObject* gameObject)
{
	pendingOnDestroy_.push_back(gameObject);
}
