// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#pragma once

#include "PlayerData.h"

PlayerData* PlayerData::instance_ = nullptr;

PlayerData::PlayerData() { army_ = new map<string, int>(); }

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

void PlayerData::increaseLevel() { level_++; }

void PlayerData::loseMoney(int money) { money_ -= money; }

void PlayerData::addMoney(int money) { money_ += money; }

void PlayerData::addUnits(string type, int size) { (*army_)[type] += size; }
