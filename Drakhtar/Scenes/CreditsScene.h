// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#pragma once
#include "Scene.h"
#include "../GameObjects/CreditText.h"
#include <fstream>

class CreditsScene : public Scene {
 private:
  CreditText* creditText_ = nullptr;
  int creditsLength_ = 0;
  int readCredits_ = 0;

  std::ifstream file_;

 public:
  CreditsScene();
  ~CreditsScene() override;
  void preload() override;

  std::string getNextLine();

  int getReadCredits();
  void setReadCredits(int readCredits);
};
