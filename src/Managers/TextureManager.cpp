// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#include "TextureManager.h"

#include "../Errors/DrakhtarError.h"
#include "Structures/Game.h"
#include "Utils/TimePool.h"

TextureManager* TextureManager::instance_ = nullptr;

TextureManager* TextureManager::getInstance() {
  if (instance_ == nullptr) {
    instance_ = new TextureManager();
  }

  return instance_;
}

TextureManager::TextureManager() = default;

Texture* TextureManager::add(const std::string& name, const std::string& path,
                             const Uint16 columns, const Uint16 rows) {
  const auto texture = new Texture(Game::getRenderer());
  texture->loadFromImage(path, rows, columns);
  map_.insert(std::pair<std::string, Texture*>(name, texture));
  return texture;
}

void TextureManager::init() {
  for (const auto& pair : map_) {
    const auto texture = pair.second;

    // If there was no default animation override, add it
    if (!texture->hasAnimation("default")) {
      const Uint16 frames = static_cast<Uint16>(texture->getColumnAmount() *
                                                texture->getRowAmount());
      std::vector<Uint16> animation(frames);
      for (Uint16 i = 0; i < frames; i++) animation[i] = i;
      texture->addAnimation("default", animation);
    }

    texture->setAnimation("default");
  }
}

void TextureManager::tick() {
  if (instance_ == nullptr) return;
  for (auto& pair : map_) {
    pair.second->tick();
  }
}

Texture* TextureManager::get(const std::string& name) {
  return getInstance()->map_[name];
}

TextureManager::~TextureManager() {
  for (auto& pair : map_) delete pair.second;
  map_.clear();
}

void TextureManager::destroy() {
  if (instance_ != nullptr) {
    delete instance_;
    instance_ = nullptr;
  }
}
