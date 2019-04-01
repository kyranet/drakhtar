// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#pragma once

#include "GameObject.h"
#include "../EventListeners/EventListener.h"
#include "../Scenes/Scene.h"
#include "../Structures/Game.h"
#include "../Structures/Texture.h"

GameObject::GameObject(Scene *scene, Texture *texture)
    : scene_(scene),
      texture_(texture),
      position_(Vector2D<int>(0, 0)),
      size_(Vector2D<int>(0, 0)) {}
GameObject::GameObject(Scene *scene, Texture *texture, Vector2D<int> position,
                       Vector2D<int> size)
    : scene_(scene), texture_(texture), position_(position), size_(size) {}

GameObject::~GameObject() {
  scene_ = nullptr;
  texture_ = nullptr;

  // Clean up event listeners
  for (auto listener : eventListeners_) delete listener;
  eventListeners_.clear();

  // Clean up children
  for (auto child : children_) delete child;
  children_.clear();
}

void GameObject::render() const {
  if (texture_ != nullptr) {
    texture_->renderFrame(getRect(),
                          texture_->getAnimation()[texture_->getFrame()]);
  }
  for (auto child : children_) child->render();
}

void GameObject::update() {
  for (auto child : children_) child->update();
}

void GameObject::handleEvents(const SDL_Event event) {
  for (auto listener : eventListeners_) listener->run(event);
  for (auto child : children_) child->handleEvents(event);
}

GameObject *GameObject::addEventListener(EventListener *eventListener) {
  eventListeners_.push_back(eventListener);
  return this;
}

SDL_Rect GameObject::getRect() const {
  return {position_.getX() - size_.getX() / 2,
          position_.getY() - size_.getY() / 2, size_.getX(), size_.getY()};
}

Texture *GameObject::getTexture() const { return texture_; }

bool GameObject::hasParent() const { return parent_ != nullptr; }
void GameObject::setParent(GameObject *gameObject) { parent_ = gameObject; }
GameObject *GameObject::getParent() const { return parent_; }

void GameObject::setTexture(Texture *texture) { texture_ = texture; }

void GameObject::setActive(bool active) { active_ = active; }

bool GameObject::getActive() const { return active_; }

void GameObject::setPosition(Vector2D<int> position) { position_ = position; }
Vector2D<int> GameObject::getPosition() const { return position_; }

bool GameObject::hasChildren() const { return !children_.empty(); }
std::vector<GameObject *> GameObject::getChildren() const { return children_; }

void GameObject::addChild(GameObject *gameObject) {
  children_.push_back(gameObject);
  gameObject->setParent(this);
}

void GameObject::removeChild(GameObject *gameObject) {
  for (auto it = children_.begin(); it != children_.end(); it++) {
    if (*it == gameObject) {
      children_.erase(it);
      break;
    }
  }
}

void GameObject::destroy() { scene_->removeGameObject(this); }
