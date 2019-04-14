// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#include "Input.h"
#include "SDL.h"

Input::Input(): mousePosition_(0, 0) {}
Input::~Input() = default;

Input* Input::instance_ = nullptr;

Input* Input::instance() {
    if (instance_ == nullptr) {
        instance_ = new Input();
    }
    return instance_;
}

void Input::clear() {
  for (auto i = 0, max = static_cast<int>(KeyboardKey::kKeyLimit); i < max;
       i++) {
    keyDown_[i] = false;
    keyUp_[i] = false;
  }

  for (auto i = 0, max = static_cast<int>(MouseKey::kKeyLimit); i < max; i++) {
    mouseDown_[i] = false;
    mouseUp_[i] = false;
  }
}

void Input::update(const SDL_Event event) {
  switch (event.type) {
    case SDL_KEYDOWN: {
      keyboard_ = SDL_GetKeyboardState(nullptr);
      keyDown_[event.key.keysym.scancode] = true;
      break;
    }
    case SDL_KEYUP: {
      keyboard_ = SDL_GetKeyboardState(nullptr);
      keyUp_[event.key.keysym.scancode] = true;
      break;
    }
    case SDL_MOUSEMOTION: {
      mousePosition_ = {event.motion.x, event.motion.y};
      break;
    }
    case SDL_MOUSEBUTTONDOWN: {
      mouse_ = SDL_GetMouseState(nullptr, nullptr);
      switch (event.button.button) {
        case SDL_BUTTON_LEFT:
          mouseDown_[static_cast<int>(MouseKey::LEFT)] = true;
          break;
        case SDL_BUTTON_MIDDLE:
          mouseDown_[static_cast<int>(MouseKey::MIDDLE)] = true;
          break;
        case SDL_BUTTON_RIGHT:
          mouseDown_[static_cast<int>(MouseKey::RIGHT)] = true;
          break;
        default:
          break;
      }
      break;
    }
    case SDL_MOUSEBUTTONUP: {
      mouse_ = SDL_GetMouseState(nullptr, nullptr);
      switch (event.button.button) {
        case SDL_BUTTON_LEFT:
          mouseUp_[static_cast<int>(MouseKey::LEFT)] = true;
          break;
        case SDL_BUTTON_MIDDLE:
          mouseUp_[static_cast<int>(MouseKey::MIDDLE)] = true;
          break;
        case SDL_BUTTON_RIGHT:
          mouseUp_[static_cast<int>(MouseKey::RIGHT)] = true;
          break;
        default:
          break;
      }
      break;
    }
    default:
      break;
  }
}

Vector2D<int> Input::getMousePosition() { return instance()->mousePosition_; }

bool Input::isKeyPressed(KeyboardKey key) {
  const auto input = instance();
  if (!input->keyboard_) return false;
  return input->keyboard_[static_cast<int>(key)];
}

bool Input::isKeyDown(KeyboardKey key) {
  return instance()->keyDown_[static_cast<int>(key)];
}
bool Input::isKeyUp(KeyboardKey key) {
  return instance()->keyUp_[static_cast<int>(key)];
}

bool Input::isMouseButtonDown(MouseKey button) {
  return instance()->mouseDown_[static_cast<int>(button)];
}
bool Input::isMouseButtonUp(MouseKey button) {
  return instance()->mouseUp_[static_cast<int>(button)];
}

bool Input::getShift() {
  const auto input = instance();
  return input->isKeyPressed(KeyboardKey::LEFT_SHIFT) ||
         input->isKeyPressed(KeyboardKey::RIGHT_SHIFT);
}

bool Input::getCtrl() {
  const auto input = instance();
  return input->isKeyPressed(KeyboardKey::LEFT_CTRL) ||
         input->isKeyPressed(KeyboardKey::RIGHT_CTRL);
}

bool Input::getAlt() {
  const auto input = instance();
  return input->isKeyPressed(KeyboardKey::LEFT_ALT) ||
         input->isKeyPressed(KeyboardKey::RIGHT_ALT);
}

bool Input::isMouseInside(const SDL_Rect* rectangle) {
  const auto input = instance();
  const auto position = input->mousePosition_;
  const auto point = SDL_Point{position.getX(), position.getY()};
  return SDL_PointInRect(&point, rectangle);
}

void Input::destroy() {
  if (instance_ != nullptr) {
    delete instance_;
    instance_ = nullptr;
  }
}
