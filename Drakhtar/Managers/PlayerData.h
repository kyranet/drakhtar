// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#pragma once
#include <map>
#include <string>

class PlayerData {
 private:
  static PlayerData* instance_;

  int money_ = 0;
  int level_ = 5;

  std::map<std::string, int>* army_ = nullptr;
  PlayerData();
  ~PlayerData();

 public:
  static PlayerData* getInstance();
  static void destroy();

  int getMoney() const { return money_; }
  std::map<std::string, int>* getArmy() const { return army_; }
  int getLevel() const { return level_; }
  void increaseLevel();

  void loseMoney(int money);
  void addMoney(int money);

  void addUnits(std::string type, int size);
};
