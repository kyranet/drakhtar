// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#pragma once

#include <list>
#include "SDL.h"
#include "Vector2D.h"

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
  list<EventListener *> eventListeners_;

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

  void destroy();
};
