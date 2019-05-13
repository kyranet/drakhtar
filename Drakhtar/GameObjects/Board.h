// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#pragma once
#include <list>
#include "../Utils/Matrix.h"
#include "GameObject.h"

class Box;

/**
 * \brief Assigns a name to each of the states a box can be when checked by
 * other box.
 */
enum class ObjectType {
  OUT_OF_BOARD = 0,
  OUT_OF_RANGE = 1,
  EMPTY = 2,
  ALLY = 3,
  ENEMY = 4
};

class Board final : public GameObject {
 protected:
  /**
   * \brief The number of rows and columns this board is composed of.
   */
  byte rows_, columns_;

  /**
   * \brief The size of each cell of the board (Applies to both width and
   * height).
   */
  double cellSize_;

 public:
  Board(Scene* scene, byte rows, byte columns, double cellSize);
  virtual ~Board();

  /**
   * \return The SDL_Rect the board occupies, being its position, width and
   * height.
   */
  SDL_Rect getRect() const override;

  /**
   * \return The number of rows of the board.
   */
  byte getRows() const { return rows_; }

  /**
   * \return The number of columns of the board.
   */
  byte getCols() const { return columns_; }

  /**
   * \param x: The row the box is placed in.
   * \param y: The column the box is placed in.
   * \return A pointer to de box in row "x" and column "y".
   */
  Box* getBoxAt(byte x, byte y) const;
};
