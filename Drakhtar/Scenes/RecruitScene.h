// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#pragma once

#include "Scene.h"
#include <string>

using namespace std;

class GameObject;
class UnitSelectorController;

class RecruitScene : public Scene {
private:
	GameObject * unitBar = nullptr;
  UnitSelectorController * controller = nullptr;
  

  void addUnit(string textureName, int position);
public:
	//virtual ~RecruitScene();
	void preload() override;
};