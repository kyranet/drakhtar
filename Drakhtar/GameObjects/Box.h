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

class Box final : public GameObject {
 protected:
  Vector2D<int> boardIndex_;
  Unit *content_;
  TextureInd cellTexture_;
  bool hovered_ = false;
  Texture *cellTextures_[5]{};
  const Vector2D<int> size_;

 public:
  Box(Scene *scene, const Vector2D<int> &pos, const Vector2D<int> &size,
      const Vector2D<int> &boardIndex, Unit *unit);

  SDL_Rect getRect() const override;
  void render() const override;
  void update() override;

  // Getters and Setters
  bool isEmpty() const;
  Vector2D<int> getIndex() const;

  Unit *getContent() const;
  void setContent(Unit *content);

  TextureInd getCurrentTexture() const;
  void setCurrentTexture(TextureInd cellTexture);
};
