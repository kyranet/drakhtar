// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#pragma once
#include "../EventListeners/ListenerOnClick.h"
#include "GameObject.h"
#include <queue>

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

class TutorialSceneOnClick final : public ListenerOnClick {
public:
  explicit TutorialSceneOnClick(GameObject *gameObject)
      : ListenerOnClick(gameObject) {}
  void onClickStop(SDL_Point point) override;
};
