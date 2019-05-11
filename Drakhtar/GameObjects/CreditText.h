// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#pragma once
#include "Text.h"

class CreditText : public Text {
 private:
  double speed_;
  bool up_ = false;
 public:
  CreditText(Scene* scene, Font* font, Vector2D<int> position, SDL_Color color,
       const std::string& text, int lineJumpLimit, double speed);
  virtual ~CreditText();
  void update() override;
  void move();
  void nextLine();

  bool getUp();
  void setUp(bool up);
};
