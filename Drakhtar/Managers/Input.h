// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#pragma once
#include <array>
#include "SDL.h"
#include "Utils/Constants.h"
#include "Utils/Vector2D.h"

class Input final {
  static Input* instance_;
  Input();
  ~Input();

  const Uint8* keyboard_{};
  Uint32 mouse_{};

  Vector2D<int> mousePosition_;

  std::array<bool, static_cast<size_t>(KeyboardKey::kKeyLimit)> keyDown_{};
  std::array<bool, static_cast<size_t>(KeyboardKey::kKeyLimit)> keyUp_{};
  std::array<bool, static_cast<size_t>(MouseKey::kKeyLimit)> mouseDown_{};
  std::array<bool, static_cast<size_t>(MouseKey::kKeyLimit)> mouseUp_{};

 public:
  static Input* instance();

  void clear();
  void update(SDL_Event event);

  static Vector2D<int> getMousePosition();
  static bool isKeyPressed(KeyboardKey key);
  static bool isKeyDown(KeyboardKey key);
  static bool isKeyUp(KeyboardKey key);
  static bool isMouseButtonDown(MouseKey button);
  static bool isMouseButtonUp(MouseKey button);
  static bool isMouseInside(const SDL_Rect* rectangle);
  static bool getShift();
  static bool getCtrl();
  static bool getAlt();
  static void destroy();
};
