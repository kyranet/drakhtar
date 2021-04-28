// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.
// Work derived from https://github.com/photonstorm/phaser, all credits to
// photonstorm and its contributors.

#pragma once
#include <list>

#include "GameObjects/GameObject.h"

class Scene;
class Tween;

class TweenManager final : public GameObject {
  std::list<Tween*> add_;
  std::list<Tween*> pending_;
  std::list<Tween*> active_;
  std::list<Tween*> destroy_;
  unsigned int toProcess_ = 0;

 public:
  explicit TweenManager(Scene* scene);
  ~TweenManager();
  Tween* create();
  void add(Tween* tween);
  void remove(Tween* tween);
  void preUpdate();
  void update() override;
  void makeActive(Tween* tween);
  std::list<Tween*> getAllTweens() const;
  void removeAllTweens() const;
  void pauseAllTweens();
  void resumeAllTweens();
};
