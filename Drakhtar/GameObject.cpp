// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#pragma once

#include "GameObject.h"
#include "EventListener.h"
#include "Game.h"
#include "Scene.h"
#include "Texture.h"

GameObject::GameObject(Scene *scene, Texture *texture)
    : scene_(scene),
      texture_(texture),
      position_(Vector2D<int>(0, 0)),
      size_(Vector2D<int>(0, 0)) {}
GameObject::GameObject(Scene *scene, Texture *texture, Vector2D<int> position,
                       Vector2D<int> size)
    : scene_(scene), texture_(texture), position_(position), size_(size) {}

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
  return {position_.getX() - size_.getX() / 2,
          position_.getY() - size_.getY() / 2, size_.getX(), size_.getY()};
}

Texture *GameObject::getTexture() const { return texture_; }

void GameObject::setTexture(Texture *texture) { texture_ = texture; }

void GameObject::setActive(bool active) { active_ = active; }

bool GameObject::getActive() const { return active_; }

void GameObject::setPosition(Vector2D<int> position) { position_ = position; }
Vector2D<int> GameObject::getPosition() const { return position_; }

void GameObject::destroy() { scene_->removeGameObject(this); }
