// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#pragma once

#include <map>
#include <string>

#include "Scene.h"

class GameObject;
class StoreListener;
class Text;
class Button;

class RecruitScene final : public Scene {
  GameObject* recruitmentPanel_ = nullptr;
  std::vector<StoreListener*> store;
  std::map<std::string, int> costs_;
  Text* moneyText_ = nullptr;
  Text* totalCostText_ = nullptr;
  Button* playButton;

  int totalCost_ = 0;
  int currentScene_ = 1;

  void addUnit(const std::string& textureName, int position);
  std::string moneyToString() const;

  void reset();

 public:
  explicit RecruitScene(int currentScene);
  void preload() override;
  int getCost(const std::string& type);
  int getTotalCost() const { return totalCost_; }
  void updateTotalCost(int amount);
};
