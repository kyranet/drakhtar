// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#pragma once

#include "LocaleManager.h"
#include "SDL.h"
#include "SceneMachine.h"

class Scene;
class SceneMachine;

class Game final {
  static Game* instance_;
  SDL_Window* window_ = nullptr;
  SDL_Renderer* renderer_ = nullptr;
  SceneMachine* sceneMachine_ = nullptr;
  LocaleManager localeManager_{};
  Locale locale_{localeManager_};

  Game();

  bool loaded_ = false;

 public:
  ~Game();
  void run() const;
  void load();
  // Get the SDL_Renderer instance.
  static SDL_Renderer* getRenderer();
  // Get the Game instance.
  static Game* getInstance();
  // Get the SceneMachine instance.
  static SceneMachine* getSceneMachine();
  // Get the SDL_Window instance
  static SDL_Window* getWindow();
  // Get the Locale instance
  Locale* getLocale();
};
