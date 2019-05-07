// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#pragma once
#include "UnitsController.h"

class Button;

class PlayerController final : public UnitsController {
  bool locked_ = false;
  Button* skipTurnButton_ = nullptr;
  bool firstMoved_;
  bool firstAttacked_;
  bool firstSkill_;

 public:
  PlayerController(Board* board, TurnManager* turnManager, GameScene* scene,
                   Team* team, Team* oppositeTeam);

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

  void setMoved_(bool moved);
  bool getMoved();
  void setAttacked(bool attacked);
  bool getAttacked();
  void setFirstSkill(bool firstSkill);
  bool getFirstSkill();

  bool canCastSkills();
  void highlightCells();
};
