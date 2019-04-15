// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#include "Scene.h"
#include <utility>
#include "Errors/SDLError.h"
#include "GameObjects/GameObject.h"
#include "Managers/Input.h"
#include "Managers/TextureManager.h"
#include "SDL.h"
#include "Scenes/RecruitScene.h"
#include "Structures/Game.h"
#include "Utils/Constants.h"
#include "Utils/TimePool.h"

Scene::Scene() = default;
Scene::~Scene() = default;

bool Scene::getTransition() const { return transition_; }

void Scene::setTransition(const bool transition) { transition_ = transition; }

void Scene::setOnEndHandler(std::function<void()> callback) {
  onEndHandler_ = std::move(callback);
}

bool Scene::isFinished() const { return finished_; }
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

  // Run the event loop
  while (!isFinished()) {
    if (poolAnimation->next(SDL_GetTicks())) {
      TextureManager::getInstance()->tick();
    }

    create();
    handleEvents();
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
  // Clear the Input's cache
  Input::instance()->clear();

  // Handle all events
  SDL_Event event;
  while (SDL_PollEvent(&event)) {
    if (event.type == SDL_QUIT) return finish(true);

    Input::instance()->update(event);
    for (auto gameObject : gameObjects_) gameObject->handleEvents(event);
  }

  // If the escape key was pressed, pause the game
  if (Input::isKeyDown(KeyboardKey::ESCAPE)) pause();

  // If the F key was pressed, toggle fullscreen
  if (Input::isKeyDown(KeyboardKey::F)) {
    SDL_Window* window_ = Game::getWindow();
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
  // Delete the Scene's cache.
  for (auto gameObject : gameObjects_) delete gameObject;
  gameObjects_.clear();

  onEndHandler_();
}

void Scene::resume() {
  paused_ = false;
  run();
}

void Scene::pause() { paused_ = true; }

void Scene::finish(bool force) {
  if (force) return Game::getSceneMachine()->popScene();

  finished_ = true;
  paused_ = true;
}

std::list<GameObject*> Scene::getGameObjects() const { return gameObjects_; }

void Scene::addGameObject(GameObject* gameObject) {
  pendingOnCreate_.push_back(gameObject);
}

void Scene::removeGameObject(GameObject* gameObject) {
  pendingOnDestroy_.push_back(gameObject);
}

void Scene::processNextTick(NextTickCallback* callback) {
  nextTick_.push_back(callback);
}

TweenManager* Scene::getTweenManager() const { return tweenManager_; }
