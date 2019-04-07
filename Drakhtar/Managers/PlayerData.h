// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#pragma once
#include <map>
#include <string>

class PlayerData final {
  static PlayerData* instance_;

  int money_ = 0;
  int level_ = 5;

  std::map<std::string, int>* army_ = nullptr;
  PlayerData();
  ~PlayerData();

 public:
  static PlayerData* getInstance();
  static void destroy();

  int getMoney() const;
  std::map<std::string, int>* getArmy() const;
  int getLevel() const;
  void increaseLevel();

  void loseMoney(int money);
  void addMoney(int money);

  void addUnits(const std::string& type, int size) const;
};
