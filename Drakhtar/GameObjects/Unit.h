// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#pragma once
#include <string>
#include "GameObject.h"

class Team;
class Box;
class Text;
class Scene;

class Unit : public GameObject {
  int baseAttack_;
  int baseSpeed_;

  int attack_;
  int defense_;
  int maxHealth_;
  int attackRange_;
  int moveRange_;
  int speed_;
  int prize_;

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

 public:
  Unit(Scene *scene, Texture *texture, Box *box, int attack, int defense,
       int health, int speed, int attackRange, int moveRange, int prize, std::string type);
  virtual ~Unit();

  int getBaseAttack() const { return baseAttack_; }
  int getBaseSpeed() const { return baseSpeed_; }
  virtual int getAttack() const { return attack_; }
  int getIndividualAttack() const { return attack_; }
  virtual int getDefense() const { return defense_; }
  int getAttackRange() const { return attackRange_; }
  int getMoveRange() const { return moveRange_; }
  virtual int getMaxHealth() const { return maxHealth_; }
  virtual int getHealth() const { return health_; }
  virtual int getPrize() const { return prize_; }
  virtual bool getMoved() { return moved_; }
  virtual bool getMoving() { return moving_; }
  int getSpeed() const { return speed_; }
  Team *getTeam() const { return team_; }
  Box *getBox() const { return box_; }
  Vector2D<int> getBoxPosition() const { return boxPosition_; }
  std::string getType() const { return type_; }

  void setAttack(const int attack) { attack_ = attack; }
  void setSpeed(const int speed) { speed_ = speed; }
  void setMoving(const bool moving) { moving_ = moving; }
  void setMoved(const bool moved) { moved_ = moved; }
  void setTeam(Team *team) { team_ = team; }

  virtual void moveToBox(Box *box);
  virtual int loseHealth(int enemyAttack);
  void render() const override;
  virtual void attack(Unit* enemy, bool counter);

  virtual void onSelect();
  virtual void onDeselect();
};
