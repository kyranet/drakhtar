// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#pragma once
#include "UnitsController.h"

class AIController final : public UnitsController {
 public:
  AIController(Board* board, TurnBar* turnBar, GameScene* scene);

  /**
   * \brief Is called every time an event is capture to process it.
   * \param event: The event to be processed.
   */
  // void run() override;

  /**
   * \brief Ends unit's turn and updates active unit.
   */
  void advanceTurn();
};
