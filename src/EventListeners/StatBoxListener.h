// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#pragma once

#include "ListenerOnHover.h"

class Board;
class UnitDescriptionBox;

class StatBoxListener final : public ListenerOnHover {
  Board* board_ = nullptr;
  UnitDescriptionBox* statsPanel_;

 public:
  StatBoxListener(Board* board, UnitDescriptionBox* statsPanel);
  ~StatBoxListener();

  void run(SDL_Event event) override;
  void onHoverStay() override;
  void onHoverStop() override;
};
