#pragma once

#include "GameObject.h"
#include "SDL.h"
#include "checkML.h"
#include <list>
#include"Constants.h"
#include"TextureManager.h"

using namespace std;

class Game;

class GameState
{
private:
	bool _exit = false;
protected:
	list<GameObject*> gameObjects_;
	list<GameObject*> pendingOnDestroy_;
	list<EventListener*> eventListeners_;
	Game* game_ = nullptr;
	SDL_Renderer *renderer_ = nullptr;
	SDL_Event event;

public:
	GameState(Game* game,SDL_Renderer* renderer) : game_(game),renderer_(renderer) {};
	virtual ~GameState();

	virtual void run();
	bool getexit();
	virtual void _preload();
	virtual void _create();
	virtual void _update();
	virtual void _render();
	virtual void _handleEvents(SDL_Event& e);
	virtual void _afterUpdate();
	virtual void _events();
	virtual void _destroy();
	virtual void _end() {};
	virtual void addGameObject(GameObject* gameObject);
	virtual void removeGameObject(GameObject* gameObject);

	GameState* addEventListener(EventListener* eventListener);

};

