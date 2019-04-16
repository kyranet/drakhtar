// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#pragma once
#include "EventListeners/UnitStoreController.h"
#include "GameObject.h"
class Scene;
class Text;
class Font;
class RecruitmentStat : public GameObject {
  StoreUnit *currentSelected_;

 public:
  RecruitmentStat(Scene *scene, SDL_Rect BoxArea, StoreUnit *controller);
  void render() const override;
  std::string fillText();
  ~RecruitmentStat();
};