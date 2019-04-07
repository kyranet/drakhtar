// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#pragma once
#include <vector>
#include "../EventListeners/ListenerOnClick.h"
#include "GameObject.h"

class Dialog;
class Scene;
class Font;

class DialogScene final : public GameObject {
  std::vector<Dialog *> dialogues_;
  size_t dialogueIndex_ = 0;  // index of the current position in vector
  int lineJumpLimit_ = 0;     // text line length
  void readFromFile(const std::string &filename, Font *textFont, SDL_Rect rect);

 public:
  DialogScene(
      Scene *scene, const std::string &filename,
      const std::string &fontFile);  // we set the position of every component
                                     // of the dialog(text and background)
  ~DialogScene();
  void next();
  void render() const override;
};

class DialogSceneOnClick final : public ListenerOnClick {
 public:
  explicit DialogSceneOnClick::DialogSceneOnClick(GameObject *gameObject)
      : ListenerOnClick(gameObject) {}
  void onClickStop(SDL_Point point) override;
};
