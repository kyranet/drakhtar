// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#include "TextureManager.h"
#include "../Errors/DrakhtarError.h"

TextureManager *TextureManager::instance_ = nullptr;

TextureManager *TextureManager::getInstance() {
  if (instance_ == nullptr) {
    instance_ = new TextureManager();
  }

  return instance_;
}

TextureManager::TextureManager() {}

TextureInfo *TextureManager::add(const std::string name, const std::string path,
                                 const Uint16 columns, const Uint16 rows,
                                 const SDL_RendererFlip flip) {
  const auto info = new TextureInfo(name, path, columns, rows, flip);
  stack_.push(info);
  return info;
}

void TextureManager::init(SDL_Renderer *renderer) {
  while (!stack_.empty()) {
    auto info = stack_.top();
    auto texture = (new Texture(renderer))
                       ->loadFromImage(info->path, info->rows, info->columns);
    texture->setFlip(info->flip);

    // Add all the queued animations
    for (const auto &animation : info->animations)
      texture->addAnimation(animation.name, animation.frames);

    // If there was no default animation override, add it
    if (!texture->hasAnimation("default")) {
      const Uint16 frames =
          texture->getColumnAmount() * texture->getRowAmount();
      std::vector<Uint16> animation(frames);
      for (Uint16 i = 0; i < frames; i++) animation[i] = i;
      texture->addAnimation("default", animation);
    }

    texture->setAnimation("default");

    // Insert the texture to the map, pop the stack, and delete the temporary
    // information
    map_.insert(std::pair<std::string, Texture *>(info->name, texture));
    stack_.pop();
    delete info;
  }
}

void TextureManager::tick() {
  if (instance_ == nullptr) return;
  for (auto pair : map_) {
    pair.second->tick();
  }
}

Texture *TextureManager::get(const std::string name) {
  return getInstance()->map_[name];
}

TextureManager::~TextureManager() {
  while (!stack_.empty()) stack_.pop();
  for (const auto &pair : map_) delete pair.second;
  map_.clear();
}

void TextureManager::destroy() {
  if (instance_ != nullptr) {
    delete instance_;
    instance_ = nullptr;
  }
}
