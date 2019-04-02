// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.
// Work derived from https://github.com/photonstorm/phaser, all credits to
// photonstorm and its contributors.

#include "TweenManager.h"
#include "Scenes/Scene.h"
#include "Structures/Tween.h"

static std::list<Tween*>::iterator iteratorFrom(std::list<Tween*>& list,
                                                Tween* tween) {
  for (auto it = list.begin(); it != list.end(); ++it) {
    if ((*it) == tween) return it;
  }
  return list.end();
}

static bool isInList(std::list<Tween*>& list, Tween* tween) {
  return iteratorFrom(list, tween) != list.end();
}

TweenManager::TweenManager(Scene* scene) : GameObject(scene, nullptr) {}
TweenManager::~TweenManager() {
  for (const auto item : add_) delete item;
  for (const auto item : pending_) delete item;
  for (const auto item : active_) delete item;
  for (const auto item : destroy_) delete item;
  add_.clear();
  pending_.clear();
  active_.clear();
  destroy_.clear();
  toProcess_ = 0;
}

Tween* TweenManager::create() {
  const auto tween = new Tween(this);
  add(tween);
  return tween;
}

void TweenManager::add(Tween* tween) {
  add_.push_back(tween);
  toProcess_++;
}

void TweenManager::remove(Tween* tween) {
  add_.remove(tween);
  pending_.remove(tween);
  active_.remove(tween);
  destroy_.remove(tween);
}

void TweenManager::preUpdate() {
  if (toProcess_ == 0) return;

  // Process all pending-to-destroy tweens
  for (auto tween : destroy_) {
    auto it = iteratorFrom(active_, tween);
    if (it == active_.end()) {
      // Not in the active array, is it in pending instead?
      it = iteratorFrom(pending_, tween);
      if (it != pending_.end()) {
        tween->setState(TweenState::REMOVED);
        delete *it;
        pending_.erase(it);
      }
    } else {
      tween->setState(TweenState::REMOVED);
      delete *it;
      active_.erase(it);
    }
  }
  destroy_.clear();

  // Process all pending-to-add tweens
  for (auto tween : add_) {
    if (tween->getState() == TweenState::PENDING_ADD) {
      if (tween->init()) {
        tween->play();
        active_.push_back(tween);
      } else {
        pending_.push_back(tween);
      }
    }
  }
  add_.clear();

  toProcess_ = 0;
}

void TweenManager::update() {
  preUpdate();

  for (auto tween : active_) {
    tween->update();
    if (tween->getState() == TweenState::PENDING_REMOVE) {
      destroy_.push_back(tween);
      toProcess_++;
    }
  }
}

std::list<Tween*> TweenManager::getAllTweens() const { return active_; }

void TweenManager::removeAllTweens() const {
  for (auto tween : active_) tween->stop();
}

void TweenManager::pauseAllTweens() {
  for (auto tween : active_) tween->pause();
}

void TweenManager::resumeAllTweens() {
  for (auto tween : active_) tween->resume();
}

void TweenManager::makeActive(Tween* tween) {
  if (isInList(add_, tween) || isInList(active_, tween)) return;

  const auto index = iteratorFrom(pending_, tween);
  if (index != pending_.end()) {
    pending_.erase(index);
  }

  add_.push_back(tween);
  tween->setState(TweenState::PENDING_ADD);
  ++toProcess_;
}
