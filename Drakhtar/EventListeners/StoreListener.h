// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#pragma once
#include <utility>
#include <vector>

#include "ListenerOnClick.h"
#include "ListenerOnHover.h"
#include "SDL.h"

class Unit;
class Text;
class RecruitmentStat;
struct StoreUnit {
  std::string type;
  GameObject* unit = nullptr;
  int cost_;
  byte amount_ = 0;
  Text* amountText = nullptr;

  StoreUnit(const std::string& type, GameObject* unit, int cost)
      : type(type), unit(unit), cost_(cost) {}
};

class StoreListener final : public ListenerOnHover {
  StoreUnit storeUnit;
  std::vector<Text*> sizeTexts_;
  StoreUnit* selectedUnit_ = nullptr;
  RecruitmentStat* stats_ = nullptr;
  int sizeToBuy;

 public:
  StoreListener(GameObject* gameObject, const std::string& type, int cost);
  ~StoreListener();

  void onHoverStart() override;
  void onHoverStop() override;

  void reset();
  std::string infoFillText() const;

  const StoreUnit& getStoreUnit() const { return storeUnit; }
};
