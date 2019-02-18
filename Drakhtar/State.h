#pragma once

#include "SDL.h"
#include <list>
#include "GameObject.h"
#include "Board.h"
#include "Game.h"
#include "DialogScene.h"

using namespace std;

class Game;
class DialogScene;

class State
{
private:
	bool _exit = false;
	list<GameObject*> gameObjects_;
	DialogScene* exampleDialog_;
	Game* game_ = nullptr;
protected:
	SDL_Renderer *renderer_ = nullptr;
	void _preload();
	void _create();
	void _render() const;
	void _update();
	void _handleEvents();
	void _afterUpdate();
	void _events();
	virtual void _destroy() {};
	virtual void _end() {};
public:
	State(Game* game, SDL_Renderer* renderer);
	virtual ~State();
	void run();
};

