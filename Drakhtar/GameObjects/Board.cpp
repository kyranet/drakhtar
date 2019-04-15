// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#include "Board.h"
#include "../Utils/Constants.h"
#include "../third_party/AStar.h"
#include "Box.h"
#include "Unit.h"

Board::Board(Scene *scene, const int rows, const int columns,
             const float cellSize)
    : GameObject(scene, nullptr, Vector2D<int>(0, 0), Vector2D<int>(0, 0)),
      rows_(rows),
      columns_(columns),
      cellSize_(cellSize) {
  // Calculates margins to center the board on screen
  size_.set(static_cast<int>(floor(columns_ * cellSize_)),
            static_cast<int>(floor(rows_ * cellSize_)));
  position_.set(static_cast<int>(floor((WIN_WIDTH - size_.getX()) / 2)),
                static_cast<int>(floor((WIN_HEIGHT - size_.getY()) / 2)));

  // Fills the board with empty boxes
  for (auto x = 0; x < columns_; x++) {
    for (auto y = 0; y < rows_; y++) {
      auto pos = Vector2D<int>(
          static_cast<int>(floor(position_.getX() + x * cellSize_)),
          static_cast<int>(floor(position_.getY() + y * cellSize_)));
      const auto size = Vector2D<int>(static_cast<int>(floor(cellSize_)),
                                      static_cast<int>(floor(cellSize_)));
      const auto box = new Box(scene, pos, size, Vector2D<int>(x, y), nullptr);
      addChild(box);
    }
  }
}

Board::~Board() { delete objectTypeMatrix_; }

SDL_Rect Board::getRect() const {
  return {position_.getX(), position_.getY(), size_.getX(), size_.getY()};
}

Box *Board::getBoxAt(const int x, const int y) const {
  return reinterpret_cast<Box *>(children_[x * rows_ + y]);
}

Box *Board::getBoxAtCoordinates(const Vector2D<int>& point) const {
  const auto x =
      static_cast<int>(floor((point.getX() - position_.getX()) / cellSize_));
  if (x < 0 || x >= columns_) return nullptr;

  const auto y =
      static_cast<int>(floor((point.getY() - position_.getY()) / cellSize_));
  if (y < 0 || y >= rows_) return nullptr;

  return getBoxAt(x, y);
}

bool Board::isInRange(Box *from, Box *to, const int range) const {
  auto fromCoords = from->getIndex();
  auto toCoords = to->getIndex();

  const auto distanceX = abs((toCoords.getX() - fromCoords.getX()));
  const auto distanceY = abs((toCoords.getY() - fromCoords.getY()));
  const auto totalDistance = distanceX + distanceY;

  return range >= totalDistance;
}

bool Board::isInMoveRange(Box *from, Box *to, const int range) const {
  auto path = findPath(from->getIndex(), to->getIndex());
  return range >= static_cast<const int>(path.size() - 1);
}

Matrix<ObjectType> *Board::getObjectTypesInRange(Box *box, const int range) {
  // Reset the cells matrix
  delete objectTypeMatrix_;
  const auto team = box->getContent()->getTeam();
  objectTypeMatrix_ = new Matrix<ObjectType>(columns_, rows_);

  // Fills the array
  for (int x = 0; x < columns_; x++) {
    for (int y = 0; y < rows_; y++) {
      ObjectType type;
      if (!isInRange(box, getBoxAt(x, y), range)) {
        type = ObjectType::OUT_OF_RANGE;
      } else {
        const auto unit = getBoxAt(x, y)->getContent();
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

bool Board::isEnemyInRange(Box *box, const int range) {
  getObjectTypesInRange(box, range);

  for (auto x = 0; x < columns_; x++) {
    for (auto y = 0; y < rows_; y++) {
      if (objectTypeMatrix_->getElement(x, y) == ObjectType::ENEMY) {
        return true;
      }
    }
  }

  return false;
}

void Board::highlightCellsInRange(Box *box, const int range) {
  getObjectTypesInRange(box, range);

  for (auto x = 0; x < columns_; x++) {
    for (auto y = 0; y < rows_; y++) {
      if (objectTypeMatrix_->getElement(x, y) == ObjectType::EMPTY) {
        if (isInMoveRange(box, getBoxAt(x, y), range)) {
          getBoxAt(x, y)->setCurrentTexture(TextureInd::MOVABLE);
        }
      }
    }
  }
}

void Board::highlightEnemiesInRange(Box *box, const int range) {
  getObjectTypesInRange(box, range);

  for (auto x = 0; x < columns_; x++) {
    for (auto y = 0; y < rows_; y++) {
      if (objectTypeMatrix_->getElement(x, y) == ObjectType::ENEMY) {
        getBoxAt(x, y)->setCurrentTexture(TextureInd::ENEMY);
      }
    }
  }
}

void Board::resetCellsToBase() {
  for (const auto box : children_)
    reinterpret_cast<Box *>(box)->setCurrentTexture(TextureInd::BASE);
}

std::list<Vector2D<int>> Board::findPath(const Vector2D<int> &start,
                                         const Vector2D<int> &end) const {
  // Create path generator
  AStar::Generator generator;
  generator.setWorldSize({columns_, rows_});
  generator.setHeuristic(
      AStar::Heuristic::euclidean);  // manhattan, euclidean or octagonal
  generator.setDiagonalMovement(false);

  // Load board obstacles
  for (auto x = 0; x < columns_; x++) {
    for (auto y = 0; y < rows_; y++) {
      if (getBoxAt(x, y)->getContent() != nullptr) {
        generator.addCollision({x, y});
      }
    }
  }

  // Remove itself as an obstacle
  generator.removeCollision({start.getX(), start.getY()});

  // Find path
  std::list<Vector2D<int>> pathList;
  auto path = generator.findPath({start.getX(), start.getY()},
                                 {end.getX(), end.getY()});

  for (auto &coordinate : path) {
    pathList.push_front({coordinate.x, coordinate.y});
  }

  return pathList;
}

std::vector<Vector2D<double>> Board::pathToRoute(
    std::list<Vector2D<int>> path) const {
  std::vector<Vector2D<double>> vector;
  vector.reserve(path.size());
  for (const auto &element : path) {
    const auto box = getBoxAt(element.getX(), element.getY());
    const auto pos = box->getPosition();
    const auto size = box->getSize();
    vector.emplace_back(pos.getX() + size.getX() / 2.0,
                        pos.getY() + size.getY() / 2.0);
  }
  return vector;
}
