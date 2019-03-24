// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#pragma once

#include <list>
#include <typeindex>
#include "../Utils/Vector2D.h"
#include "SDL.h"

class Scene;
class Texture;
class EventListener;

class GameObject {
 protected:
  bool active_ = true;
  Scene *scene_ = nullptr;
  Vector2D<int> position_;
  Vector2D<int> size_;
  Texture *texture_;
  std::list<EventListener *> eventListeners_;
  std::list<GameObject *> children_;
  GameObject *parent_ = nullptr;

 public:
  GameObject(Scene *scene, Texture *texture);
  GameObject(Scene *scene, Texture *texture, Vector2D<int> position,
             Vector2D<int> size);
  virtual ~GameObject();
  virtual void render() const;
  virtual void handleEvents(SDL_Event event);
  GameObject *addEventListener(EventListener *eventListener);
  SDL_Rect getRect() const;

  void setActive(bool active);
  bool getActive() const;

  void setPosition(Vector2D<int> position);
  Vector2D<int> getPosition() const;

  void setTexture(Texture *texture);
  Texture *getTexture() const;

  bool hasParent() const;
  void setParent(GameObject *gameObject);
  GameObject *getParent() const;

  bool hasChildren() const;
  std::list<GameObject *> getChildren() const;
  void addChild(GameObject *gameObject);
  void removeChild(GameObject *gameObject);

  void destroy();
};
