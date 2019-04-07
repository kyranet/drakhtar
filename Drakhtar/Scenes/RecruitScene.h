// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#pragma once

#include <map>
#include <string>
#include "Scene.h"

using namespace std;

class GameObject;
class UnitStoreController;
class Text;

class RecruitScene : public Scene {
 private:
  GameObject* recruitmentPanel_ = nullptr;
  UnitStoreController* controller_ = nullptr;
  map<string, int> costs_;
  Text* moneyText_ = nullptr;
  Text* totalCostText_ = nullptr;

  void addUnit(string textureName, int position);
  string moneyToString();

 public:
  void preload() override;
  void buyUnits(string type, int quantity);
  int getCost(string type);
  void updateTotalCostText(int amount);
};
