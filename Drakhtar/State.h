#pragma once

#include "SDL.h"
#include <list>
#include "GameObject.h"
#include "Board.h"
#include "Game.h"
#include "DialogScene.h"
#include "Unit.h"
#include "TurnBar.h"

using namespace std;

class Game;
class DialogScene;

class State
{
private:
	bool _exit = false;
	list<GameObject*> gameObjects_;
	list<GameObject*> pendingOnDestroy_;
	Game* game_ = nullptr;
protected:
	SDL_Renderer *renderer_ = nullptr;
	virtual void _preload();
	virtual void _create();
	virtual void _render() const;
	virtual void _update();
	virtual void _handleEvents();
	virtual void _afterUpdate();
	virtual void _events();
	virtual void _destroy();
	virtual void _end() {};
public:
	State(Game* game, SDL_Renderer* renderer);
	virtual ~State();
	virtual void run();
	virtual void addGameObject(GameObject* gameObject);
	virtual void removeGameObject(GameObject* gameObject);
};

