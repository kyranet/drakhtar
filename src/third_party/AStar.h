/*
    Copyright (c) 2015, Damian Barczynski <daan.net@wp.eu>
    Following tool is licensed under the terms and conditions of the ISC
   license. For more information visit https://opensource.org/licenses/ISC.
*/

#pragma once
#include <functional>
#include <set>
#include <vector>

namespace AStar {
struct Vec2i {
  int x, y;

  bool operator==(const Vec2i& coordinates) const;
};

using Uint = unsigned int;
using HeuristicFunction = std::function<Uint(Vec2i, Vec2i)>;
using CoordinateList = std::vector<Vec2i>;

struct Node {
  Uint g, h;
  Vec2i coordinates{};
  Node* parent;

  explicit Node(Vec2i coordinates, Node* parent = nullptr);
  Uint getScore() const;
};

using NodeSet = std::set<Node*>;

class Generator {
  bool detectCollision(Vec2i coordinates);
  static Node* findNodeOnList(NodeSet& nodes, Vec2i coordinates);
  static void releaseNodes(NodeSet& nodes);

 public:
  Generator();
  void setWorldSize(Vec2i worldSize);
  void setDiagonalMovement(bool enable);
  void setHeuristic(HeuristicFunction heuristic);
  CoordinateList findPath(Vec2i source, Vec2i target);
  void addCollision(Vec2i coordinates);
  void removeCollision(Vec2i coordinates);
  void clearCollisions();

 private:
  HeuristicFunction heuristic_;
  CoordinateList direction_, walls_;
  Vec2i worldSize_{};
  Uint directions_{};
};

class Heuristic {
  static Vec2i getDelta(Vec2i source, Vec2i target);

 public:
  static Uint manhattan(Vec2i source, Vec2i target);
  static Uint euclidean(Vec2i source, Vec2i target);
  static Uint octagonal(Vec2i source, Vec2i target);
};
}  // namespace AStar
