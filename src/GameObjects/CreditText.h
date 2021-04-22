// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#pragma once
#include "Text.h"

class CreditText : public Text {
 private:
  double speed_;
  int creditsLength_ = 0;
  bool lastCredit_ = false;

 public:
  CreditText(Scene* scene, Font* font, Vector2D<int> position, SDL_Color color,
             const std::string& text, int lineJumpLimit, double speed,
             int creditsLength);
  virtual ~CreditText();
  void update() override;
  void move();
  void nextLine();
};
