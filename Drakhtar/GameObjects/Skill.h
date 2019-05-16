// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#pragma once
#include <string>
#include <vector>
#include "Utils/Vector2D.h"

class Commander;
class Texture;
class GameScene;

class Skill {
 protected:
  std::string id_;
  std::string description_ = " ";
  Commander* caster_;
  GameScene* scene_;
  int16_t cooldown_;
  int16_t duration_;

 public:
  Skill(const std::string& id, int16_t cooldown, int16_t duration,
        Commander* caster);
  virtual ~Skill() = default;

  virtual void cast();

  std::string getId() const { return id_; }
  std::string getDescription() const { return description_; }
  int16_t getRemainingCooldown() const;

  std::vector<Vector2D<uint16_t>> getAllUnitPositions() const;
  std::vector<Vector2D<uint16_t>> getAllAlliesPositions() const;
  std::vector<Vector2D<uint16_t>> getAllEnemiesPositions() const;
};

class BattleCry final : public Skill {
 public:
  explicit BattleCry(Commander* caster);
  ~BattleCry() = default;

  void cast() override;
};

class ArrowRain final : public Skill {
  int range = 5;

 public:
  explicit ArrowRain(Commander* caster);
  ~ArrowRain() = default;

  void cast() override;
};

class HeroicStrike final : public Skill {
  double attackIncrement_;

 public:
  explicit HeroicStrike(Commander* caster);
  ~HeroicStrike() = default;

  void cast() override;
};

class WitheringCurse final : public Skill {
 public:
  explicit WitheringCurse(Commander* caster);
  ~WitheringCurse() = default;

  void cast() override;
};

class Charge final : public Skill {
 public:
  explicit Charge(Commander* caster);
  ~Charge() = default;

  void cast() override;
};

class Berserker final : public Skill {
 public:
  explicit Berserker(Commander* caster);
  ~Berserker() = default;

  void cast() override;
};

class DeathRay final : public Skill {
 public:
  explicit DeathRay(Commander* caster);
  ~DeathRay() = default;

  void cast() override;
};

class Reinforce final : public Skill {
  int range = 5;

 public:
  explicit Reinforce(Commander* caster);
  ~Reinforce() = default;

  void cast() override;
};
