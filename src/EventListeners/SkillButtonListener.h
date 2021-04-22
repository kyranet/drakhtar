// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#pragma once

#include "ListenerOnHover.h"

class GameObject;

class SkillButtonListener final : public ListenerOnHover {
  GameObject* panel_;
 public:
  SkillButtonListener(GameObject* hoveredObject, GameObject* panel);
  ~SkillButtonListener();

  void onHoverStart() override;
  void onHoverStop() override;
};
