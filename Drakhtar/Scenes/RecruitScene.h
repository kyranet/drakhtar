// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#pragma once

#include "Scene.h"
#include <string>
#include <map>

using namespace std;

class GameObject;
class UnitSelectorController;
class Text;

class RecruitScene : public Scene {
private:
  GameObject * unitBar_ = nullptr;
  UnitSelectorController * controller_ = nullptr;
  map<string, int> costs_;
  Text * moneyText_;

  void addUnit(string textureName, int position);
  string moneyToString();

public:
	//virtual ~RecruitScene();
	void preload() override;
	void buyUnits(string type, int quantity);
};