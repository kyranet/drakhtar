// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#pragma once
#include "EventListeners/ListenerOnClick.h"
#include "UnitsController.h"

class PlayerController final : public UnitsController {
  bool locked_ = true;

 public:
  PlayerController(Board* board, TurnBar* turnBar, GameScene* scene);

  /**
   * \brief Moves active unit to an empty cell within range.
   * \param boxClicked: The box where the unit should move.
   */
  void onClickMove(Box* boxClicked);

  /**
   * \brief Makes active unit attack another unit clicked
   * \param boxClicked: The box containing the unit that will receive the
   * attack.
   */
  void onClickAttack(Box* boxClicked);

  void start() override;
  void finish() override;

  bool getLocked() const;
};
