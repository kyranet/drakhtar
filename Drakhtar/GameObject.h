// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#pragma once

#include "Texture.h"
#include "EventListener.h"
#include "Vector2D.h"
#include <list>

class EventListener;

class GameObject
{
 protected:
    Vector2D<int> pos_;
    Vector2D<int> size_;
    Texture *texture_;
    list<EventListener *> eventListeners_;

 public:
    GameObject(Texture *texture, Vector2D<int> pos, Vector2D<int> size)
        : texture_(texture), pos_(pos), size_(size) {}
    virtual ~GameObject();
    virtual void render() const;
    virtual void handleEvents(SDL_Event event);
    GameObject *addEventListener(EventListener *eventListener);
    SDL_Rect getRect() const;
    Texture *getTexture() const;
    void setTexture(Texture *texture);
    void destroy();
};
