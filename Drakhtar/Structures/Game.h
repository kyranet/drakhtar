// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#pragma once

#include "SDL.h"
#include "SceneMachine.h"

class Scene;
class SceneMachine;

class Game final {
  static Game *instance_;
  SDL_Window *window_ = nullptr;
  SDL_Renderer *renderer_ = nullptr;
  SceneMachine *sceneMachine_ = nullptr;
  Game();

 public:
  ~Game();
  void run() const;
  // Get the SDL_Renderer instance.
  static SDL_Renderer *getRenderer();
  // Get the Game instance.
  static Game *getInstance();
  // Get the SceneMachine instance.
  static SceneMachine *getSceneMachine();
};
