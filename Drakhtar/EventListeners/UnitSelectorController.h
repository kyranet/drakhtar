// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#pragma once
#include "ListenerOnClick.h"
#include "SDL.h"
#include <vector>

using namespace std;

class UnitSelectorController : public ListenerOnClick {
private:
	vector<GameObject*> unitList = nullptr;
	vector<GameObject*> UnitStore = nullptr;
	GameObject currentVisibleUnit = nullptr;
public:
	UnitSelectorController();

};