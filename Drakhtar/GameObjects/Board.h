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
  int rows_, columns_;

  /**
   * \brief The size of each cell of the board (Applies to both width and
   * height).
   */
  double cellSize_;

  /**
   * \brief Auxiliary matrix that saves the last search of cells near another
   * cell.
   */
  Matrix<ObjectType> *objectTypeMatrix_ = nullptr;

 public:
  Board(Scene *scene, int rows, int columns, double cellSize);
  virtual ~Board();

  /**
   * \return The SDL_Rect the board occupies, being its position, width and
   * height.
   */
  SDL_Rect getRect() const override;

  /**
   * \return The number of rows of the board.
   */
  int getRows() const { return rows_; }

  /**
   * \return The number of columns of the board.
   */
  int getCols() const { return columns_; }

  /**
   * \param x: The row the box is placed in.
   * \param y: The column the box is placed in.
   * \return A pointer to de box in row "x" and column "y".
   */
  Box *getBoxAt(int x, int y) const;

  /**
   * \param point: A SDL_Point in the game window.
   * \return A pointer to the box the SDL_Point is over.
   */
  Box *getBoxAtCoordinates(const Vector2D<int>& point) const;

  /**
   * \brief Checks if two cells are within a certain range of each other.
   * \param from: The box from which distances will be calculated.
   * \param to: The box we are checking to be in range.
   * \param range: The number of boxes we can reach in any direction.
   * \return Whether or not the two boxes are "range" or less boxes away
   */
  bool isInRange(Box *from, Box *to, int range) const;

  /**
   * \brief Checks if two cells are within a certain range of each other,
   * considering path-finding.
   * \param from: The box from which distances will be calculated.
   * \param to: The box we are checking to be in range.
   * \param range: The number of boxes we can reach in any direction.
   * \return Whether or not the two boxes are "range" or less boxes away,
   * considering path-finding.
   */
  bool isInMoveRange(Box *from, Box *to, int range) const;

  /**
   * \brief Checks the content of cells in range of a specific cell.
   * \param box: The box from which to calculate the range.
   * \param range: The number of boxes to check in all directions.
   * \return Returns an integer matrix of the contents of cells in range.
   */
  Matrix<ObjectType> *getObjectTypesInRange(Box *box, int range);

  /**
   * \brief Checks is there is one or more enemies in range.
   * \param box: The box from which to calculate the range.
   * \param range: The number of boxes to check in all directions.
   * \return Whether or not there are one or more enemies in range.
   */
  bool isEnemyInRange(Box *box, int range);

  /**
   * \brief Changes texture of empty cells in range to the Box::MOVABLE texture.
   * \param box: The box from which to calculate the range.
   * \param range: The number of boxes to check in all directions.
   */
  void highlightCellsInRange(Box *box, int range);

  /**
   * \brief Changes texture of cells containing enemies in range to the
   * Box::ENEMY texture.
   * \param box: The box from which to calculate the range.
   * \param range: The number of boxes to check in all directions.
   */
  void highlightEnemiesInRange(Box *box, int range);

  /**
   * \brief Changes texture of ALL cells to the Box::BASE texture.
   */
  void resetCellsToBase();

  /**
   * \brief Uses AStar to find a path from one box to another, avoiding
   * obstacles.
   * \param start: The index of the box from which to start the path.
   * \param end: The index of the box where the path must end.
   * \return An ordered list of the indexes of the cells the path must follow.
   */
  std::list<Vector2D<int>> findPath(const Vector2D<int> &start,
                                    const Vector2D<int> &end) const;

  /**
   * \brief Transforms a cells path to a window coordinates path
   * \param path: An ordered list of the indexes of the cells the path follows.
   * \return An ordered list of the window coordinates the path must follow.
   */
  std::vector<Vector2D<double>> pathToRoute(
      std::list<Vector2D<int>> path) const;
};
