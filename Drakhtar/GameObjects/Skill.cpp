// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#include "Skill.h"
#include "../Structures/Team.h"

Skill::Skill(std::string id, int cooldown, int duration, Unit* caster)
    : id_(id), cooldown_(cooldown), caster_(caster) {}

// ---------- BATTLECRY ----------
BattleCry::BattleCry(Unit* caster) : Skill("BattleCry", 3, 1, caster) {}

void BattleCry::cast(Board* board) {
  if (remainingCooldown_ == 0 && caster_->getMoving()) {
    std::cout << "Casted <BattleCry> by Thassa" << std::endl;
    active_ = true;
    for (auto unit : caster_->getTeam()->getUnitList()) {
      unit->setAttack(
          static_cast<int>(floor(unit->getStats().attack * 1.2)));
      // TODO(onaranjoUCM): Uncomment when we get acces to turnBar
      // unit->setSpeed(unit->getSpeed() + 1);
      // turnBar.sort()
    }
    remainingCooldown_ = cooldown_;
  }
}

void BattleCry::end() {
  std::cout << "<BattleCry> ended" << std::endl;
  active_ = false;
  for (auto unit : caster_->getTeam()->getUnitList()) {
    unit->setAttack(unit->getBaseStats().attack);
    // TODO(onaranjoUCM): Uncomment when we get acces to turnBar
    // unit->setSpeed(unit->getBaseSpeed());
  }
}

void BattleCry::resetAttack() {
  if (remainingCooldown_ == 0) {
    std::cout << "Casted <BattleCry>" << std::endl;
    for (auto unit : caster_->getTeam()->getUnitList()) {
      unit->setAttack(
          static_cast<int>(floor(unit->getStats().attack * 1.2)));
    }
    remainingCooldown_ = cooldown_;
  }
}

// ---------- ARROW RAIN ----------
ArrowRain::ArrowRain(Unit* caster) : Skill("ArrowRain", 2, 0, caster) {}

void ArrowRain::cast(Board* board) {
  if (remainingCooldown_ == 0 && caster_->getMoving()) {
    std::cout << "Casted <ArrowRain> by Zamdran" << std::endl;
    active_ = true;
    for (auto unit : caster_->getTeam()->getUnitList()) {
      unit->setAttack(
          static_cast<int>(floor(unit->getStats().attack * 1.2)));
    }
    remainingCooldown_ = cooldown_;
  }
}

void ArrowRain::end() {
  active_ = false;
  std::cout << "<ArrowRain> ended" << std::endl;
}
