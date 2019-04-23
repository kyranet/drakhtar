// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.
#include "GameObject.h"
#include "../EventListeners/EventListener.h"
#include "../Scenes/Scene.h"
#include "../Structures/Game.h"
#include "../Structures/Texture.h"

GameObject::GameObject(Scene* scene, Texture* texture)
    : scene_(scene), position_(0, 0), size_(0, 0), texture_(texture) {}
GameObject::GameObject(Scene* scene, Texture* texture,
                       const Vector2D<int>& position, const Vector2D<int>& size)
    : scene_(scene), position_(position), size_(size), texture_(texture) {}

GameObject::~GameObject() {
  // Clean up event listeners
  for (auto listener : eventListeners_) delete listener;
  eventListeners_.clear();

  // Clean up children
  for (auto child : children_) delete child;
  children_.clear();
}

void GameObject::render(SDL_Rect rect) const {
  if (getRenderizable() && texture_ != nullptr) {
    texture_->renderFrame(rect, texture_->getAnimation()[texture_->getFrame()]);
  }
  for (auto child : children_)
    if (child->getRenderizable()) child->render();
}

void GameObject::render() const { render(getRect()); }

void GameObject::update() {
  for (auto child : children_)
    if (child->getActive()) child->update();
}

void GameObject::handleEvents(const SDL_Event event) {
  for (auto listener : eventListeners_)
    if (listener->getActive()) listener->run(event);
  for (auto child : children_)
    if (child->getActive()) child->handleEvents(event);
}

GameObject* GameObject::addEventListener(EventListener* eventListener) {
  eventListeners_.push_back(eventListener);
  return this;
}

SDL_Rect GameObject::getRect() const {
  return {position_.getX() - size_.getX() / 2,
          position_.getY() - size_.getY() / 2, size_.getX(), size_.getY()};
}

Scene* GameObject::getScene() const { return scene_; }

bool GameObject::hasParent() const { return parent_ != nullptr; }
void GameObject::setParent(GameObject* gameObject) { parent_ = gameObject; }
GameObject* GameObject::getParent() const { return parent_; }

void GameObject::setTexture(Texture* texture) { texture_ = texture; }
Texture* GameObject::getTexture() const { return texture_; }

void GameObject::setActive(const bool active) { active_ = active; }
bool GameObject::getActive() const { return active_; }

void GameObject::setTransparent(const bool transparent) {
  transparent_ = transparent;
}

bool GameObject::getTransparent() const { return transparent_; }

void GameObject::setRenderizable(bool renderizable) {
  renderizable_ = renderizable;
}

bool GameObject::getRenderizable() const { return renderizable_; }

void GameObject::setSize(Vector2D<int> size) { size_ = size; }
Vector2D<int> GameObject::getSize() const { return size_; }

void GameObject::setPosition(const Vector2D<int>& position) {
  position_ = position;
}
Vector2D<int> GameObject::getPosition() const { return position_; }

bool GameObject::hasChildren() const { return !children_.empty(); }
std::vector<GameObject*> GameObject::getChildren() const { return children_; }

void GameObject::addChild(GameObject* gameObject) {
  children_.push_back(gameObject);
  gameObject->setParent(this);
}

void GameObject::removeChild(GameObject* gameObject) {
  for (auto it = children_.begin(); it != children_.end(); ++it) {
    if (*it == gameObject) {
      children_.erase(it);
      break;
    }
  }
}

void GameObject::destroy() { scene_->removeGameObject(this); }

GameObject* GameObject::clickScan(SDL_Point point) const {
  const auto children = getChildren();
  for (auto it = children.rbegin(); it != children.rend(); ++it) {
    const auto child = *it;
    if (child->clickScan(point)) return child;
  }

  const auto rect = getRect();
  return !getTransparent() && SDL_PointInRect(&point, &rect)
             ? const_cast<GameObject*>(this)
             : nullptr;
}
