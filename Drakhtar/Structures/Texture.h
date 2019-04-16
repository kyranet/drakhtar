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
  Texture();
  explicit Texture(SDL_Renderer *r);
  ~Texture();

  Uint16 getColumnAmount() const;
  Uint16 getRowAmount() const;
  Uint16 getFrame() const;
  Vector2D<Uint16> getSize() const;
  Vector2D<Uint16> getFrameSize() const;
  Vector2D<Uint16> getFramePosition(Uint16 frame) const;

  std::vector<Uint16> getAnimation() const;
  SDL_Texture *getTexture() const;
  SDL_Renderer *getRenderer() const;
  SDL_RendererFlip getFlip() const;

  Texture *setTexture(SDL_Texture *const &texture);
  Texture *setColumnAmount(Uint16 columns);
  Texture *setRowAmount(Uint16 rows);
  Texture *setFrameSize(Vector2D<Uint16> const &frameSize);
  Texture *setFlip(SDL_RendererFlip const &flip);
  Texture *loadFromImage(const std::string &filename, Uint16 rowAmount = 1,
                         Uint16 columnAmount = 1);
  Texture *loadFromText(Font *font, const std::string &text,
                        SDL_Color color = { 0, 0, 0, 255 },
                        int lineJumpLimit = 250);
  void addAnimation(const std::string &name, std::vector<Uint16> const &frames);
  void setAnimation(const std::string &name);
  bool hasAnimation(const std::string &name) const;
  void tick();
  void render(const Vector2D<int> &position) const;
  void render(SDL_Rect const &dest, double angle = 0,
              SDL_Rect *clip = nullptr) const;
  void renderFrame(SDL_Rect const &dest, Uint16 frame, double angle = 0) const;
  void close();
};
