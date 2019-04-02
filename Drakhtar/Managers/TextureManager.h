// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#pragma once
#include <stack>
#include <utility>
#include "../Structures/Texture.h"
#include "ResourceManager.h"

struct AnimationTextureInfo {
  std::string name;
  std::vector<Uint16> frames;
};

class TextureInfo final {
 public:
  TextureInfo(std::string name, std::string path, const Uint16 columns,
              const Uint16 rows, const SDL_RendererFlip flip = SDL_FLIP_NONE)
      : name_(std::move(name)),
        path_(std::move(path)),
        columns_(columns),
        rows_(rows),
        flip_(flip) {}
  ~TextureInfo() { animations_.clear(); }
  std::string name_;
  std::string path_;
  Uint16 columns_;
  Uint16 rows_;
  SDL_RendererFlip flip_;
  std::vector<AnimationTextureInfo> animations_;
  TextureInfo *addAnimation(const std::string &name,
                            const std::vector<Uint16> &frames) {
    animations_.push_back({name, frames});
    return this;
  }
};

class TextureManager final : public ResourceManager<Texture *> {
  static TextureManager *instance_;
  TextureManager();
  ~TextureManager();
  std::stack<TextureInfo *> stack_;

 public:
  TextureInfo *add(std::string name, std::string path, Uint16 columns,
                   Uint16 rows, SDL_RendererFlip flip = SDL_FLIP_NONE);
  void init(SDL_Renderer *renderer) override;
  void tick();
  static Texture *get(std::string name);
  static TextureManager *getInstance();
  static void destroy();
};
