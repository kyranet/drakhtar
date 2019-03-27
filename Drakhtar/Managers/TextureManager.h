// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#pragma once
#include <stack>
#include "../Structures/Texture.h"
#include "ResourceManager.h"

struct AnimationTextureInfo {
  std::string name;
  std::vector<Uint16> frames;
};

class TextureInfo {
 public:
  TextureInfo(std::string name, std::string path, Uint16 columns, Uint16 rows,
              SDL_RendererFlip flip = SDL_FLIP_NONE)
      : name(name), path(path), columns(columns), rows(rows), flip(flip) {}
  ~TextureInfo() { animations.clear(); }
  std::string name;
  std::string path;
  Uint16 columns;
  Uint16 rows;
  SDL_RendererFlip flip;
  std::vector<AnimationTextureInfo> animations;
  TextureInfo *addAnimation(std::string name, std::vector<Uint16> frames) {
    animations.push_back({name, frames});
    return this;
  }
};

class TextureManager : public ResourceManager<Texture *> {
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
