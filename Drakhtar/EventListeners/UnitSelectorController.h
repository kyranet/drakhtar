// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#pragma once
#include "ListenerOnClick.h"
#include "SDL.h"
#include <vector>

using namespace std;

class UnitSelectorController : public ListenerOnClick {
private:
	vector<GameObject*> bigUnits;
	vector<GameObject*> unitStore;
	GameObject *currentVisibleUnit = nullptr;
public:
  explicit UnitSelectorController(GameObject *gameObject)
    : ListenerOnClick(gameObject) {}

  void addUnitToStore(GameObject * unit);
  void addBigUnit(GameObject * unit);


  virtual void onClickStop(const SDL_Point) override;

};