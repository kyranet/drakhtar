// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#include "Skill.h"

#include <algorithm>

#include "Commanders/Commander.h"
#include "Controllers/UnitsController.h"
#include "GameObjects/Battalion.h"
#include "GameObjects/Board.h"
#include "GameObjects/Box.h"
#include "Managers/SDLAudioManager.h"
#include "Managers/State.h"
#include "Managers/TextureManager.h"
#include "Scenes/GameScene.h"
#include "Structures/Game.h"
#include "Structures/Team.h"

Skill::Skill(const std::string& id, int16_t cooldown, int16_t duration,
             Commander* caster)
    : id_(id), caster_(caster), cooldown_(cooldown), duration_(duration) {
  scene_ = reinterpret_cast<GameScene*>(caster->getScene());
}

void Skill::cast() {
  std::cout << "Casted <" + id_ + "> by " + caster_->getType() << std::endl;
  scene_->getState()->castSkill(caster_, id_, cooldown_);
}

int16_t Skill::getRemainingCooldown() const {
  return scene_->getState()->getRemainingSkillCooldown(id_);
}

std::vector<Vector2D<uint16_t>> Skill::getAllAlliesPositions() const {
  const auto state = *scene_->getState();
  std::vector<Vector2D<uint16_t>> output;
  for (const auto& stats : state.getBoard()) {
    if (stats.unit_ != nullptr && stats.team_ == caster_->getTeam()->getColor())
      output.push_back(stats.position_);
  }
  return output;
}

std::vector<Vector2D<uint16_t>> Skill::getAllEnemiesPositions() const {
  const auto state = *scene_->getState();
  std::vector<Vector2D<uint16_t>> output;
  for (const auto& stats : state.getBoard()) {
    if (stats.unit_ != nullptr && stats.team_ != caster_->getTeam()->getColor())
      output.push_back(stats.position_);
  }
  return output;
}

// ---------- BATTLECRY ----------

BattleCry::BattleCry(Commander* caster)
    : Skill(Game::getInstance()->getLocale()->format("BATTLECRY"), 3, 1,
            caster) {
  description_ =
      Game::getInstance()->getLocale()->format("BATTLECRY_DESC", cooldown_);
}

void BattleCry::cast() {
  Skill::cast();

  auto state = scene_->getState();
  for (const auto& position : getAllAlliesPositions()) {
    state->addModifierAt(
        position,
        {caster_,
         [](const UnitState& state) {
           return UnitState{
               state.unit_,
               state.team_,
               state.position_,
               static_cast<uint16_t>(state.attack_ + state.attack_ * 0.20),
               state.health_,
               state.minimumAttack_,
               state.defense_,
               state.maxHealth_,
               state.attackRange_,
               static_cast<uint16_t>(state.moveRange_ + 1U),
               state.speed_,
               state.prize_,
               state.battalionSize_,
               false,
               state.counterAttackable_,
               state.modifiers_};
         },
         duration_, false, true});
  }
  SDLAudioManager::getInstance()->playChannel(10, 0, 1);
}

// ---------- ARROW RAIN ----------
ArrowRain::ArrowRain(Commander* caster)
    : Skill(Game::getInstance()->getLocale()->format("ARROWRAIN"), 4, 0,
            caster) {
  description_ =
      Game::getInstance()->getLocale()->format("ARROWRAIN_DESC", cooldown_);
}

void ArrowRain::cast() {
  Skill::cast();

  auto state = scene_->getState();
  const auto from = caster_->getBox()->getIndex();
  const auto stats = state->getModifiedAt(from);
  const auto damage = static_cast<uint16_t>(stats.attack_ * 0.5);
  for (const auto& position : getAllEnemiesPositions()) {
    if (!state->isInRange(from, position, range_)) continue;
    state->attack(position, damage);
  }
  SDLAudioManager::getInstance()->playChannel(11, 0, 1);
}

// ---------- HEROIC STRIKE ----------
HeroicStrike::HeroicStrike(Commander* caster)
    : Skill(Game::getInstance()->getLocale()->format("HEROICSTRIKE"), 2, 0,
            caster),
      attackIncrement_(0) {
  description_ =
      Game::getInstance()->getLocale()->format("HEROICSTRIKE_DESC", cooldown_);
}

void HeroicStrike::cast() {
  Skill::cast();

  auto state = scene_->getState();
  for (const auto& position : getAllAlliesPositions()) {
    state->addModifierAt(
        position,
        {caster_,
         [](const UnitState& state) {
           return UnitState{
               state.unit_,
               state.team_,
               state.position_,
               static_cast<uint16_t>(state.attack_ + (state.attack_ * 0.5)),
               state.health_,
               state.minimumAttack_,
               state.defense_,
               state.maxHealth_,
               state.attackRange_,
               state.moveRange_,
               state.speed_,
               state.prize_,
               state.battalionSize_,
               state.counterAttacked_,
               false,
               state.modifiers_};
         },
         duration_, false, true});
  }
  SDLAudioManager::getInstance()->playChannel(9, 0, 1);
}

// ---------- WITHERING CURSE ----------
WitheringCurse::WitheringCurse(Commander* caster)
    : Skill("Withering Curse", 3, 1, caster) {
  description_ =
      "Casts a curse over the enemy team, lowering their attack by 20% and "
      "their defense by 10. (CD: " +
      std::to_string(cooldown_) + " turns)";
}

void WitheringCurse::cast() {
  Skill::cast();

  const auto state = scene_->getState();
  for (const auto& position : getAllEnemiesPositions()) {
    state->addModifierAt(
        position,
        {caster_,
         [](const UnitState& state) {
           return UnitState{
               state.unit_,
               state.team_,
               state.position_,
               static_cast<uint16_t>(state.attack_ - (state.attack_ * 0.2)),
               state.health_,
               state.minimumAttack_,
               static_cast<uint16_t>(
                   state.defense_ <= 10 ? 0 : state.defense_ - 10),
               state.maxHealth_,
               state.attackRange_,
               state.moveRange_,
               state.speed_,
               state.prize_,
               state.battalionSize_,
               state.counterAttacked_,
               state.counterAttackable_,
               state.modifiers_};
         },
         duration_, true, false});
  }
}

// ---------- CHARGE ----------
Charge::Charge(Commander* caster) : Skill("Charge", -1, -1, caster) {
  description_ =
      "Charges with unstoppable force, preventing the enemy from "
      "counter-attacking. (CD: Passive skill)";
}

void Charge::cast() {
  Skill::cast();
  const auto state = scene_->getState();
  state->addModifierAt(caster_->getBox()->getIndex(),
                       {caster_,
                        [](const UnitState& state) {
                          return UnitState{state.unit_,
                                           state.team_,
                                           state.position_,
                                           state.attack_,
                                           state.health_,
                                           state.minimumAttack_,
                                           state.defense_,
                                           state.maxHealth_,
                                           state.attackRange_,
                                           state.moveRange_,
                                           state.speed_,
                                           state.prize_,
                                           state.battalionSize_,
                                           state.counterAttacked_,
                                           false,
                                           state.modifiers_};
                        },
                        duration_, false, false});
}

// ---------- BERSERKER ----------
Berserker::Berserker(Commander* caster) : Skill("Berserker", 4, 2, caster) {
  description_ =
      "Goes into a blood frenzy, doubling its attack but halving its defense "
      "for 2 turns. (CD: " +
      std::to_string(cooldown_) + " turns)";
}

void Berserker::cast() {
  Skill::cast();
  const auto state = scene_->getState();
  state->addModifierAt(caster_->getBox()->getIndex(),
                       {caster_,
                        [](const UnitState& state) {
                          return UnitState{
                              state.unit_,
                              state.team_,
                              state.position_,
                              static_cast<uint16_t>(state.attack_ * 2),
                              state.health_,
                              state.minimumAttack_,
                              static_cast<uint16_t>(state.defense_ / 2),
                              state.maxHealth_,
                              state.attackRange_,
                              state.moveRange_,
                              state.speed_,
                              state.prize_,
                              state.battalionSize_,
                              state.counterAttacked_,
                              state.counterAttackable_,
                              state.modifiers_};
                        },
                        duration_, true, true});
}

// ---------- DEATHRAY ----------
DeathRay::DeathRay(Commander* caster) : Skill("Death Ray", 3, 0, caster) {
  description_ =
      "Throws a bolt of dark magic to the furthest enemy, dealing 20 damage "
      "plus double the distance between the caster and the target. (CD: " +
      std::to_string(cooldown_) + " turns)";
}

void DeathRay::cast() {
  Skill::cast();
  Unit* furthestUnit = nullptr;
  int distance = 0;

  const auto state = scene_->getState();
  const auto from = caster_->getBox()->getIndex();
  for (const auto& position : getAllEnemiesPositions()) {
    int aux = state->getDistance(from, position);
    if (aux > distance) {
      distance = aux;
      furthestUnit = state->getUnitAt(position);
    }
  }

  if (furthestUnit) {
    state->attack(furthestUnit->getBox()->getIndex(),
                  static_cast<uint16_t>(20 + distance * 2));
  }
}

// ---------- REINFORCE ----------
Reinforce::Reinforce(Commander* caster) : Skill("Reinforce", 1, 0, caster) {
  description_ =
      "Reinforces all soldiers, archers and mages in a 5-box radius, "
      "increasing the size of the unit by 1. (CD: " +
      std::to_string(cooldown_) + " turn)";
}

void Reinforce::cast() {
  Skill::cast();

  auto state = scene_->getState();
  const auto from = caster_->getBox()->getIndex();
  for (const auto& position : getAllAlliesPositions()) {
    if (!state->isInRange(from, position, range_)) continue;
    const auto& type = state->getUnitAt(position)->getType();
    if (type == "Soldier" || type == "Archer" || type == "Mage") {
      auto stats = state->getAt(position);
      auto base = stats.unit_->getBaseStats();
      ++stats.battalionSize_;
      ++stats.minimumAttack_;
      stats.attack_ = static_cast<uint16_t>(stats.attack_ + base.attack);
      stats.maxHealth_ =
          static_cast<uint16_t>(stats.maxHealth_ + base.maxHealth);
      reinterpret_cast<Battalion*>(stats.unit_)
          ->setBattalionSize(stats.battalionSize_);
      state->setAt(position, stats);
    }
  }
}
