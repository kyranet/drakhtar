// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#pragma once
#include <string>

#include "Scenes/GameScene.h"

class Commander;
class Texture;

class Skill {
 protected:
  std::string id_;
  std::string description_ = " ";
  Commander* caster_;
  int cooldown_;
  int duration_;
  int remainingCooldown_ = 0;
  int remainingDuration_ = 0;
  bool active_ = false;

 public:
  Skill(const std::string& id, int cooldown, int duration, Commander* caster);
  virtual ~Skill() = default;

  virtual void cast(GameScene* scene);
  virtual void end(GameScene* scene);

  std::string getId() const { return id_; }
  std::string getDescription() const { return description_; }
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
  void end(GameScene* scene) override;
};

class ArrowRain final : public Skill {
  int range = 5;

 public:
  explicit ArrowRain(Commander* caster);
  virtual ~ArrowRain() = default;

  void cast(GameScene* scene) override;
  void end(GameScene* scene) override;
};

class HeroicStrike final : public Skill {
  double attackIncrement_;

 public:
  explicit HeroicStrike(Commander* caster);
  virtual ~HeroicStrike() = default;

  void cast(GameScene* scene) override;
  void end(GameScene* scene) override;
};

class WitheringCurse final : public Skill {
 public:
  explicit WitheringCurse(Commander* caster);
  virtual ~WitheringCurse() = default;

  void cast(GameScene* scene) override;
  void end(GameScene* scene) override;
};

class Charge final : public Skill {
 public:
  explicit Charge(Commander* caster);
  virtual ~Charge() = default;

  void cast(GameScene* scene) override;
  void end(GameScene* scene) override;
};

class Berserker final : public Skill {
 public:
  explicit Berserker(Commander* caster);
  virtual ~Berserker() = default;

  void cast(GameScene* scene) override;
  void end(GameScene* scene) override;
};

class DeathRay final : public Skill {
 public:
  explicit DeathRay(Commander* caster);
  virtual ~DeathRay() = default;

  void cast(GameScene* scene) override;
  void end(GameScene* scene) override;
};

class Reinforce final : public Skill {
  int range = 5;
 public:
  explicit Reinforce(Commander* caster);
  virtual ~Reinforce() = default;

  void cast(GameScene* scene) override;
  void end(GameScene* scene) override;
};