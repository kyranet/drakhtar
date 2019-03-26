// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#pragma once
#include <string>
#include "GameObject.h"
using namespace std;

class Team;
class Box;
class Text;
class Scene;

class Unit : public GameObject {
 private:
  int attack_;
  int defense_;
  int maxHealth_;
  int attackRange_;
  int moveRange_;
  int speed_;
  int prize_;
  bool moving_ = false;
  bool moved_ = false;
  Vector2D<int> boxPosition_;
  Team *team_ = nullptr;

 protected:
  Box *box_ = nullptr;
  Text *healthText_ = nullptr;
  int health_;
  string healthToString() const;

 public:
  Unit(Scene *scene, Texture *texture, Box *box, int attack, int defense,
       int health, int speed, int attackRange, int moveRange, int prize);
  virtual ~Unit();
  virtual int getAttack() const { return attack_; }
  virtual int getDefense() const { return defense_; }
  int getAttackRange() const { return attackRange_; }
  int getMoveRange() const { return moveRange_; }
  virtual int getMaxHealth() const { return maxHealth_; }
  virtual int getHealth() const { return health_; }
  virtual int getPrize() const { return prize_; }
  bool getMoving() const { return moving_; }
  bool getMoved() const { return moved_; }
  int getSpeed() const { return speed_; }
  Team *getTeam() const { return team_; }
  Box *getBox() const { return box_; }
  Vector2D<int> getBoxPosition() const { return boxPosition_; }
  void setMoving(bool moving);
  void setMoved(bool moved);
  void setTeam(Team *team);
  virtual void moveToBox(Box *box);
  virtual int loseHealth(int enemyAttack);
  virtual void render() const;
};
