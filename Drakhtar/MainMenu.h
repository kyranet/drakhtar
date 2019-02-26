#pragma once

#include "SDL.h"
#include <list>
#include "GameObject.h"
#include "Board.h"
#include "Game.h"
#include "DialogScene.h"
#include "Unit.h"
#include "GameState.h"
#include "Button.h"

using namespace std;

class Game;

class MainMenu : public GameState
{
private:
	bool _exit = false;
	Game* game_ = nullptr;

protected:
	SDL_Renderer *renderer_ = nullptr;
	virtual void _update();
	virtual void _handleEvents();
	virtual void _render() const;
public:
	MainMenu(Game* game, SDL_Renderer* renderer);
	~MainMenu();
	virtual void run();
};

