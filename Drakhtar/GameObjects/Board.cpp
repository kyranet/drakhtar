// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#include "Board.h"
#include <algorithm>
#include "../Utils/Constants.h"
#include "Box.h"
#include "Unit.h"

Board::Board(Scene *scene, int rows, int columns, float cellSize)
    : GameObject(scene, nullptr, Vector2D<int>(0, 0), Vector2D<int>(0, 0)),
      rows_(rows),
      columns_(columns),
      cellSize_(cellSize) {
  // Calculates margins to center the board on screen
  size_.set(static_cast<int>(floor(columns_ * cellSize_)),
            static_cast<int>(floor(rows_ * cellSize_)));
  position_.set(static_cast<int>(floor((WIN_WIDTH - size_.getX()) / 2)),
                static_cast<int>(floor((WIN_HEIGHT - size_.getY()) / 2)));

  // Creates the board matrix
  board_ = new Box **[columns_];

  // Fills the board with empty boxes
  for (int x = 0; x < columns_; x++) {
    board_[x] = new Box *[rows_];
    for (int y = 0; y < rows_; y++) {
      auto pos = Vector2D<int>(
          static_cast<int>(floor(position_.getX() + x * cellSize_)),
          static_cast<int>(floor(position_.getY() + y * cellSize_)));
      auto size = Vector2D<int>(static_cast<int>(floor(cellSize_)),
                                static_cast<int>(floor(cellSize_)));
      auto box = new Box(scene, pos, size, Vector2D<int>(x, y), nullptr);
      board_[x][y] = box;
    }
  }
}

Board::~Board() {
  if (board_ != nullptr) {
    for (int x = 0; x < columns_; x++) {
      for (int y = 0; y < rows_; y++) {
        delete board_[x][y];
      }
      delete[] board_[x];
    }
    delete[] board_;
    board_ = nullptr;
  }
  delete objectTypeMatrix_;
}

SDL_Rect Board::getRect() const {
  return {position_.getX(), position_.getY(), size_.getX(), size_.getY()};
}

void Board::render() const {
  // Renders each cell and it's content
  for (int i = 0; i < columns_; i++) {
    for (int j = 0; j < rows_; j++) {
      if (board_[i][j] != nullptr) {
        board_[i][j]->render();
      }
    }
  }
}

void Board::handleEvents(SDL_Event event) {
  for (int i = 0; i < columns_; i++) {
    for (int j = 0; j < rows_; j++) {
      board_[i][j]->handleEvents(event);
    }
  }
  GameObject::handleEvents(event);
}

Box *Board::getBoxAt(int x, int y) { return board_[x][y]; }

Box *Board::getBoxAtCoordinates(SDL_Point point) {
  int x = static_cast<int>(floor((point.x - position_.getX()) / cellSize_));
  if (x < 0 || x >= columns_) return nullptr;

  int y = static_cast<int>(floor((point.y - position_.getY()) / cellSize_));
  if (y < 0 || y >= rows_) return nullptr;

  return getBoxAt(x, y);
}

bool Board::isInRange(Box *from, Box *to, int range) {
  Vector2D<int> fromCoords = from->getIndex();
  Vector2D<int> toCoords = to->getIndex();

  int distanceX = abs((toCoords.getX() - fromCoords.getX()));
  int distanceY = abs((toCoords.getY() - fromCoords.getY()));
  int totalDistance = distanceX + distanceY;

  return range >= totalDistance;
}

Matrix<ObjectType> *Board::getObjectTypesInRange(Box *box, int range) {
  // Reset the cells matrix
  if (objectTypeMatrix_ != nullptr) {
    delete objectTypeMatrix_;
  }

  auto team = box->getContent()->getTeam();
  objectTypeMatrix_ = new Matrix<ObjectType>(columns_, rows_);

  // Fills the array
  for (int x = 0; x < columns_; x++) {
    for (int y = 0; y < rows_; y++) {
      ObjectType type;
      if (!isInRange(box, getBoxAt(x, y), range)) {
        type = ObjectType::OUT_OF_RANGE;
      } else {
        auto unit = getBoxAt(x, y)->getContent();
        if (unit == nullptr) {
          type = ObjectType::EMPTY;
        } else if (unit->getTeam() == team) {
          type = ObjectType::ALLY;
        } else {
          type = ObjectType::ENEMY;
        }
      }

      objectTypeMatrix_->setElement(x, y, type);
    }
  }
  return objectTypeMatrix_;
}

bool Board::isEnemyInRange(Box *box, int range) {
  getObjectTypesInRange(box, range);

  for (int x = 0; x < columns_; x++) {
    for (int y = 0; y < rows_; y++) {
      if (objectTypeMatrix_->getElement(x, y) == ObjectType::ENEMY) {
        return true;
      }
    }
  }

  return false;
}

void Board::highlightCellsInRange(Box *box, int range) {
  getObjectTypesInRange(box, range);

  for (int x = 0; x < columns_; x++) {
    for (int y = 0; y < rows_; y++) {
      if (objectTypeMatrix_->getElement(x, y) == ObjectType::EMPTY) {
        getBoxAt(x, y)->setCurrentTexture(TextureInd::MOVABLE);
      }
    }
  }
}

void Board::highlightEnemiesInRange(Box *box, int range) {
  getObjectTypesInRange(box, range);

  for (int x = 0; x < columns_; x++) {
    for (int y = 0; y < rows_; y++) {
      if (objectTypeMatrix_->getElement(x, y) == ObjectType::ENEMY) {
        getBoxAt(x, y)->setCurrentTexture(TextureInd::ENEMY);
      }
    }
  }
}

void Board::resetCellsToBase() {
  for (int x = 0; x < columns_; x++) {
    for (int y = 0; y < rows_; y++) {
      board_[x][y]->setCurrentTexture(TextureInd::BASE);
    }
  }
}
