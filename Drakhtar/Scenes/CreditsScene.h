// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#pragma once
#include "Scene.h"
#include "../GameObjects/CreditText.h"
#include <fstream>

class CreditsScene : public Scene {
 private:
  CreditText* creditText1_ = nullptr;
  CreditText* creditText2_ = nullptr;
  int creditsLength_ = 0;
  int readCredits_ = 0;
  bool lastCredit_ = false;

  std::ifstream file_;

 public:
  CreditsScene();
  ~CreditsScene() override;
  void preload() override;

  std::string getNextLine();

  int getReadCredits();
  void setReadCredits(int readCredits);

  bool getLastCredit();
  void setLastCredit(bool lastCredit);
};
