// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#pragma once
#include <string>
#include "GameObject.h"

class Team;
class Box;
class Text;
class Scene;

struct UnitStats {
  int attack;
  int defense;
  int health;
  int attackRange;
  int moveRange;
  int speed;
  int prize;
};
class Unit : public GameObject {
  bool moved_ = false;
  bool moving_ = false;

  Vector2D<int> boxPosition_;
  Team *team_ = nullptr;
  std::string type_;

 protected:
  Box *box_ = nullptr;
  Text *healthText_ = nullptr;
  int health_;
  std::string healthToString() const;

  const UnitStats baseStats_;
  UnitStats stats_;

 public:
  Unit(Scene *scene, Texture *texture, Box *box, UnitStats stats,
       std::string type);
  virtual ~Unit();

  /*int getBaseAttack() const { return baseAttack_; }
  int getBaseSpeed() const { return baseSpeed_; }
  virtual int getAttack() const { return attack_; }
  int getIndividualAttack() const { return attack_; }
  virtual int getDefense() const { return defense_; }
  int getStats().attackRange const { return attackRange_; }
  int getStats().moveRange const { return moveRange_; }
  virtual int getMaxHealth() const { return maxHealth_; }
  virtual int getHealth() const { return health_; }
  virtual int getPrize() const { return prize_; }
    int getSpeed() const { return speed_; }*/
  UnitStats getBaseStats() const { return baseStats_; }
  UnitStats getStats() const { return stats_; }
  virtual bool getMoved() { return moved_; }
  virtual bool getMoving() { return moving_; }
  Team *getTeam() const { return team_; }
  Box *getBox() const { return box_; }
  Vector2D<int> getBoxPosition() const { return boxPosition_; }
  std::string getType() const { return type_; }

  void setAttack(const int attack) { stats_.attack = attack; }
  void setSpeed(const int speed) { stats_.speed = speed; }
  void setMoving(const bool moving) { moving_ = moving; }
  void setMoved(const bool moved) { moved_ = moved; }
  void setTeam(Team *team) { team_ = team; }

  virtual void moveToBox(Box *box);
  virtual int loseHealth(int enemyAttack);
  void render() const override;
  virtual void attack(Unit *enemy, bool counter);

  virtual void onSelect();
  virtual void onDeselect();
};
