// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#pragma once

#include "GameObject.h"

class Unit;

class Box : public GameObject {
 protected:
  Vector2D<int> boardIndex;
  Unit *content;
  int currentTexture;
  Texture *cellTextures[5];

 public:
  Box(Texture *t, Vector2D<int> pos, Vector2D<int> size,
      Vector2D<int> boardIndex, Unit *go);
  virtual ~Box();

  virtual void render();
  virtual void handleEvents(SDL_Event event);

  // Getters and Setters
  bool isEmpty();
  Vector2D<int> getIndex();
  Unit *getContent();
  void setContent(Unit *object);
  int getCurrentTexture() const;
  void setCurrentTexture(int textureInd);

  const enum textureInd {
    BASE_TEX = 0,
    HOVER_TEX = 1,
    MOVABLE_TEX = 2,
    ENEMY_TEX = 3,
    ACTICE_TEX = 4
  };
};
