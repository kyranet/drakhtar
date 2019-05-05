// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#pragma once
#include <queue>
#include "GameObjects/Base/Sequence.h"

class TutorialBox;
class Scene;
class Font;

class TutorialSequence final : public Sequence {
  std::queue<TutorialBox*> tutorials_;
  int counter = 0;
  int tutorialLength = 0;
  void readFromFile(const std::string& filename, Font* textFont);
  static TutorialSequence* instance_;

 public:
  TutorialSequence(Scene* scene, const std::string& filename,
                   const std::string& fontFile);
  ~TutorialSequence();
  void render() const override;

  void next() override;
  void skip() override;
  void update() override;
  int getCounter();
};
