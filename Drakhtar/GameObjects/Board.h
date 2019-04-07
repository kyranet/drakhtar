// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#pragma once
#include <list>
#include "../Utils/Matrix.h"
#include "GameObject.h"

class Box;

enum class ObjectType {
  OUT_OF_BOARD = 0,
  OUT_OF_RANGE = 1,
  EMPTY = 2,
  ALLY = 3,
  ENEMY = 4
};

class Board final : public GameObject {
 protected:
  int rows_, columns_;
  float cellSize_;
  Matrix<ObjectType> *objectTypeMatrix_ = nullptr;

 public:
  Board(Scene *scene, int rows, int columns, float cellSize);
  virtual ~Board();

  SDL_Rect getRect() const override;
  int getRows() const { return rows_; }
  int getCols() const { return columns_; }

  // Returns cell in board index (x, y)
  Box *getBoxAt(int x, int y) const;

  // Returns cell in window coordinates (x, y)
  Box *getBoxAtCoordinates(SDL_Point point) const;

  // Checks if two cells are within a certain range of each other
  bool isInRange(Box *from, Box *to, int range) const;

  // Checks if two cells are within a certain range of each other considering
  // path-finding
  bool isInMoveRange(Box *from, Box *to, int range) const;

  // Returns an integer matrix of the contents of cells in range of a specific
  // cell
  Matrix<ObjectType> *getObjectTypesInRange(Box *box, int range);

  // Checks is there is one or more enemies in range
  bool isEnemyInRange(Box *box, int range);

  // Changes texture of empty cells in range
  void highlightCellsInRange(Box *box, int range);

  // Changes texture of cells with enemies in range
  void highlightEnemiesInRange(Box *box, int range);

  // Resets ALL cells to their base texture
  void resetCellsToBase();

  std::list<Vector2D<int>> findPath(const Vector2D<int> &start,
                                    const Vector2D<int> &end) const;
  std::vector<Vector2D<double>> pathToRoute(
      std::list<Vector2D<int>> path) const;
};
