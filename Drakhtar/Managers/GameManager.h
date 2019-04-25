// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#pragma once
#include <map>
#include <string>
#include <vector>

class Unit;

#define BASE_MONEY 1000

enum UnitType { SOLDIER, ARCHER, MAGE, KNIGHT, MONSTER };

class GameManager final {
  static GameManager* instance_;

  int money_ = BASE_MONEY;
  int level_ = 5;

  std::map<std::string, int>* army_ = nullptr;
  std::map<UnitType, std::string> typeOrder;
  GameManager();
  ~GameManager();

 public:
  static GameManager* getInstance();
  static void destroy();
  void reset();
  void updateUnits(std::vector<Unit*>& units);

  int getMoney() const;
  const std::map<std::string, int>& getArmy() const;
  const std::map<UnitType, std::string>& getTypeOrder() const;
  int getLevel() const;
  void increaseLevel();

  void loseMoney(int money);
  void addMoney(int money);

  void addUnits(const std::string& type, int size) const;
};
