// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#include "GameManager.h"
#include "GameObjects/Battalion.h"

GameManager* GameManager::instance_ = nullptr;

GameManager::GameManager() {
  army_ = new std::map<std::string, uint16_t>();
  typeOrder[SOLDIER] = "Soldier";
  (*army_)["Soldier"] = 8;
  typeOrder[ARCHER] = "Archer";
  (*army_)["Archer"] = 6;
  typeOrder[MAGE] = "Mage";
  (*army_)["Mage"] = 0;
  typeOrder[KNIGHT] = "Knight";
  (*army_)["Knight"] = 0;
  typeOrder[MONSTER] = "Monster";
  (*army_)["Monster"] = 0;

  buyingCap_ = new std::map<std::string, uint16_t>();
  (*buyingCap_)["Soldier"] = 20;
  (*buyingCap_)["Archer"] = 18;
  (*buyingCap_)["Mage"] = 12;
  (*buyingCap_)["Knight"] = 10;
  (*buyingCap_)["Monster"] = 3;
}

GameManager::~GameManager() {
  if (army_ != nullptr) {
    delete army_;
    army_ = nullptr;
  }
  if (buyingCap_ != nullptr) {
    delete buyingCap_;
    buyingCap_ = nullptr;
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

  (*army_)["Soldier"] = 8;
  (*army_)["Archer"] = 6;
  (*army_)["Mage"] = 0;
  (*army_)["Knight"] = 0;
  (*army_)["Monster"] = 0;

  money_ = BASE_MONEY;
}

void GameManager::updateUnits(std::vector<Unit*>& units) {
  for (const auto& pair : typeOrder) (*army_)[pair.second] = 0;

  for (auto unit : units) {
    if (army_->find(unit->getType()) != army_->end()) {
      (*army_)[unit->getType()] =
          reinterpret_cast<Battalion*>(unit)->getBattalionSize();
    }
  }
}

int GameManager::getMoney() const { return money_; }

const std::map<std::string, uint16_t>& GameManager::getArmy() const {
  return (*army_);
}

const std::map<std::string, uint16_t>& GameManager::getCap() const {
  return (*buyingCap_);
}

const std::map<UnitType, std::string>& GameManager::getTypeOrder() const {
  return typeOrder;
}

int GameManager::getLevel() const { return level_; }

void GameManager::increaseLevel() { level_++; }

void GameManager::loseMoney(const int money) { money_ -= money; }

void GameManager::addMoney(const int money) { money_ += money; }

void GameManager::addUnits(const std::string& type, const uint16_t size) const {
  (*army_)[type] = static_cast<uint16_t>((*army_)[type] + size);
}
