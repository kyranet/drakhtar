// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#pragma once
#include <vector>
#include "SDL.h"

class TurnManager;
class Unit;
class GameScene;
class Board;
class Box;
class EventListener;
class Team;

class UnitsController {
 protected:
  /**
   * \brief A pointer to the game board.
   */
  Board* board_;

  /**
   * \brief A pointer to the game's turn manager.
   */
  TurnManager* turnManager_;

  /**
   * \brief A pointer to the unit that has the turn.
   */
  Unit* activeUnit_ = nullptr;

  /**
   * \brief A pointer to the game scene.
   */
  GameScene* scene_;

  /**
   * \brief The team that manages this controller.
   */
  Team* team_;

  /**
   * \brief The opposite team.
   */
  Team* oppositeTeam_;

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
  UnitsController(Board* board, TurnManager* turnManager, GameScene* scene,
                  Team* team, Team* oppositeTeam);

  virtual ~UnitsController();

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
  TurnManager* getTurnManager() const;
  Unit* getActiveUnit() const;
  bool hasMoved() const;
  bool hasAttacked() const;
};
