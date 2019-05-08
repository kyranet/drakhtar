// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#include "Skill.h"

#include <algorithm>

#include "../Controllers/UnitsController.h"
#include "../Managers/TextureManager.h"
#include "../Managers/TurnManager.h"
#include "../Structures/Team.h"
#include "Commanders/Commander.h"
#include "GameObjects/Battalion.h"
#include "GameObjects/Board.h"
#include "GameObjects/Box.h"
#include "Managers/SDLAudioManager.h"

Skill::Skill(const std::string& id, int cooldown, int duration,
             Commander* caster)
    : id_(std::move(id)),
      caster_(caster),
      cooldown_(cooldown),
      duration_(duration) {}

void Skill::cast(GameScene*) {
  std::cout << "Casted <" + id_ + "> by " + caster_->getType() << std::endl;
  active_ = true;
  remainingCooldown_ = cooldown_;
  remainingDuration_ = duration_;

  // If the unit has moved and attacked, and has no other castable skills, end
  // turn
  if (caster_->getTeam()->getController()->hasMoved() &&
      caster_->getTeam()->getController()->hasAttacked()) {
    for (auto skill : caster_->getSkills()) {
      if (skill->getRemainingCooldown() == 0) return;
    }
    caster_->getTeam()->getController()->finish();
  }
}

void Skill::end(GameScene*) {}

// ---------- BATTLECRY ----------
BattleCry::BattleCry(Commander* caster) : Skill("BattleCry", 3, 1, caster) {
  description_ =
      "An inspiring command that increases every ally's attack by "
      "20% and move range by 1 for 1 turn. (CD: " +
      std::to_string(cooldown_) + " turns)";
}

void BattleCry::cast(GameScene* scene) {
  if (remainingCooldown_ == 0 && caster_->getMoving()) {
    Skill::cast(scene);
    // Boost attack and movement range of every unit in the same team
    for (auto unit : scene->getAlliedTeam(caster_)->getUnits()) {
      unit->Unit::setAttack(
          static_cast<int>(floor(unit->getStats().attack * 1.2)));
      unit->setMoveRange(unit->getStats().moveRange + 1);
      unit->setBuffed(true);
    }
    SDLAudioManager::getInstance()->playChannel(10, 0, 1);

    if (!caster_->getTeam()->getController()->hasMoved()) {
      scene->getBoard()->highlightCellsInRange(caster_->getBox(),
                                               caster_->getStats().moveRange);
    }
  }
}

void BattleCry::end(GameScene* scene) {
  std::cout << "<Battle Cry> ended" << std::endl;
  active_ = false;

  // Reset every unit's attack and move range to base
  for (auto unit : scene->getAlliedTeam(caster_)->getUnits()) {
    unit->setAttack(unit->getBaseStats().attack);
    unit->setMoveRange(unit->getStats().moveRange - 1);
    unit->setBuffed(false);
  }

  // Update turn priority
  caster_->getTeam()->getController()->getTurnManager()->sortUnits();
}

// ---------- ARROW RAIN ----------
ArrowRain::ArrowRain(Commander* caster) : Skill("ArrowRain", 4, 0, caster) {
  description_ =
      "Fire an volley of arrows that deal half damage to enemies in a " +
      std::to_string(range) +
      " cells range. (CD: " + std::to_string(cooldown_) + " turns)";
}

void ArrowRain::cast(GameScene* scene) {
  if (remainingCooldown_ == 0 && caster_->getMoving()) {
    Skill::cast(scene);
    SDLAudioManager::getInstance()->playChannel(11, 0, 1);

    // Caster deals half damage to every enemy unit in range
    for (auto unit : scene->getEnemyTeam(caster_)->getUnits()) {
      if (scene->getBoard()->isInRange(caster_->getBox(), unit->getBox(),
                                       range)) {
        unit->loseHealth(caster_->getStats().attack / 2, 1);
        if (unit->getHealth() <= 0) {
          unit->getBox()->destroyContent();
        }
      }
    }
    end(scene);
  }
}

void ArrowRain::end(GameScene*) { active_ = false; }

// ---------- HEROIC STRIKE ----------
HeroicStrike::HeroicStrike(Commander* caster)
    : Skill("Heroic Strike", 2, 0, caster) {
  description_ =
      "The next attack this turn will deal 50% increased damage and will not "
      "trigger a counter-attack. (CD: " +
      std::to_string(cooldown_) + " turns)";
}

void HeroicStrike::cast(GameScene* scene) {
  if (remainingCooldown_ == 0 && caster_->getMoving()) {
    Skill::cast(scene);
    attackIncrement_ = caster_->getStats().attack * 0.5;
    caster_->setAttack(caster_->getStats().attack + attackIncrement_);
    caster_->setUnstoppable(true);
    caster_->setBuffed(true);
    SDLAudioManager::getInstance()->playChannel(8, 0, 1);
  }
}

void HeroicStrike::end(GameScene*) {
  active_ = false;
  std::cout << "<HeroicStrike> ended" << std::endl;
  caster_->setAttack(caster_->getStats().attack - attackIncrement_);
  caster_->setUnstoppable(false);
  caster_->setBuffed(false);
}

// ---------- WITHERING CURSE ----------
WitheringCurse::WitheringCurse(Commander* caster)
    : Skill("Withering Curse", 3, 1, caster) {
  description_ =
      "Casts a curse over the enemy team, lowering their attack by 20% and "
      "their defense by 10. (CD: " +
      std::to_string(cooldown_) + " turns)";
}

void WitheringCurse::cast(GameScene* scene) {
  if (remainingCooldown_ == 0 && caster_->getMoving()) {
    Skill::cast(scene);

    for (auto unit : scene->getEnemyTeam(caster_)->getUnits()) {
      unit->Unit::setAttack(
          static_cast<int>(floor(unit->getStats().attack * 0.8)));
      unit->setDefense(std::max(unit->getStats().defense - 10, 0));
      unit->setDebuffed(true);
    }
  }
}

void WitheringCurse::end(GameScene* scene) {
  std::cout << "<" + id_ + "> ended" << std::endl;
  active_ = false;
  for (auto unit : scene->getEnemyTeam(caster_)->getUnits()) {
    unit->setAttack(unit->getBaseStats().attack);
    unit->setDefense(unit->getBaseStats().defense);
    unit->setDebuffed(false);
  }
}

// ---------- CHARGE ----------
Charge::Charge(Commander* caster) : Skill("Charge", 1, 0, caster) {
  description_ =
      "Charges with unstoppable force, preventing the enemy from "
      "counter-attacking. (CD: Passive skill)";
}

void Charge::cast(GameScene* scene) {
  if (remainingCooldown_ == 0 && caster_->getMoving()) {
    Skill::cast(scene);
    caster_->setUnstoppable(true);
  }
}

void Charge::end(GameScene* scene) {
  std::cout << "<" + id_ + "> ended" << std::endl;
  active_ = false;
}

// ---------- BERSERKER ----------
Berserker::Berserker(Commander* caster) : Skill("Berserker", 4, 2, caster) {
  description_ =
      "Goes into a blood frenzy, doubling its attack but halving its defense "
      "for 2 turns. (CD: " +
      std::to_string(cooldown_) + " turns)";
}

void Berserker::cast(GameScene* scene) {
  if (remainingCooldown_ == 0 && caster_->getMoving()) {
    Skill::cast(scene);
    caster_->setAttack(caster_->getStats().attack * 2);
    caster_->setDefense(caster_->getStats().defense / 2);
    caster_->setBuffed(true);
    caster_->setDebuffed(true);
  }
}

void Berserker::end(GameScene* scene) {
  std::cout << "<" + id_ + "> ended" << std::endl;
  caster_->setAttack(caster_->getBaseStats().attack);
  caster_->setDefense(caster_->getBaseStats().defense);
  caster_->setBuffed(false);
  caster_->setDebuffed(false);
  active_ = false;
}

// ---------- DEATHRAY ----------
DeathRay::DeathRay(Commander* caster) : Skill("Death Ray", 3, 0, caster) {
  description_ =
      "Throws a bolt of dark magic to the furthest enemy, dealing 20 damage "
      "plus double the distance between the caster and the target. (CD: " +
      std::to_string(cooldown_) + " turns)";
}

void DeathRay::cast(GameScene* scene) {
  if (remainingCooldown_ == 0 && caster_->getMoving()) {
    Skill::cast(scene);

    // Searches for the furthest unit
    Unit* furthestUnit;
    int maxDistance = 0;
    for (auto unit : scene->getEnemyTeam(caster_)->getUnits()) {
      const auto distanceX = abs((caster_->getBox()->getIndex().getX() -
                                  unit->getBox()->getIndex().getX()));
      const auto distanceY = abs((caster_->getBox()->getIndex().getY() -
                                  unit->getBox()->getIndex().getY()));
      const auto totalDistance = distanceX + distanceY;
      if (totalDistance > maxDistance) {
        maxDistance = totalDistance;
        furthestUnit = unit;
      }
    }

    furthestUnit->loseHealth(20 + maxDistance * 2, 20 + maxDistance * 2);
  }
}

void DeathRay::end(GameScene* scene) {
  std::cout << "<" + id_ + "> ended" << std::endl;
  active_ = false;
}

// ---------- REINFORCE ----------
Reinforce::Reinforce(Commander* caster) : Skill("Reinforce", 1, 0, caster) {
  description_ =
      "Reinforces all soldiers, archers and mages in a 5-box radius, "
      "increasing the size of the unit by 1. (CD: " +
      std::to_string(cooldown_) + " turn)";
}

void Reinforce::cast(GameScene* scene) {
  if (remainingCooldown_ == 0 && caster_->getMoving()) {
    Skill::cast(scene);

    for (auto unit : scene->getAlliedTeam(caster_)->getUnits()) {
      if (scene->getBoard()->isInRange(caster_->getBox(), unit->getBox(),
                                       range)) {
        if (unit->getType() == "Soldier" || unit->getType() == "Archer" ||
            unit->getType() == "Mage") {
          const auto battalion = reinterpret_cast<Battalion*>(unit);
          battalion->setBattalionSize(battalion->getBattalionSize() + 1);
        }
      }
    }
  }
}

void Reinforce::end(GameScene* scene) {
  std::cout << "<" + id_ + "> ended" << std::endl;
  active_ = false;
}
