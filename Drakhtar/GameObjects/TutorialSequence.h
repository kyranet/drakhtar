// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#pragma once
#include <queue>
#include "GameObjects/Base/Sequence.h"

class TutorialBox;
class Scene;
class Font;

class TutorialSequence final : public Sequence {
  std::queue<TutorialBox*> tutorials_;
  int tutorialLenght = 0;
  void readFromFile(const std::string& filename, Font* textFont,
                    SDL_Rect tutorialArea, SDL_Rect dialogueBackground);
  static TutorialSequence* instance_;

 public:
  static int counter = 0;
  TutorialSequence(Scene* scene, const std::string& filename,
                   const std::string& fontFile);
  ~TutorialSequence();
  void render() const override;

  void next() override;
  void skip() override;
  void update() override;
  static int getCounter();
};
