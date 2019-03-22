#include "Scene.h"
#include "GameObject.h"
#include "SDL.h"

Scene::Scene() {}
Scene::~Scene() {}

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
    update();
    render();
    destroy();
  }

  end();
}

void Scene::preload() {}
void Scene::create() {
  for (auto gameObject : pendingOnCreate_) {
    // If the gameObject was removed early, skip
    if (gameObject == nullptr) continue;
    gameObjects_.push_back(gameObject);
  }
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
  // TODO(Antonio Román): Add GameObject::update()
  // for (auto gameObject : gameObjects_) gameObject->update();
}

void Scene::render() {
  // Clear the screen
  SDL_RenderClear(renderer_);

  // Render each game object
  for (auto gameObject : gameObjects_) {
    if (gameObject->getActive()) gameObject->render();
  }

  // Render the new frame
  SDL_RenderPresent(renderer_);
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

void Scene::end() {}

void Scene::resume() { paused_ = true; }
void Scene::pause() {
  paused_ = false;
  run();
}

void Scene::finish() {
  paused_ = true;
  exit_ = true;
}

void Scene::addGameObject(GameObject *gameObject) {
  pendingOnCreate_.push_back(gameObject);
}

void Scene::removeGameObject(GameObject *gameObject) {
  pendingOnDestroy_.push_back(gameObject);
}
