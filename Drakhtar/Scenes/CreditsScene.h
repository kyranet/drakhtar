// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#pragma once
#include "Scene.h"
#include "../GameObjects/CreditText.h"
#include <iostream>
#include <string>
#include <fstream>

class CreditsScene : public Scene {
 private:
  CreditText* creditText_ = nullptr;
  int creditsLength_ = 0;
  int readCredits_ = 0;

 public:
  CreditsScene();
  ~CreditsScene() override;
  void preload() override;
  void readNextLine();

  std::string getNextLine(std::ifstream file);
};