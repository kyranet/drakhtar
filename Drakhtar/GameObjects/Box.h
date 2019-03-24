// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#pragma once
#include "GameObject.h"

class Unit;

enum class TextureInd {
  BASE = 0,
  HOVER = 1,
  MOVABLE = 2,
  ENEMY = 3,
  ACTIVE = 4
};

class Box : public GameObject {
 protected:
  Vector2D<int> boardIndex_;
  Unit *content_;
  TextureInd cellTexture_;
  Texture *cellTextures_[5];

 public:
  Box(Scene *scene, Vector2D<int> pos, Vector2D<int> size,
      Vector2D<int> boardIndex, Unit *unit);

  virtual void render();
  virtual void handleEvents(SDL_Event event);

  // Getters and Setters
  bool isEmpty() const;
  Vector2D<int> getIndex() const;

  Unit *getContent() const;
  void setContent(Unit *object);

  TextureInd getCurrentTexture() const;
  void setCurrentTexture(TextureInd cellTexture);
};
