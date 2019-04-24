// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#pragma once
#include "EventListeners/StoreListener.h"
#include "GameObject.h"

class Scene;
class Text;
class Font;
class SkillButton;

class SkillDescriptionBox : public GameObject {
  SkillButton* skillButton_;
 public:
  SkillDescriptionBox(Scene* scene, SkillButton* skillButton);
  ~SkillDescriptionBox() = default;

  void render() const override;
  std::string fillText();
  void updateText();
};
