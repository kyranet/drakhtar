/*
    Copyright (c) 2015, Damian Barczynski <daan.net@wp.eu>
    Following tool is licensed under the terms and conditions of the ISC
   license. For more information visit https://opensource.org/licenses/ISC.
*/
#ifndef DRAKHTAR_THIRD_PARTY_ASTAR_H_
#define DRAKHTAR_THIRD_PARTY_ASTAR_H_

#include <functional>
#include <set>
#include <vector>

namespace AStar {
struct Vec2i {
  int x, y;

  bool operator==(const Vec2i& coordinates_) const;
};

using uint = unsigned int;
using HeuristicFunction = std::function<uint(Vec2i, Vec2i)>;
using CoordinateList = std::vector<Vec2i>;

struct Node {
  uint G, H;
  Vec2i coordinates{};
  Node* parent;

  explicit Node(Vec2i coord_, Node* parent_ = nullptr);
  uint getScore() const;
};

using NodeSet = std::set<Node*>;

class Generator {
  bool detectCollision(Vec2i coordinates_);
  static Node* findNodeOnList(NodeSet& nodes_, Vec2i coordinates_);
  static void releaseNodes(NodeSet& nodes_);

 public:
  Generator();
  void setWorldSize(Vec2i worldSize_);
  void setDiagonalMovement(bool enable_);
  void setHeuristic(HeuristicFunction heuristic_);
  CoordinateList findPath(Vec2i source_, Vec2i target_);
  void addCollision(Vec2i coordinates_);
  void removeCollision(Vec2i coordinates_);
  void clearCollisions();

 private:
  HeuristicFunction heuristic;
  CoordinateList direction, walls;
  Vec2i worldSize{};
  uint directions{};
};

class Heuristic {
  static Vec2i getDelta(Vec2i source_, Vec2i target_);

 public:
  static uint manhattan(Vec2i source_, Vec2i target_);
  static uint euclidean(Vec2i source_, Vec2i target_);
  static uint octagonal(Vec2i source_, Vec2i target_);
};
}  // namespace AStar

#endif  // DRAKHTAR_THIRD_PARTY_ASTAR_H_