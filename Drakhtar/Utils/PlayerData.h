// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#pragma once
#include <map>
#include <string>
using namespace std;

class PlayerData {
 private:
  int money_ = 0;
  string name;
  map<string, int>* army_ = nullptr;
  PlayerData();
  static PlayerData * instance_;
  ~PlayerData();

 public:
  static PlayerData* getInstance();
  static void destroy();

  int getMoney() const { return money_; }
  map<string, int>* getArmy() const { return army_; }

  void lossMoney(int money);
  void addMoney(int money);

  void addUnits(string type, int size);
};
