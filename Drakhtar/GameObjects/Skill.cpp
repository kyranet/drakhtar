// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#include "Skill.h"

#include "../Controllers/UnitsController.h"
#include "../Managers/TextureManager.h"
#include "../Managers/TurnManager.h"
#include "../Structures/Team.h"
#include "Commanders/Commander.h"
#include "GameObjects/HealthBar.h"

Skill::Skill(std::string id, int cooldown, int duration, Commander* caster)
    : id_(std::move(id)),
      caster_(caster),
      cooldown_(cooldown),
      duration_(duration) {}

// ---------- BATTLECRY ----------
#pragma region BattleCry

BattleCry::BattleCry(Commander* caster) : Skill("BattleCry", 3, 1, caster) {
  description_ =
      "An inspiring command that increases every ally's attack and speed by "
      "20% for 1 turn";
}

void BattleCry::cast(GameScene* scene) {
  if (remainingCooldown_ == 0 && caster_->getMoving()) {
    std::cout << "Casted <BattleCry> by Thassa" << std::endl;
    active_ = true;
    // Boost attack and speed of every unit in the same team
    for (auto unit : caster_->getTeam()->getUnits()) {
      unit->Unit::setAttack(
          static_cast<int>(floor(unit->getStats().attack * 1.2)));
      unit->setSpeed(unit->getStats().speed + 10);
      unit->setBuffed(true);
    }

    // Update turn priority
    caster_->getTeam()->getController()->getTurnManager()->sortUnits();

    remainingCooldown_ = cooldown_;
    remainingDuration_ = duration_;
  }
}

void BattleCry::end() {
  std::cout << "<BattleCry> ended" << std::endl;
  active_ = false;

  // Reset every unit's attack and speed to base
  for (auto unit : caster_->getTeam()->getUnits()) {
    unit->setAttack(unit->getBaseStats().attack);
    unit->setSpeed(unit->getBaseStats().speed);
    unit->setBuffed(false);
  }

  // Update turn priority
  caster_->getTeam()->getController()->getTurnManager()->sortUnits();
}
#pragma endregion BattleCry

// ---------- ARROW RAIN ----------
#pragma region ArrowRain
ArrowRain::ArrowRain(Commander* caster) : Skill("ArrowRain", 2, 0, caster) {
  description_ =
      "Fire an volley of arrows that deal half damage to ALL enemies in the "
      "battlefield";
}

void ArrowRain::cast(GameScene* scene) {
  if (remainingCooldown_ == 0 && caster_->getMoving()) {
    std::cout << "Casted <ArrowRain> by Zamdran" << std::endl;
    active_ = true;

    // Caster deal half damage to every enemy unit
    for (auto unit : scene->getTeam1_()->getUnits()) {
      unit->loseHealth(caster_->getStats().attack / 2, 1);
    }
    remainingCooldown_ = cooldown_;
    remainingDuration_ = duration_;
    end();
  }
}

void ArrowRain::end() { active_ = false; }
#pragma endregion ArrowRain

// ---------- HEROIC STRIKE ----------
#pragma region HeroicStrike
HeroicStrike::HeroicStrike(Commander* caster)
    : Skill("Heroic Strike", 2, 0, caster) {
  description_ =
      "The next attack this turn will deal 50% increased damage and will not "
      "trigger a counter-attack";
}

void HeroicStrike::cast(GameScene* scene) {
  if (remainingCooldown_ == 0 && caster_->getMoving()) {
    active_ = true;
    std::cout << "Casted <HeroicStrike> by Thassa" << std::endl;
    attackIncrement_ = caster_->getStats().attack * 0.5;
    caster_->setAttack(caster_->getStats().attack + attackIncrement_);
    caster_->setUnstoppable(true);
    caster_->setBuffed(true);

    remainingCooldown_ = cooldown_;
    remainingDuration_ = duration_;
  }
}

void HeroicStrike::end() {
  active_ = false;
  std::cout << "<HeroicStrike> ended" << std::endl;
  caster_->setAttack(caster_->getStats().attack - attackIncrement_);
  caster_->setUnstoppable(false);
  caster_->setBuffed(false);
}
#pragma endregion HeroicStrike
