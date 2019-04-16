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
      const Uint16 frames =
          texture->getColumnAmount() * texture->getRowAmount();
      std::vector<Uint16> animation(frames);
      for (Uint16 i = 0; i < frames; i++) animation[i] = i;
      texture->addAnimation("default", animation, animation.size());
    }

    texture->setAnimation("default");
    ensurePool(texture->getFrameRate());
    pools_[texture->getFrameRate()].textures.push_back(texture);
  }
}

void TextureManager::tick() {
  if (instance_ == nullptr) return;
  for (auto& pair : pools_) {
    if (pair.second.timePool->next(SDL_GetTicks())) {
      for (auto texture : pair.second.textures) {
        texture->tick();
      }
    }
  }
}

Texture* TextureManager::get(const std::string& name) {
  return getInstance()->map_[name];
}

TextureManager::~TextureManager() {
  for (auto& pair : map_) delete pair.second;
  map_.clear();

  for (auto& pair : pools_) {
    delete pair.second.timePool;
    pair.second.textures.clear();
  }
  pools_.clear();
}

void TextureManager::destroy() {
  if (instance_ != nullptr) {
    delete instance_;
    instance_ = nullptr;
  }
}

void TextureManager::switchPool(Uint16 previous, Uint16 now, Texture* texture) {
  if (previous == now) return;
  if (hasPool(previous)) {
    pools_[previous].textures.remove(texture);
    if (pools_[previous].textures.empty()) removePool(previous);
  }
  ensurePool(now);
  pools_[now].textures.push_back(texture);
}

bool TextureManager::hasPool(Uint16 frameRate) {
  return pools_.count(frameRate) != 0;
}

void TextureManager::removePool(Uint16 frameRate) {
  for (auto it = pools_.begin(); it != pools_.end(); it++) {
    if ((*it).first != frameRate) continue;
    pools_.erase(it);
  }
}

void TextureManager::ensurePool(Uint16 frameRate) {
  if (hasPool(frameRate)) return;
  Pool pool{new TimePool(1000 / frameRate, SDL_GetTicks()), {}};
  pools_.insert(std::pair<Uint16, Pool>(frameRate, pool));
}
