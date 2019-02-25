#pragma once

#include "GameObject.h"
#include "SDL.h"
#include "checkML.h"
#include <list>

using namespace std;

class Game;

class GameState
{
protected:
	list<GameObject*> gameObjects;
	Game* game;

public:
	GameState(Game* game) : game(game) {};
	~GameState() { }

	virtual void run();
	virtual void update();
	virtual void render();
	virtual void handleEvents();
};

