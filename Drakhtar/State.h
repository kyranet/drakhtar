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
#include"Pause.h"

using namespace std;

class DialogScene;

class State : public GameState
{
private:
	bool _exit = false;
	bool paused_ = false;
	Game* game_ = nullptr;
	TurnBar* turnBar_;
	Board* board_;
	Pause* pause_ = nullptr;
protected:
	void _preload();
	void _render();
	void _handleEvents(SDL_Event& e);
	void boton() { cout << "boton"; }
	SDLAudioManager audioManager;
public:
	State(Game* game, SDL_Renderer* renderer);
	virtual ~State();

	// temporary
	void playSound(int tag, int loop, int channels);

};

