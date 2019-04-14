// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#pragma once
#include <utility>
#include <vector>
#include "ListenerOnClick.h"
#include "SDL.h"

class Unit;
class Text;

struct StoreUnit {
  std::string type;
  int amount = 0;
  GameObject *unit;
  Text *amountText;
  GameObject *moreButton;
  GameObject *lessButton;

  StoreUnit(std::string type, GameObject *unit, Text *amountText,
            GameObject *moreButton, GameObject *lessButton)
      : type(std::move(type)),
        unit(unit),
        amountText(amountText),
        moreButton(moreButton),
        lessButton(lessButton) {}
};

class UnitStoreController final : public ListenerOnClick {
  std::vector<StoreUnit *> unitStore_;
  StoreUnit *selectedUnit_ = nullptr;
  GameObject *acceptButton_ = nullptr;
  GameObject *cancelButton_ = nullptr;
  int totalCost_ = 0;

  void increaseAmount(StoreUnit *storeUnit);
  void reduceAmount(StoreUnit *storeUnit);
  void buyUnits();
  void reset();

 public:
  explicit UnitStoreController(GameObject *gameObject);
  ~UnitStoreController();

  void addUnitToStore(const std::string &type, GameObject *unit,
                      Text *amountText, GameObject *moreButton,
                      GameObject *lessButton);

  void onClickStop() override;
};
