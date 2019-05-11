// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#pragma once

#include <map>
#include <string>
#include <vector>
#include "../Utils/Vector2D.h"
#include "SDL.h"

class Font;
class TimePool;

class Texture final {
  struct AnimationTextureInfo {
    std::string name;
    std::vector<Uint16> frames;
    Uint16 frameRate;
  };

  SDL_Texture* texture_ = nullptr;
  SDL_Renderer* renderer_ = nullptr;

  TimePool* pool_ = nullptr;

  Vector2D<Uint16> size_;
  Vector2D<double> scale_{1, 1};
  Vector2D<Uint16> frameSize_;
  Uint32 columnAmount_ = 1;
  Uint32 rowAmount_ = 1;
  std::map<std::string, AnimationTextureInfo> animations_;
  std::string previousAnimation_;
  AnimationTextureInfo animation_;
  Uint16 frame_ = 0;
  SDL_RendererFlip flip_ = SDL_FLIP_NONE;
  Vector2D<int> offset_;

 public:
  Texture();
  explicit Texture(SDL_Renderer* r);
  ~Texture();

  Uint16 getColumnAmount() const;
  Texture* setColumnAmount(Uint16 columns);

  Uint16 getRowAmount() const;
  Texture* setRowAmount(Uint16 rows);

  Vector2D<double> getScale() const;
  Texture* setScale(Vector2D<double> scale);

  Uint16 getFrame() const;
  Uint16 getFrameRate() const;

  Vector2D<Uint16> getSize() const;
  Vector2D<Uint16> getCalculatedSize() const;

  Vector2D<Uint16> getFrameSize() const;
  Texture* setFrameSize(const Vector2D<Uint16>& frameSize);

  SDL_Texture* getTexture() const;
  Texture* setTexture(SDL_Texture* texture);

  Vector2D<Uint16> getFramePosition(Uint16 frame) const;

  std::vector<Uint16> getAnimation() const;

  Vector2D<int> getOffset() const;
  // offset is set to size*percentage
  void setOffset(Vector2D<double> percentage); 

  SDL_Renderer* getRenderer() const;
  SDL_RendererFlip getFlip() const;
  Texture* setFlip(SDL_RendererFlip const& flip);

  Texture* loadFromImage(const std::string& filename, Uint16 rowAmount = 1,
                         Uint16 columnAmount = 1);
  Texture* loadFromText(Font* font, const std::string& text,
                        SDL_Color color = {0, 0, 0, 255},
                        int lineJumpLimit = 250);
  Texture* addAnimation(const std::string& name,
                        const std::vector<Uint16>& frames,
                        Uint16 frameRate = 0);
  void setAnimation(const std::string& name);
  void setAnimationOnce(const std::string& name);
  bool hasAnimation(const std::string& name) const;

  void tick();
  void render(const Vector2D<int>& position) const;
  void render(const SDL_Rect& dest, double angle = 0,
              SDL_Rect* clip = nullptr) const;
  void renderFrame(const SDL_Rect& dest, Uint16 frame, double angle = 0) const;
  void close();
};
