// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#pragma once
#include <functional>
#include <list>

#include "Managers/TweenManager.h"

class Pause;
class GameObject;

using NextTickCallback = void();

class Scene {
  bool loaded_ = false;
  bool paused_ = true;
  bool finished_ = false;
  TweenManager* tweenManager_ = nullptr;
  bool transition_ = false;
  bool game_ = false;
  std::function<void()> onEndHandler_;

 protected:
  std::list<GameObject*> gameObjects_;
  std::list<GameObject*> pendingOnCreate_;
  std::list<GameObject*> pendingOnDestroy_;
  std::list<NextTickCallback*> nextTick_;

 public:
  Scene();
  virtual ~Scene();

  bool isFinished() const;
  bool isRunning() const;
  bool isPaused() const;
  bool isLoaded() const;
  bool getTransition() const;
  void setTransition(bool transition);
  void setOnEndHandler(std::function<void()> callback);
  virtual void run();
  virtual void preload();
  virtual void tick();
  virtual void create();
  virtual void update();
  virtual void render();
  virtual void handleEvents();
  virtual void destroy();
  virtual void end();

  virtual void pause();
  virtual void resume();

  void finish(bool force = true);

  std::list<GameObject*> getGameObjects() const;
  void addGameObject(GameObject* gameObject);
  void removeGameObject(GameObject* gameObject);

  void processNextTick(NextTickCallback* callback);

  TweenManager* getTweenManager() const;
  Pause* pauseInterface = nullptr;
};
