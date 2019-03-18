// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

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
#include "UnitFactory.h"
#include "SDLAudioManager.h"
#include "Pause.h"
#include "UnitFactory.h"

using namespace std;

class DialogScene;

class State : public GameState
{
 private:
    bool _exit = false;
    Game *game_ = nullptr;
    TurnBar *turnBar_;
    Button *Pause_Button;
    Pause *pauseInterface = nullptr;
    Board *board_ = nullptr;
    Team *team1 = nullptr;
    Team *team2 = nullptr;
    UnitFactory *factory = nullptr;

 protected:
    void _preload();
    void _render();
    void _update();
    void _handleEvents(SDL_Event e);
    void boton() { cout << "boton"; }
    SDLAudioManager audioManager;

 public:
    State(Game *game, SDL_Renderer *renderer);
    virtual ~State();
    void setPause();
    bool paused_ = false;
    // temporary
    void playSound(int tag, int loop, int channels);
    static void Pause_game(Game *game, SDL_Renderer *renderer);
};
