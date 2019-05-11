// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#pragma once
#include <string>

#include "GameObject.h"
#include "Utils/Constants.h"

class Team;
class Box;
class Text;
class HealthBar;
class Scene;

class Unit : public GameObject {
  bool moved_ = false;
  bool moving_ = false;
  bool hasCounterAttacked_ = false;

  Vector2D<int> boxPosition_;
  Team* team_ = nullptr;
  std::string type_;

 protected:
  Box* box_ = nullptr;
  Text* healthText_ = nullptr;
  HealthBar* healthBar_ = nullptr;
  int health_;
  std::string healthToString() const;
  int minDamage_ = 1;

  const UnitStats baseStats_;
  UnitStats stats_;

 public:
  Unit(Scene* scene, Texture* texture, Box* box, UnitStats stats,
       const std::string& type);
  virtual ~Unit();

  /*int getBaseAttack() const { return baseAttack_; }
  int getBaseSpeed() const { return baseSpeed_; }
  virtual int getAttack() const { return attack_; }
  int getIndividualAttack() const { return attack_; }
  int getStats().attackRange const { return attackRange_; }
  int getStats().moveRange const { return moveRange_; }
  virtual int getMaxHealth() const { return maxHealth_; }
  virtual int getHealth() const { return health_; }
  virtual int getPrize() const { return prize_; }
    int getSpeed() const { return speed_; }*/

  int getHealth() const { return health_; }
  virtual int getDefense() const { return stats_.defense; }
  UnitStats getBaseStats() const { return baseStats_; }
  UnitStats getStats() const { return stats_; }
  virtual bool getMoved() { return moved_; }
  virtual bool getMoving() { return moving_; }
  Team* getTeam() const { return team_; }
  Box* getBox() const { return box_; }
  Vector2D<int> getBoxPosition() const { return boxPosition_; }
  std::string getType() const { return type_; }

  bool getHasCounterAttacked() const { return hasCounterAttacked_; }
  void setHasCounterAttacked(const bool counter) {
    hasCounterAttacked_ = counter;
  }

  virtual void setAttack(const int attack) { stats_.attack = attack; }
  void setSpeed(const int speed) { stats_.speed = speed; }
  void setDefense(const int defense) { stats_.defense = defense; }
  void setMoveRange(const int range) { stats_.moveRange = range; }

  void setMoving(const bool moving) { moving_ = moving; }
  void setMoved(const bool moved) { moved_ = moved; }
  void setTeam(Team* team) { team_ = team; }

  HealthBar* getHealthBar() const { return healthBar_; }
  virtual void setHealthBar();

  virtual void moveToBox(Box* box);
  virtual int loseHealth(int enemyAttack, int minDamage);
  void update() override;
  virtual void attack(Unit* enemy, bool allowsCounter);
  virtual void kill();

  virtual void onSelect();
  virtual void onDeselect();

  virtual void setBuffed(bool buffed);
  virtual void setDebuffed(bool debuffed);
};
