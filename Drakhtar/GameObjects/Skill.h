// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#pragma once
#include <string>
#include "Board.h"
#include "Unit.h"

class Skill {
 protected:
  std::string id_;
  Unit* caster_;
  int cooldown_;
  int duration_;
  int remainingCooldown_ = 0;
  int remainingDuration_ = 0;
  bool active_ = false;

 public:
  Skill(std::string id, int cooldown, int duration, Unit* caster);
  virtual ~Skill() {}

  virtual void cast(Board* board) = 0;
  virtual void end() = 0;

  bool getActive() { return active_; }
  int getRemainingCooldown() { return remainingCooldown_; }
  int getRemainingDuration() { return remainingDuration_; }
  void setRemainingCooldown(int turns) { remainingCooldown_ = turns; }
  void setRemainingDuration(int turns) { remainingDuration_ = turns; }
};

class BattleCry : public Skill {
 public:
  explicit BattleCry(Unit* caster);
  virtual ~BattleCry() {}

  virtual void cast(Board* board);
  virtual void end();
  void resetAttack();
};

class ArrowRain : public Skill {
 public:
  explicit ArrowRain(Unit* caster);
  virtual ~ArrowRain() {}

  virtual void cast(Board* board);
  virtual void end();
};
