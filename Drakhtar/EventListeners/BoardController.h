// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#pragma once
#include "ListenerOnClick.h"
#include "SDL.h"

class TurnBar;
class Unit;
class GameScene;
class Board;
class Box;

class BoardController final : public ListenerOnClick {
 protected:
  /**
   * \brief A pointer to the game board.
   */
  Board *board_;

  /**
   * \brief A pointer to the game's turn bar.
   */
  TurnBar *turnBar_;

  /**
   * \brief A pointer to the unit that has the turn.
   */
  Unit *activeUnit_;

  /**
   * \brief A pointer to the game scene.
   */
  GameScene *scene_;

  /**
   * \brief Whether or not the active unit has already moved this turn.
   */
  bool hasMoved_ = false;

  /**
   * \brief Whether or not the active unit has already attacked this turn.
   */
  bool hasAttacked_ = false;

  /**
   * \brief Whether or not the active unit currently moving.
   */
  bool isTweening_ = false;

 public:
  BoardController(Board *board, TurnBar *turnBar, GameScene *scene);

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
};
