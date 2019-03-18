// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#pragma once
#include "Button.h"
#include "SDL.h"
#include "GameState.h"

class Pause : public GameState
{
 private:
    SDL_Renderer *renderer_ = nullptr;
    Game *game_ = nullptr;
    Button *Restart;
    Button *Exit;
    list<GameObject *> gameObjectsPause_;

 public:
    Pause(Game *game, SDL_Renderer *renderer);
    virtual ~Pause();
    void _preload();
    void _render();
    void _handleEvents(SDL_Event e);
    static void RestartGame(Game *game, SDL_Renderer *renderer);
    static void ExitGame(Game *game, SDL_Renderer *renderer);
};
