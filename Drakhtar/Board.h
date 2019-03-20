// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#pragma once

#include "Box.h"
#include "Constants.h"
#include "GameObject.h"
#include "Matrix.h"

class Board : public GameObject {
 protected:
  int rows, cols;
  float marginX, marginY, cellSize;
  Box ***board;
  Matrix<int> *cellsMatrix = nullptr;

 public:
  Board(Texture *cellTexture, int r, int c, float cellSize);
  virtual ~Board();

  virtual void render() const;
  virtual void handleEvents(SDL_Event event);

  // Returns cell in board index (x, y)
  Box *getBoxAt(int x, int y);

  // Returns cell in window coordinates (x, y)
  Box *getBoxAtCoordinates(Vector2D<int> coordinates);

  // Checks if two cells are within a certain range of each other
  bool isInRange(Box *from, Box *to, int range);

  // Returns an integer matrix of the contents of cells in range of a specific
  // cell
  Matrix<int> *getCellsInRange(Box *box, int range);

  // Checks is there is one or more enemies in range
  bool isEnemyInRange(Box *box, int range);

  // Changes texture of empty cells in range
  void highlightCellsInRange(Box *box, int range);

  // Changes texture of cells with enemies in range
  void highlightEnemiesInRange(Box *box, int range);

  // Resets ALL cells to their base texture
  void resetCellsToBase();

  const enum objectType {
    OUT_OF_BOARD = 0,
    OUT_OF_RANGE = 1,
    EMPTY = 2,
    ALLY = 3,
    ENEMY = 4
  };
};
