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
	Button* Play;

protected:	
	void _preload();
	//void _handleEvents(SDL_Event& e);

	static void Play_game(Game* game);
public:
	MainMenu(Game* game, SDL_Renderer* renderer);
	~MainMenu();
	
};

