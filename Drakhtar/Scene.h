// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#pragma once

class GameObject;

class Scene {
 private:
  bool exit_ = false;
  bool loaded_ = false;
  bool paused_ = false;

 protected:
  list<GameObject *> gameObjects_;
  list<GameObject *> pendingOnCreate_;
  list<GameObject *> pendingOnDestroy_;

 public:
  Scene();
  virtual ~Scene();

  bool isFinished() const;
  bool isPaused() const;
  bool isLoaded() const;
  virtual void run();
  virtual void preload();
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
};
