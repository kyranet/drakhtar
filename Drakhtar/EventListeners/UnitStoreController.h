// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#pragma once
#include <vector>
#include "ListenerOnClick.h"
#include "SDL.h"

class Unit;
class Text;

struct StoreUnit {
  std::string type_;
  int amount_ = 0;
  GameObject *unit_;
  Text *amountText_;
  GameObject *moreButton_;
  GameObject *lessButton_;

  StoreUnit(std::string type, GameObject *unit, Text *amountText,
            GameObject *moreButton, GameObject *lessButton)
      : type_(type),
        unit_(unit),
        amountText_(amountText),
        moreButton_(moreButton),
        lessButton_(lessButton) {}
};

class UnitStoreController : public ListenerOnClick {
 private:
  std::vector<StoreUnit *> unitStore;
  StoreUnit *selectedUnit = nullptr;
  GameObject *acceptButton = nullptr;
  GameObject *cancelButton = nullptr;
  int totalCost = 0;

  void increaseAmount(StoreUnit *storeUnit);
  void reduceAmount(StoreUnit *storeUnit);
  void buyUnits();
  void reset();

 public:
  explicit UnitStoreController(GameObject *gameObject);
  virtual ~UnitStoreController();

  void addUnitToStore(std::string type, GameObject *unit, Text *amountText,
                      GameObject *moreButton, GameObject *lessButton);

  void onClickStop(const SDL_Point) override;
};
