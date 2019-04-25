// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#include "GameManager.h"

GameManager* GameManager::instance_ = nullptr;

GameManager::GameManager() {
  army_ = new std::map<std::string, int>();
  typeOrder[SOLDIER] = "Soldier";
  (*army_)["Soldier"] = 9;
  typeOrder[ARCHER] = "Archer";
  (*army_)["Archer"] = 9;
  typeOrder[MAGE] = "Mage";
  (*army_)["Mage"] = 6;
  typeOrder[KNIGHT] = "Knight";
  (*army_)["Knight"] = 4;
  typeOrder[MONSTER] = "Monster";
  (*army_)["Monster"] = 2;
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

int GameManager::getMoney() const { return money_; }

const std::map<std::string, int>& GameManager::getArmy() const {
  return (*army_);
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
