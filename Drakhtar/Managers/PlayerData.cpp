// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#include "PlayerData.h"

PlayerData* PlayerData::instance_ = nullptr;

PlayerData::PlayerData() { army_ = new std::map<std::string, int>(); }

PlayerData::~PlayerData() {
  if (army_ != nullptr) {
    delete army_;
    army_ = nullptr;
  }
}

PlayerData* PlayerData::getInstance() {
  if (instance_ == nullptr) instance_ = new PlayerData();
  return instance_;
}

void PlayerData::destroy() {
  if (instance_ != nullptr) {
    delete instance_;
    instance_ = nullptr;
  }
}

int PlayerData::getMoney() const { return money_; }

std::map<std::string, int>* PlayerData::getArmy() const { return army_; }

int PlayerData::getLevel() const { return level_; }

void PlayerData::increaseLevel() { level_++; }

void PlayerData::loseMoney(const int money) { money_ -= money; }

void PlayerData::addMoney(const int money) { money_ += money; }

void PlayerData::addUnits(const std::string& type, const int size) const {
  (*army_)[type] += size;
}
