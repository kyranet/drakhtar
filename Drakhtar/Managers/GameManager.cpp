// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#include "GameManager.h"

#include "GameObjects/Battalion.h"

GameManager* GameManager::instance_ = nullptr;

GameManager::GameManager() {
  army_ = new std::map<std::string, int>();
  typeOrder[SOLDIER] = "Soldier";
  (*army_)["Soldier"] = 0;
  typeOrder[ARCHER] = "Archer";
  (*army_)["Archer"] = 0;
  typeOrder[MAGE] = "Mage";
  (*army_)["Mage"] = 0;
  typeOrder[KNIGHT] = "Knight";
  (*army_)["Knight"] = 0;
  typeOrder[MONSTER] = "Monster";
  (*army_)["Monster"] = 0;

  buyingCap_ = new std::map<std::string, int>();
  (*buyingCap_)["Soldier"] = 10;
  (*buyingCap_)["Archer"] = 8;
  (*buyingCap_)["Mage"] = 7;
  (*buyingCap_)["Knight"] = 5;
  (*buyingCap_)["Monster"] = 4;
}

GameManager::~GameManager() {
  if (army_ != nullptr) {
    delete army_;
    army_ = nullptr;
  }
}

GameManager* GameManager::getInstance() {
  if (instance_ == nullptr) instance_ = new GameManager();
  return instance_;
}

void GameManager::destroy() {
  if (instance_ != nullptr) {
    delete instance_;
    instance_ = nullptr;
  }
}

void GameManager::reset() {
  for (auto pair : (*army_)) {
    (*army_)[pair.first] = 0;
  }
  money_ = BASE_MONEY;
}

void GameManager::updateUnits(std::vector<Unit*>& units) {
  for (auto unit : units) {
    if (army_->find(unit->getType()) != army_->end()) {
      (*army_)[unit->getType()] =
          reinterpret_cast<Battalion*>(unit)->getBattalionSize();
    }
  }
}

int GameManager::getMoney() const { return money_; }

const std::map<std::string, int>& GameManager::getArmy() const {
  return (*army_);
}

const std::map<std::string, int>& GameManager::getCap() const {
  return (*buyingCap_);
}

const std::map<UnitType, std::string>& GameManager::getTypeOrder() const {
  return typeOrder;
}

int GameManager::getLevel() const { return level_; }

void GameManager::increaseLevel() { level_++; }

void GameManager::loseMoney(const int money) { money_ -= money; }

void GameManager::addMoney(const int money) { money_ += money; }

void GameManager::addUnits(const std::string& type, const int size) const {
  (*army_)[type] += size;
}
