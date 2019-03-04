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
#include "Battalion.h"
#include "TurnBar.h"
#include "SDLAudioManager.h"

using namespace std;

class DialogScene;

class State : public GameState
{
private:
	bool _exit = false;
	Game* game_ = nullptr;
	TurnBar* turnBar_;
	Board* board_;
	SDLAudioManager * audioManager;
protected:
	void _preload();
	void _handleEvents(SDL_Event& e);
	
	void boton() { cout << "boton"; }
public:
	State(Game* game, SDL_Renderer* renderer);
	virtual ~State();
	virtual void addGameObject(GameObject* gameObject);
	virtual void removeGameObject(GameObject* gameObject);
};

