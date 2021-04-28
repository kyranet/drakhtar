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

  std::vector<Vector2D<uint16_t>> getAllAlliesPositions() const;
  std::vector<Vector2D<uint16_t>> getAllEnemiesPositions() const;
};

class BattleCry final : public Skill {
 public:
  explicit BattleCry(Commander* caster);
  void cast() override;
};

class ArrowRain final : public Skill {
  int range_ = 5;

 public:
  explicit ArrowRain(Commander* caster);
  void cast() override;
};

class HeroicStrike final : public Skill {
  double attackIncrement_;

 public:
  explicit HeroicStrike(Commander* caster);
  void cast() override;
};

class WitheringCurse final : public Skill {
 public:
  explicit WitheringCurse(Commander* caster);
  void cast() override;
};

class Charge final : public Skill {
 public:
  explicit Charge(Commander* caster);
  void cast() override;
};

class Berserker final : public Skill {
 public:
  explicit Berserker(Commander* caster);
  void cast() override;
};

class DeathRay final : public Skill {
 public:
  explicit DeathRay(Commander* caster);
  void cast() override;
};

class Reinforce final : public Skill {
  int range_ = 5;

 public:
  explicit Reinforce(Commander* caster);
  void cast() override;
};
