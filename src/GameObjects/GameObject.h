// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#pragma once

#include <vector>

#include "../Utils/Vector2D.h"
#include "SDL.h"

class Scene;
class Texture;
class EventListener;

class GameObject {
 protected:
  bool awakened_ = false;
  bool active_ = true;
  bool transparent_ = false;
  bool renderable_ = true;
  Scene* scene_ = nullptr;
  Vector2D<int> position_;
  Vector2D<int> size_;
  Texture* texture_;
  std::vector<EventListener*> eventListeners_;
  std::vector<GameObject*> children_;
  GameObject* parent_ = nullptr;

 public:
  GameObject(Scene* scene, Texture* texture);
  GameObject(Scene* scene, Texture* texture, const Vector2D<int>& position,
             const Vector2D<int>& size);
  virtual ~GameObject();
  virtual void awake();
  virtual void render(SDL_Rect) const;
  virtual void render() const;
  virtual void update();
  virtual void handleEvents(SDL_Event event);
  GameObject* addEventListener(EventListener* eventListener);
  virtual SDL_Rect getRect() const;

  Scene* getScene() const;

  void setActive(bool active);
  bool getActive() const;

  void setTransparent(bool transparent);
  bool getTransparent() const;

  void setRenderable(bool renderable);
  bool getRenderable() const;

  void setSize(Vector2D<int> size);
  Vector2D<int> getSize() const;

  void setPosition(const Vector2D<int>& position);
  Vector2D<int> getPosition() const;

  void setTexture(Texture* texture);
  Texture* getTexture() const;

  bool hasParent() const;
  void setParent(GameObject* gameObject);
  GameObject* getParent() const;

  bool hasChildren() const;
  std::vector<GameObject*> getChildren() const;
  void addChild(GameObject* gameObject);
  void removeChild(GameObject* gameObject);

  void destroy();

  GameObject* clickScan(SDL_Point point) const;
};
