// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#pragma once
#include "UnitsController.h"
#include "Utils/Vector2D.h"

class Button;

class PlayerController final : public UnitsController {
  bool locked_ = false;
  Button* skipTurnButton_ = nullptr;

 protected:
  void onComplete() override;

 public:
  PlayerController(Board* board, GameScene* scene, Team* team,
                   Team* oppositeTeam);

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

  bool canCastSkills();
  void highlightCells();
};
