// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#pragma once
#include "ListenerOnClick.h"

class TutorialSceneOnClick final : public ListenerOnClick {
 public:
  explicit TutorialSceneOnClick(GameObject *gameObject)
      : ListenerOnClick(gameObject) {}
  void onClickStop() override;
};
