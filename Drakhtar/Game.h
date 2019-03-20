// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#pragma once

#include "SDL.h"
#include "SDL_ttf.h"
#include "GameState.h"
#include "SDL_mixer.h"
#include "State.h"
#include "Texture.h"
#include "GameStateMachine.h"
#include "Constants.h"
#include "TextureManager.h"
#include "FontManager.h"

typedef unsigned int uint;

class GameState;
class GameStateMachine;

class Game
{
 private:
    static Game *instance;
    SDL_Window *window_ = nullptr;
    SDL_Renderer *renderer_ = nullptr;
    // TODO(Kyra): Why is this a thing.
    SDL_Event event;
    bool _exit = false;
    TextureManager *textureManager_ = TextureManager::getInstance();
    FontManager * fontManager_ = FontManager::getInstance();
    GameStateMachine *stateMachine = nullptr;
    GameState *state_ = nullptr;
    GameState *currentState_ = nullptr;
    Game();

 public:
    virtual ~Game();
    // Run the game's loop.
    void run();
    // Get the SDL_Renderer instance.
    SDL_Renderer *getRenderer();
    // Get the Game instance.
    static Game *getInstance();
    // Get the GameState instance.
    static GameState *currentState();
    // Get the GameStateMachine instance.
    GameStateMachine *getStateMachine();
};
