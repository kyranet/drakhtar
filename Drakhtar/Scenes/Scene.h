// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#pragma once
#include <list>

class GameObject;

using NextTickCallback = void();

class Scene {
  bool exit_ = false;
  bool loaded_ = false;
  bool paused_ = true;
  bool finished_ = false;
  bool transition_ = false;
  bool skipDialog_ = false;
 protected:
  std::list<GameObject *> gameObjects_;
  std::list<GameObject *> pendingOnCreate_;
  std::list<GameObject *> pendingOnDestroy_;
  std::list<NextTickCallback *> nextTick_;

 public:
  Scene();
  virtual ~Scene();

  bool isFinished() const;
  bool isRunning() const;
  bool isPaused() const;
  bool isLoaded() const;
  bool getTransition();
  bool getSkip();
  void setTransition(bool transition);
  void setSkip(bool skip);
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
  virtual void finish();

  void addGameObject(GameObject *gameObject);
  void removeGameObject(GameObject *gameObject);

  void processNextTick(NextTickCallback *callback);
};
