// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#pragma once
#include <string>

#include "Scenes/GameScene.h"

class Commander;

class Skill {
 protected:
  std::string id_;
  Commander* caster_;
  int cooldown_;
  int duration_;
  int remainingCooldown_ = 0;
  int remainingDuration_ = 0;
  bool active_ = false;

 public:
  Skill(std::string id, int cooldown, int duration, Commander* caster);
  virtual ~Skill() = default;

  virtual void cast(GameScene* scene) = 0;
  virtual void end() = 0;

  bool getActive() const { return active_; }
  int getRemainingCooldown() const { return remainingCooldown_; }
  int getRemainingDuration() const { return remainingDuration_; }
  void setRemainingCooldown(const int turns) { remainingCooldown_ = turns; }
  void setRemainingDuration(const int turns) { remainingDuration_ = turns; }
};

class BattleCry final : public Skill {
 public:
  explicit BattleCry(Commander* caster);
  virtual ~BattleCry() = default;

  void cast(GameScene* scene) override;
  void end() override;
  void resetAttack();
};

class ArrowRain final : public Skill {
 public:
  explicit ArrowRain(Commander* caster);
  virtual ~ArrowRain() = default;

  void cast(GameScene* scene) override;
  void end() override;
};

class HeroicStrike final : public Skill {
  double attackIncrement_;

 public:
  explicit HeroicStrike(Commander* caster);
  virtual ~HeroicStrike() = default;

  void cast(GameScene* scene) override;
  void end() override;
};
