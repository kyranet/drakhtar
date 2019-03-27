// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#pragma once
#include <map>
#include <string>
#include <vector>
#include "../Utils/Vector2D.h"
#include "Font.h"
#include "SDL.h"

class Texture final {
  SDL_Texture *texture_ = nullptr;
  SDL_Renderer *renderer_ = nullptr;
  Vector2D<Uint16> size_;
  Vector2D<Uint16> frameSize_;
  Uint32 columnAmount_ = 1;
  Uint32 rowAmount_ = 1;
  std::map<std::string, std::vector<Uint16>> animations_;
  std::vector<Uint16> animation_;
  Uint16 frame_ = 0;
  SDL_RendererFlip flip_ = SDL_FLIP_NONE;

 public:
  Texture() = default;
  explicit Texture(SDL_Renderer *r) : renderer_(r) {}
  ~Texture();

  Uint16 getColumnAmount() const { return columnAmount_; }
  Uint16 getRowAmount() const { return rowAmount_; }
  Uint16 getFrame() const { return frame_; }
  Vector2D<Uint16> getSize() const { return size_; }
  Vector2D<Uint16> getFrameSize() const { return frameSize_; }
  Vector2D<Uint16> getFramePosition(Uint16 frame) const {
    return Vector2D<Uint16>(frame % columnAmount_,
                            static_cast<Uint16>(floor(frame / columnAmount_)));
  }

  std::vector<Uint16> getAnimation() const { return animation_; }
  SDL_Texture *getTexture() const { return texture_; }
  SDL_Renderer *getRenderer() const { return renderer_; }
  SDL_RendererFlip getFlip() const { return flip_; }

  Texture *setTexture(SDL_Texture *const &texture);
  Texture *setColumnAmount(Uint16 columns);
  Texture *setRowAmount(Uint16 rows);
  Texture *setFrameSize(Vector2D<Uint16> const &frameSize);
  Texture *setFlip(SDL_RendererFlip const &flip);
  Texture *loadFromImage(const std::string &filename, Uint16 rowAmount = 1,
                         Uint16 columnAmount = 1);
  Texture *loadFromText(Font *font, const std::string &text,
                        SDL_Color color = {0, 0, 0, 255},
                        int lineJumpLimit = 250);
  void addAnimation(const std::string &name, std::vector<Uint16> const &frames);
  void setAnimation(const std::string &name);
  bool hasAnimation(const std::string &name);
  void tick();
  void render(const Vector2D<int> &position) const;
  void render(SDL_Rect const &dest, double angle = 0,
              SDL_Rect *clip = nullptr) const;
  void renderFrame(SDL_Rect const &dest, Uint16 frame, double angle = 0) const;
  void close();
};
