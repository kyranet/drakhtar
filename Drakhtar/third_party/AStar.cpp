// Copyright 2018 the daancode/a-star authors. All rights reserved. MIT license.
// (https://github.com/daancode/a-star)

#include "AStar.h"
#include <algorithm>
#include <cmath>

bool AStar::Vec2i::operator==(const Vec2i& coordinates) const {
  return (x == coordinates.x && y == coordinates.y);
}

AStar::Vec2i operator+(const AStar::Vec2i& left, const AStar::Vec2i& right) {
  return {left.x + right.x, left.y + right.y};
}

AStar::Node::Node(const Vec2i coordinates, Node* parent) {
  this->parent = parent;
  this->coordinates = coordinates;
  g = h = 0;
}

AStar::Uint AStar::Node::getScore() const { return g + h; }

AStar::Generator::Generator() {
  setDiagonalMovement(false);
  setHeuristic(&Heuristic::manhattan);
  direction_ = {{0, 1},   {1, 0}, {0, -1}, {-1, 0},
               {-1, -1}, {1, 1}, {-1, 1}, {1, -1}};
}

void AStar::Generator::setWorldSize(const Vec2i worldSize) {
  this->worldSize_ = worldSize;
}

void AStar::Generator::setDiagonalMovement(const bool enable) {
  directions_ = (enable ? 8 : 4);
}

void AStar::Generator::setHeuristic(HeuristicFunction heuristic) {
  this->heuristic_ =
      std::bind(heuristic, std::placeholders::_1, std::placeholders::_2);
}

void AStar::Generator::addCollision(const Vec2i coordinates) {
  walls_.push_back(coordinates);
}

void AStar::Generator::removeCollision(const Vec2i coordinates) {
  const auto it = std::find(walls_.begin(), walls_.end(), coordinates);
  if (it != walls_.end()) {
    walls_.erase(it);
  }
}

void AStar::Generator::clearCollisions() { walls_.clear(); }

AStar::CoordinateList AStar::Generator::findPath(const Vec2i source, const Vec2i target) {
  Node* current = nullptr;
  NodeSet openSet, closedSet;
  openSet.insert(new Node(source));

  while (!openSet.empty()) {
    current = *openSet.begin();
    for (auto node : openSet) {
      if (node->getScore() <= current->getScore()) {
        current = node;
      }
    }

    if (current->coordinates == target) {
      break;
    }

    closedSet.insert(current);
    openSet.erase(std::find(openSet.begin(), openSet.end(), current));

    for (Uint i = 0; i < directions_; ++i) {
      const auto newCoordinates(current->coordinates + direction_[i]);
      if (detectCollision(newCoordinates) ||
          findNodeOnList(closedSet, newCoordinates)) {
        continue;
      }

      const auto totalCost = current->g + ((i < 4) ? 10 : 14);

      auto successor = findNodeOnList(openSet, newCoordinates);
      if (successor == nullptr) {
        successor = new Node(newCoordinates, current);
        successor->g = totalCost;
        successor->h = heuristic_(successor->coordinates, target);
        openSet.insert(successor);
      } else if (totalCost < successor->g) {
        successor->parent = current;
        successor->g = totalCost;
      }
    }
  }

  CoordinateList path;
  while (current != nullptr) {
    path.push_back(current->coordinates);
    current = current->parent;
  }

  releaseNodes(openSet);
  releaseNodes(closedSet);

  return path;
}

AStar::Node* AStar::Generator::findNodeOnList(NodeSet& nodes,
                                              const Vec2i coordinates) {
  for (auto node : nodes) {
    if (node->coordinates == coordinates) {
      return node;
    }
  }
  return nullptr;
}

void AStar::Generator::releaseNodes(NodeSet& nodes) {
  for (auto it = nodes.begin(); it != nodes.end();) {
    delete *it;
    it = nodes.erase(it);
  }
}

bool AStar::Generator::detectCollision(const Vec2i coordinates) {
  return coordinates.x < 0 || coordinates.x >= worldSize_.x ||
         coordinates.y < 0 || coordinates.y >= worldSize_.y ||
         std::find(walls_.begin(), walls_.end(), coordinates) != walls_.end();
}

AStar::Vec2i AStar::Heuristic::getDelta(const Vec2i source, const Vec2i target) {
  return {abs(source.x - target.x), abs(source.y - target.y)};
}

AStar::Uint AStar::Heuristic::manhattan(const Vec2i source, const Vec2i target) {
  const auto delta = getDelta(source, target);
  return static_cast<Uint>(10 * (delta.x + delta.y));
}

AStar::Uint AStar::Heuristic::euclidean(const Vec2i source, const Vec2i target) {
  const auto delta = getDelta(source, target);
  return static_cast<Uint>(10 * sqrt(pow(delta.x, 2) + pow(delta.y, 2)));
}

AStar::Uint AStar::Heuristic::octagonal(const Vec2i source, const Vec2i target) {
  const auto delta = getDelta(source, target);
  return 10 * (delta.x + delta.y) + (-6) * std::min(delta.x, delta.y);
}
