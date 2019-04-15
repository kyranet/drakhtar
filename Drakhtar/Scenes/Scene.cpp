// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#include "Scene.h"
#include "../Scenes/RecruitScene.h"
#include "Errors/SDLError.h"
#include "GameObjects/GameObject.h"
#include "Managers/Input.h"
#include "Managers/TextureManager.h"
#include "SDL.h"
#include "Structures/Game.h"
#include "Utils/Constants.h"
#include "Utils/TimePool.h"

Scene::Scene() = default;
Scene::~Scene() { Scene::finish(); }

bool Scene::getTransition() const { return transition_; }

void Scene::setTransition(const bool transition) { transition_ = transition; }

bool Scene::isFinished() const { return exit_; }
bool Scene::isRunning() const { return !paused_; }
bool Scene::isPaused() const { return paused_; }
bool Scene::isLoaded() const { return loaded_; }

void Scene::run() {
  // If it hasn't loaded yet, preload and set it to loaded
  if (!isLoaded()) {
    preload();
    loaded_ = true;
  }

  // If it's already running, don't re-run the event loop twice
  if (isRunning()) return;

  // Set current status to resume
  resume();

  auto poolAnimation =
      new TimePool(1000 / ANIMATION_TICKS_PER_SECOND, SDL_GetTicks());
  auto poolFrameRate = new TimePool(1000 / GAME_FRAMERATE, SDL_GetTicks());
  while (!isFinished()) {
    if (poolAnimation->next(SDL_GetTicks())) {
      TextureManager::getInstance()->tick();
    }

    create();
    handleEvents();

    // If it has received a SDL_QUIT, don't process the event loop any further
    if (exit_) break;

    // Otherwise continue the event loop
    update();
    render();
    destroy();
    tick();

    if (poolFrameRate->next(SDL_GetTicks())) {
      SDL_Delay(poolFrameRate->getRemaining());
    }
  }

  delete poolAnimation;
  delete poolFrameRate;

  end();
}

void Scene::preload() {
  tweenManager_ = new TweenManager(this);
  addGameObject(tweenManager_);
}

void Scene::tick() {
  if (nextTick_.empty()) return;

  for (auto callback : nextTick_) {
    callback();
  }
  nextTick_.clear();
}

void Scene::create() {
  for (auto gameObject : pendingOnCreate_) {
    // If the gameObject was removed early, skip
    if (gameObject == nullptr) continue;
    gameObjects_.push_back(gameObject);
  }

  pendingOnCreate_.clear();
}

void Scene::handleEvents() {
  SDL_Event event;
  Input::instance()->clear();

  while (SDL_PollEvent(&event)) {
    if (event.type == SDL_QUIT) {
      exit_ = true;
      break;
    }

    Input::instance()->update(event);
    for (auto gameObject : gameObjects_) {
      gameObject->handleEvents(event);

      // Some event handlers can change the exit_ state, which causes several
      // issues as this loop will keep running when it's supposed to stop. This
      // cannot be done with a for loop using iterators, but only making it so
      // it checks for exit_ and breaking before increasing it.
      if (exit_) break;
    }
  }

  if (Input::isKeyDown(KeyboardKey::ESCAPE)) {
    Game::getSceneMachine()->getCurrentScene()->pause();
  }

  if (!exit_ && Input::isKeyDown(KeyboardKey::F)) {
    SDL_Window *window_ = Game::getWindow();
    const auto flags = SDL_GetWindowFlags(window_);
    const auto flag = flags & SDL_WINDOW_FULLSCREEN ? 0 : SDL_WINDOW_FULLSCREEN;
    if (SDL_SetWindowFullscreen(window_, flag) != 0) {
      throw SDLError("Failed to change full screen: " +
                     std::string(SDL_GetError()));
    }
  }
}

void Scene::update() {
  for (auto gameObject : gameObjects_) gameObject->update();
}

void Scene::render() {
  // Clear the screen
  SDL_RenderClear(Game::getRenderer());

  // Render each game object
  for (auto gameObject : gameObjects_) {
    if (gameObject->getActive()) gameObject->render();
  }

  // Render the new frame
  SDL_RenderPresent(Game::getRenderer());
}

void Scene::destroy() {
  for (auto gameObject : pendingOnDestroy_) {
    // If the gameObject was already deleted from memory,
    // skip this search
    if (gameObject == nullptr) continue;

    auto it = gameObjects_.begin();
    while (it != gameObjects_.end()) {
      if (*it == gameObject) {
        gameObjects_.erase(it);
        delete gameObject;
        break;
      }
      ++it;
    }
  }

  pendingOnDestroy_.clear();
}

void Scene::end() {
  finish();
  // This is logic, as this is run at the end of the event loop, finishing and
  // deleting the object early can cause several issues as the Scene has not
  // been done yet with its job, so makes sense to put it here so it finishes
  // all its remaining tasks.
  // Also, it's safe to delete this because finish() removes this instance from
  // the SceneMachine, so there are no memory leaks.
  delete this;
}

void Scene::resume() {
  paused_ = false;
  run();
}
void Scene::pause() { paused_ = true; }

void Scene::skipTurn() {}

void Scene::finish() {
  if (finished_) return;

  finished_ = true;
  paused_ = true;
  exit_ = true;

  for (auto gameObject : gameObjects_) delete gameObject;
  gameObjects_.clear();

  Game::getSceneMachine()->popScene();
}

std::list<GameObject *> Scene::getGameObjects() const { return gameObjects_; }

void Scene::addGameObject(GameObject *gameObject) {
  pendingOnCreate_.push_back(gameObject);
}

void Scene::removeGameObject(GameObject *gameObject) {
  pendingOnDestroy_.push_back(gameObject);
}

void Scene::processNextTick(NextTickCallback *callback) {
  nextTick_.push_back(callback);
}

TweenManager *Scene::getTweenManager() const { return tweenManager_; }
