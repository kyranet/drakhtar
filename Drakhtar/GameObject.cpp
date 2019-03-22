// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#pragma once

#include "GameObject.h"
#include "EventListener.h"
#include "Game.h"
#include "Scene.h"

GameObject::~GameObject() {
  texture_ = nullptr;
  for (auto listener : eventListeners_) delete listener;
  eventListeners_.clear();
}

void GameObject::render() const {
  if (texture_ == nullptr) return;
  texture_->renderFrame(getRect(),
                        texture_->getAnimation()[texture_->getFrame()]);
}

void GameObject::handleEvents(SDL_Event event) {
  for (auto listener : eventListeners_) listener->run(event);
}

GameObject *GameObject::addEventListener(EventListener *eventListener) {
  eventListeners_.push_back(eventListener);
  return this;
};

SDL_Rect GameObject::getRect() const {
  return {pos_.getX() - size_.getX() / 2, pos_.getY() - size_.getY() / 2,
          size_.getX(), size_.getY()};
}

Texture *GameObject::getTexture() const { return texture_; }

void GameObject::setTexture(Texture *texture) { texture_ = texture; }

void GameObject::setActive(bool active) { active_ = active; }

bool GameObject::getActive() const { return active_; }

void GameObject::destroy() { scene_->removeGameObject(this); }
