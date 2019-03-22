// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#pragma once

#include <list>
#include "Texture.h"
#include "Vector2D.h"

class Scene;
class EventListener;

class GameObject {
 protected:
  bool active_ = true;
  Scene *scene_ = nullptr;
  Vector2D<int> pos_;
  Vector2D<int> size_;
  Texture *texture_;
  list<EventListener *> eventListeners_;

 public:
  GameObject(Scene *scene, Texture *texture, Vector2D<int> pos,
             Vector2D<int> size)
      : scene_(scene), texture_(texture), pos_(pos), size_(size) {}
  virtual ~GameObject();
  virtual void render() const;
  virtual void handleEvents(SDL_Event event);
  GameObject *addEventListener(EventListener *eventListener);
  SDL_Rect getRect() const;

  void setActive(bool active);
  bool getActive() const;

  void setTexture(Texture *texture);
  Texture *getTexture() const;

  void destroy();
};
