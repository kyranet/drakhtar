// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#include "FontManager.h"
#include "../Structures/Font.h"

FontManager* FontManager::instance_ = nullptr;

FontManager::FontManager() = default;

FontManager* FontManager::getInstance() {
  if (instance_ == nullptr) instance_ = new FontManager();
  return instance_;
}

void FontManager::destroy() {
  if (instance_ != nullptr) {
    delete instance_;
    instance_ = nullptr;
  }
}

Font* FontManager::get(std::string name) { return getInstance()->map_[name]; }

FontInfo* FontManager::add(const std::string name, const std::string path,
                           const int size, const int lineJumpLimit) {
  const auto info = new FontInfo(name, path, size, lineJumpLimit);
  stack_.push(info);
  return info;
}

void FontManager::init() {
  while (!stack_.empty()) {
    const auto info = stack_.top();
    auto font = (new Font(info->path, info->size));
    map_.insert(std::pair<std::string, Font*>(info->name, font));
    stack_.pop();
    delete info;
  }
}

FontManager::~FontManager() {
  while (!stack_.empty()) stack_.pop();
  for (auto pair : map_) delete pair.second;
  map_.clear();
}
