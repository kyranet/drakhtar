// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#pragma once
#include "ListenerOnClick.h"

class DialogSceneOnClick final : public ListenerOnClick {
 public:
  explicit DialogSceneOnClick(GameObject *gameObject)
      : ListenerOnClick(gameObject) {}
  void onClickStart() override;
};
