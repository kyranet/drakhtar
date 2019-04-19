// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#pragma once
#include "UnitsController.h"
#include "EventListeners/ListenerOnClick.h"

class PlayerController final : public UnitsController, public ListenerOnClick {
 public:
  PlayerController(Board *board, TurnBar *turnBar, GameScene *scene);

  /**
   * \brief Is called every time an event is capture to process it.
   * \param event: The event to be processed.
   */
  void run(SDL_Event event) override;

  /**
   * \brief Moves active unit to an empty cell within range.
   * \param boxClicked: The box where the unit should move.
   */
  void onClickMove(Box *boxClicked);

  /**
   * \brief Makes active unit attack another unit clicked
   * \param boxClicked: The box containing the unit that will receive the
   * attack.
   */
  void onClickAttack(Box *boxClicked);

  /**
   * \brief Resets board textures, ends unit's turn and updates active unit.
   */
  void advanceTurn();

  void start() override;
  void finish() override;
};
