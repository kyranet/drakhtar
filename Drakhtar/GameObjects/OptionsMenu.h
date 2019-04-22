// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.
#pragma once

#include "GameObject.h"
class OptionsMenu : public GameObject {
  /*GameObject* greenTick;
  GameObject* soundIcon;
  GameObject* muteIcon;
  */
 public:
  explicit OptionsMenu(Scene* scene);
  ~OptionsMenu();
  void render() const override;
};
