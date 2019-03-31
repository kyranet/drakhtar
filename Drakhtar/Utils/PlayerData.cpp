// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#pragma once

#include "PlayerData.h"

PlayerData::PlayerData()
{
  army_ = new map<string, int>();
}

void PlayerData::lossMoney(int money)
{
  money_ -= money;
}

void PlayerData::addMoney(int money)
{
  money_ += money;
}

void PlayerData::addUnits(string type, int size)
{
  (*army_)[type] += size;
}





