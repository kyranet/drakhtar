// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#pragma once
#include "EventListeners/StoreListener.h"
#include "GameObject.h"
class Scene;
class Text;
class Font;
class RecruitmentStat : public GameObject {
  StoreUnit *currentSelected_;

 public:
  RecruitmentStat(Scene *scene, StoreUnit *controller);
  void render() const override;
  std::string fillText();
  void updateText();
  ~RecruitmentStat();
};
