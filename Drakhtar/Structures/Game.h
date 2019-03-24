// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#pragma once

#include "SDL.h"
#include "SDL_mixer.h"
#include "SDL_ttf.h"
#include "SceneMachine.h"

using uint = unsigned int;

class Scene;
class SceneMachine;

class Game {
 private:
  static Game *instance;
  SDL_Window *window_ = nullptr;
  SDL_Renderer *renderer_ = nullptr;
  SceneMachine *sceneMachine_ = nullptr;
  Game();

 public:
  virtual ~Game();
  void run();
  // Get the SDL_Renderer instance.
  static SDL_Renderer *getRenderer();
  // Get the Game instance.
  static Game *getInstance();
  // Get the SceneMachine instance.
  static SceneMachine *getSceneMachine();
};
