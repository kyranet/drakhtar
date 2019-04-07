// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#pragma once

#include <map>
#include <string>
#include "Scene.h"

class GameObject;
class UnitStoreController;
class Text;

class RecruitScene : public Scene {
 private:
  GameObject* recruitmentPanel_ = nullptr;
  UnitStoreController* controller_ = nullptr;
  std::map<std::string, int> costs_;
  Text* moneyText_ = nullptr;
  Text* totalCostText_ = nullptr;

  void addUnit(std::string textureName, int position);
  std::string moneyToString();

 public:
  void preload() override;
  void buyUnits(std::string type, int quantity);
  int getCost(std::string type);
  void updateTotalCostText(int amount);
};
