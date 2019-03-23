#include "Scene.h"
#include "Game.h"
#include "GameObject.h"
#include "SDL.h"

Scene::Scene() {}
Scene::~Scene() { finish(); }

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

  while (!isFinished()) {
    create();
    handleEvents();

    // If it has received a SDL_QUIT, don't process the event loop any further
    if (exit_) break;

    // Otherwise continue the event loop
    update();
    render();
    destroy();
    tick();
  }

  end();
}

void Scene::preload() {}

void Scene::tick() {
  if (!nextTick_.size()) return;

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
  while (SDL_PollEvent(&event)) {
    if (event.type == SDL_QUIT) {
      exit_ = true;
      break;
    }

    for (auto gameObject : gameObjects_) gameObject->handleEvents(event);
  }
}

void Scene::update() {
  // TODO(Antonio Rom�n): Add GameObject::update()
  // for (auto gameObject : gameObjects_) gameObject->update();
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
      it++;
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

void Scene::resume() { paused_ = true; }
void Scene::pause() {
  paused_ = false;
  run();
}

void Scene::finish() {
  if (finished_) return;

  finished_ = true;
  paused_ = true;
  exit_ = true;

  for (auto gameObject : gameObjects_) delete gameObject;
  gameObjects_.clear();

  Game::getSceneMachine()->popScene();
}

void Scene::addGameObject(GameObject *gameObject) {
  pendingOnCreate_.push_back(gameObject);
}

void Scene::removeGameObject(GameObject *gameObject) {
  pendingOnDestroy_.push_back(gameObject);
}

void Scene::processNextTick(NextTickCallback *callback) {
  nextTick_.push_back(callback);
}
