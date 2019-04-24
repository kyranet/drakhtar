// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#include "GameManager.h"

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
  if (instance_ == nullptr){
    getInstance();
    return;
  }
  for (auto pair : instance_->getArmy()){
    pair.second = 0;
  }
  instance_->loseMoney(instance_->getMoney());
  instance_->addMoney(BASE_MONEY);
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
