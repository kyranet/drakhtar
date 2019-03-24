// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#include "FontManager.h"
#include "../Structures/Font.h"

FontManager* FontManager::instance = nullptr;

FontManager::FontManager() {}

FontManager* FontManager::getInstance() {
  if (instance == nullptr) instance = new FontManager();

  return instance;
}

void FontManager::destroy() {
  if (instance != nullptr) {
    delete instance;
    instance = nullptr;
  }
}

Font* FontManager::get(std::string name) { return getInstance()->map_[name]; }

FontInfo* FontManager::add(std::string name, std::string path, int size,
                           int lineJumpLimit) {
  auto info = new FontInfo(name, path, size, lineJumpLimit);
  stack_.push(info);
  return info;
}

void FontManager::init() {
  while (!stack_.empty()) {
    auto info = stack_.top();
    auto font = (new Font(info->path_, info->size_));
    map_.insert(std::pair<std::string, Font*>(info->name_, font));
    stack_.pop();
    delete info;
  }
}

FontManager::~FontManager() {
  while (!stack_.empty()) stack_.pop();
  for (auto pair : map_) delete pair.second;
  map_.clear();
}
