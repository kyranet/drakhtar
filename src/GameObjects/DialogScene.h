// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#pragma once
#include <vector>

#include "GameObjects/Base/Sequence.h"

class Dialog;
class Scene;
class Font;

class DialogScene final : virtual public Sequence {
  std::vector<Dialog*> dialogues_;
  size_t dialogueIndex_ = 0;  // index of the current position in vector
  int lineJumpLimit_ = 0;     // text line length
  int numbBattles = 6;        // number of battles implemented in game + 1

  void readFromFile(const std::string& filename, Font* textFont, SDL_Rect rect);
  void readFromLocale(const std::string& dialogKey, Font* textFont,
                      const SDL_Rect rect, size_t nLines);

 public:
  DialogScene(
      Scene* scene, const std::string& filename,
      const std::string& fontFile);  // we set the position of every component
                                     // of the dialog(text and background)

  DialogScene(
      Scene* scene, const std::string& dialogKey, size_t nLines,
      const std::string& fontFile);  // we set the position of every component
                                     // of the dialog(text and background)
  ~DialogScene();
  void next() override;
  void skip() override;
  void render() const override;
};
