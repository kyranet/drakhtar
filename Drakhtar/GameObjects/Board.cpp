// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#include "Board.h"
#include "Box.h"
#include "Unit.h"
#include "Utils/Constants.h"
#include "third_party/AStar.h"

Board::Board(Scene* scene, const byte rows, const byte columns,
             const double cellSize)
    : GameObject(scene, nullptr, Vector2D<int>(0, 0), Vector2D<int>(0, 0)),
      rows_(rows),
      columns_(columns),
      cellSize_(cellSize) {
  // Calculates margins to center the board on screen
  size_.set(static_cast<int>(columns_ * cellSize_),
            static_cast<int>(rows_ * cellSize_));
  position_.set(static_cast<int>((WIN_WIDTH - size_.getX()) / 2),
                static_cast<int>((WIN_HEIGHT - size_.getY()) / 2));

  // Fills the board with empty boxes
  for (byte x = 0; x < columns_; x++) {
    for (byte y = 0; y < rows_; y++) {
      auto pos =
          Vector2D<int>(static_cast<int>(position_.getX() + x * cellSize_),
                        static_cast<int>(position_.getY() + y * cellSize_));
      const auto size = Vector2D<int>(static_cast<int>(cellSize_),
                                      static_cast<int>(cellSize_));
      const auto box = new Box(scene, pos, size, Vector2D<byte>(x, y));
      addChild(box);
    }
  }
}

Board::~Board() = default;

SDL_Rect Board::getRect() const {
  return {position_.getX(), position_.getY(), size_.getX(), size_.getY()};
}

Box* Board::getBoxAt(const byte x, const byte y) const {
  return reinterpret_cast<Box*>(children_[x * rows_ + y]);
}
