// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#pragma once
#include <queue>
#include "GameObject.h"

class TutorialBox;
class Scene;
class Font;

class TutorialSequence final : public GameObject {
  std::queue<TutorialBox *> tutorials_;
  void readFromFile(const std::string &filename, Font *textFont,
                    SDL_Rect tutorialArea, SDL_Rect dialogueBackground);
  static TutorialSequence *instance_;

 public:
  TutorialSequence(Scene *scene, const std::string &filename,
                   const std::string &fontFile);
  ~TutorialSequence();
  void createNextTutorial();
  void render() const override;
};
