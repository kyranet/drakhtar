// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#pragma once
#include "Board.h"
#include "Commanders/Commander.h"
#include "GameObject.h"

class SkillButton : public GameObject {
 private:
  Commander* commander_;
  int skill_;
  Board* board_;

 public:
  SkillButton(Scene* scene, Texture* texture, Vector2D<int> pos,
              Vector2D<int> size, Board* board, Commander* commander,
              int skill);
  void handleEvents(SDL_Event e);
};
