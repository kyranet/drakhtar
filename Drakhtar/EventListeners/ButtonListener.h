// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#pragma once
#include "ListenerOnClick.h"

class ButtonListener : public ListenerOnClick {
 public:
  explicit ButtonListener(GameObject* gameObject)
      : ListenerOnClick(gameObject) {}

  void onClickStart() override;
};
