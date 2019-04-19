// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#pragma once
#include "SDL.h"
#include <vector>

class TurnBar;
class Unit;
class GameScene;
class Board;
class Box;
class EventListener;

class UnitsController {
 protected:
  /**
   * \brief A pointer to the game board.
   */
  Board* board_;

  /**
   * \brief A pointer to the game's turn bar.
   */
  TurnBar* turnBar_;

  /**
   * \brief A pointer to the unit that has the turn.
   */
  Unit* activeUnit_;

  /**
   * \brief A pointer to the game scene.
   */
  GameScene* scene_;

  /**
   * \brief All the event listeners this controller depends on to run.
   * \attention The listeners must not be deleted in this class, but in Scene.
   */
  std::vector<EventListener*> listeners_{};

  /**
   * \brief Whether or not the active unit has already moved this turn.
   */
  bool hasMoved_ = false;

  /**
   * \brief Whether or not the active unit has already attacked this turn.
   */
  bool hasAttacked_ = false;

 public:
  UnitsController(Board* board, TurnBar* turnBar, GameScene* scene);

  /**
   * \brief Is called when this controller is ready to process data.
   */
  virtual void start();

  /**
   * \brief Is called when this controller has finished processing this turn.
   */
  virtual void finish();

  /**
   * \brief Only used on multi-player mode to close the network sockets.
   */
  virtual void end() {}

  Board* getBoard() const;
  TurnBar* getTurnBar() const;
  Unit* getActiveUnit() const;
  bool hasMoved() const;
  bool hasAttacked() const;
};
