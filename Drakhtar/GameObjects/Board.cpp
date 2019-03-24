// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#include "Board.h"
#include "../Utils/Constants.h"
#include "Box.h"
#include "Unit.h"

Board::Board(Scene *scene, int rows, int columns, float cellSize)
    : GameObject(scene, nullptr, Vector2D<int>(0, 0), Vector2D<int>(0, 0)),
      rows_(rows),
      columns_(columns),
      cellSize_(cellSize) {
  // Calculates margins to center the board on screen
  marginX_ = (WIN_WIDTH - (cellSize_ * (columns_ - 1))) / 2;
  marginY_ = (WIN_HEIGHT - (cellSize_ * (rows_ - 1))) / 2;

  // Creates the board matrix
  board_ = new Box **[rows_];
  for (int i = 0; i < rows_; i++) {
    board_[i] = new Box *[columns_];
  }

  // Fills the board with empty boxes
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < columns_; j++) {
      auto pos =
          Vector2D<int>(static_cast<int>(floor(marginX_ + j * cellSize_)),
                        static_cast<int>(floor(marginY_ + i * cellSize_)));
      auto size = Vector2D<int>(static_cast<int>(floor(cellSize_)),
                                static_cast<int>(floor(cellSize_)));
      auto box = new Box(scene, pos, size, Vector2D<int>(j, i), nullptr);
      board_[i][j] = box;
    }
  }
}

Board::~Board() {
  if (board_ != nullptr) {
    for (int r = 0; r < rows_; r++) {
      for (int c = 0; c < columns_; c++) {
        delete board_[r][c];
      }
      delete[] board_[r];
    }
    delete[] board_;
    board_ = nullptr;
  }
  delete cellsMatrix_;
}

void Board::render() const {
  // Renders each cell and it's content
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < columns_; j++) {
      if (board_[i][j] != nullptr) {
        board_[i][j]->render();
      }
    }
  }
}

void Board::handleEvents(SDL_Event event) {
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < columns_; j++) {
      board_[i][j]->handleEvents(event);
    }
  }
}

Box *Board::getBoxAt(int x, int y) { return board_[y][x]; }

Box *Board::getBoxAtCoordinates(Vector2D<int> coordinates) {
  // Coordinates are out of the board
  if (coordinates.getX() < marginX_ - cellSize_ / 2 ||
      coordinates.getY() < marginY_ - cellSize_ / 2 ||
      coordinates.getX() > marginX_ + columns_ * cellSize_ - cellSize_ / 2 ||
      coordinates.getY() > marginY_ + rows_ * cellSize_ - cellSize_ / 2) {
    return nullptr;
  } else {
    // Coordinates are inside the board
    int x = static_cast<int>(
        floor((coordinates.getX() - marginX_ + cellSize_ / 2) / cellSize_));
    int y = static_cast<int>(
        floor((coordinates.getY() - marginY_ + cellSize_ / 2) / cellSize_));
    return getBoxAt(x, y);
  }
}

bool Board::isInRange(Box *from, Box *to, int range) {
  Vector2D<int> fromCoords = from->getIndex();
  Vector2D<int> toCoords = to->getIndex();

  int distanceX = abs((toCoords.getX() - fromCoords.getX()));
  int distanceY = abs((toCoords.getY() - fromCoords.getY()));
  int totalDistance = distanceX + distanceY;

  return range >= totalDistance;
}

Matrix<ObjectType> *Board::getCellsInRange(Box *box, int range) {
  // Reset the cells matrix
  if (cellsMatrix_ != nullptr) {
    delete cellsMatrix_;
  }

  int size = range * 2 + 1;
  int startX = box->getIndex().getX() - range;
  int startY = box->getIndex().getY() - range;
  cellsMatrix_ = new Matrix<ObjectType>(size, size);

  // Fills the array
  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      if (j + startX < 0 || i + startY < 0 || j + startX >= columns_ ||
          i + startY >= rows_) {
        // Current cell is out of the board
        cellsMatrix_->setElement(j, i, ObjectType::OUT_OF_BOARD);
      } else if (!isInRange(box, getBoxAt(j + startX, i + startY), range)) {
        // Current cell is out of the movement range
        cellsMatrix_->setElement(j, i, ObjectType::OUT_OF_RANGE);
      } else {
        // Current cell is in the board and in range
        Unit *unit = board_[i + startY][j + startX]->getContent();

        if (unit == nullptr) {
          // Current cell is empty
          cellsMatrix_->setElement(j, i, ObjectType::EMPTY);
        } else {
          // Current cell is occupied
          if (unit->getTeam() == box->getContent()->getTeam()) {
            // Ally
            cellsMatrix_->setElement(j, i, ObjectType::ALLY);
          } else {
            // Enemy
            cellsMatrix_->setElement(j, i, ObjectType::ENEMY);
          }
        }
      }
    }
  }
  return cellsMatrix_;
}

bool Board::isEnemyInRange(Box *box, int range) {
  cellsMatrix_ = getCellsInRange(box, range);
  int size = range * 2 + 1;
  bool enemyFound = false;
  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      if (cellsMatrix_->getElement(i, j) == ObjectType::ENEMY) {
        enemyFound = true;
      }
    }
  }

  return enemyFound;
}

void Board::highlightCellsInRange(Box *box, int range) {
  cellsMatrix_ = getCellsInRange(box, range);
  int size = range * 2 + 1;
  int startX = box->getIndex().getX() - range;
  int startY = box->getIndex().getY() - range;

  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      if (cellsMatrix_->getElement(i, j) == ObjectType::EMPTY) {
        if (getBoxAt(i + startX, j + startY)->getCurrentTexture() !=
            TextureInd::HOVER) {
          getBoxAt(i + startX, j + startY)
              ->setCurrentTexture(TextureInd::MOVABLE);
        }
      }
    }
  }
}

void Board::highlightEnemiesInRange(Box *box, int range) {
  cellsMatrix_ = getCellsInRange(box, range);
  int size = range * 2 + 1;
  int startX = box->getIndex().getX() - range;
  int startY = box->getIndex().getY() - range;

  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      if (cellsMatrix_->getElement(i, j) == ObjectType::ENEMY) {
        if (getBoxAt(i + startX, j + startY)->getCurrentTexture() !=
            TextureInd::HOVER) {
          getBoxAt(i + startX, j + startY)
              ->setCurrentTexture(TextureInd::ENEMY);
        }
      }
    }
  }
}

void Board::resetCellsToBase() {
  for (int i = 0; i < columns_; i++) {
    for (int j = 0; j < rows_; j++) {
      board_[j][i]->setCurrentTexture(TextureInd::BASE);
    }
  }
}
