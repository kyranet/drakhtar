// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#include "Texture.h"
#include "../Errors/SDLError.h"
#include "../Structures/Game.h"
#include "SDL_image.h"

Texture::~Texture() {
  close();
  animations_.clear();
}

Texture *Texture::setTexture(SDL_Texture *const &texture) {
  if (texture != texture_) {
    if (texture_ != nullptr) SDL_DestroyTexture(texture_);
    texture_ = texture;
  }

  return this;
}

Texture *Texture::setColumnAmount(const Uint16 columns) {
  columnAmount_ = columns;
  return this;
}

Texture *Texture::setRowAmount(const Uint16 rows) {
  rowAmount_ = rows;
  return this;
}

Texture *Texture::setFrameSize(Vector2D<Uint16> const &frameSize) {
  frameSize_ = frameSize;
  return this;
}

Texture *Texture::setFlip(SDL_RendererFlip const &flip) {
  flip_ = flip;
  return this;
}

Texture *Texture::loadFromImage(const std::string &filename,
                                const Uint16 rowAmount,
                                const Uint16 columnAmount) {
  const auto surface = IMG_Load(filename.c_str());
  if (surface == nullptr) {
    const auto message = "Error loading surface from " + filename +
                         "\nReason: " + SDL_GetError();
    throw SDLError(message);
  }

  close();
  texture_ = SDL_CreateTextureFromSurface(renderer_, surface);
  if (texture_ != nullptr) {
    size_.set(surface->w, surface->h);
    frameSize_.set(surface->w / columnAmount, surface->h / rowAmount);
    columnAmount_ = columnAmount;
    rowAmount_ = rowAmount;
  }
  SDL_FreeSurface(surface);
  return this;
}

Texture *Texture::loadFromText(Font *font, const std::string &text,
                               SDL_Color const color, const int lineJumpLimit) {
  const auto surface = font->renderText(text, color, lineJumpLimit);
  if (surface == nullptr) {
    const auto message =
        "Error loading text: " + text + "\nReason: " + TTF_GetError();
    throw SDLError(message);
  }

  close();
  texture_ = SDL_CreateTextureFromSurface(renderer_, surface);
  if (texture_ != nullptr) {
    size_.set(surface->w, surface->h);
    frameSize_.set(surface->w, surface->h);
    columnAmount_ = 1;
    rowAmount_ = 1;
  }
  SDL_FreeSurface(surface);
  return this;
}

void Texture::addAnimation(const std::string &name,
                           const std::vector<Uint16> &frames) {
  animations_[name] = frames;
}

void Texture::setAnimation(const std::string &name) {
  if (hasAnimation(name))
    animation_ = animations_[name];
  else
    throw DrakhtarError(
        "Cannot set an animation that has not been previously added.");
}

bool Texture::hasAnimation(const std::string &name) {
  return animations_.count(name) != 0;
}

void Texture::tick() {
  const auto size = animation_.size();
  if (size == 0) return;
  if (frame_ == size - 1)
    frame_ = 0;
  else
    frame_++;
}

void Texture::render(const Vector2D<int> &position) const {
  const SDL_Rect dest{position.getX(), position.getY(), size_.getX(),
                      size_.getY()};
  render(dest);
}

void Texture::render(const SDL_Rect &dest, double angle, SDL_Rect *clip) const {
  if (texture_ != nullptr) {
    if (clip == nullptr) {
      SDL_Rect defaultClip = {0, 0, size_.getX(), size_.getY()};
      clip = &defaultClip;
    }
    SDL_RenderCopy(renderer_, texture_, clip, &dest);
  }
}

void Texture::renderFrame(SDL_Rect const &dest, Uint16 frame,
                          double angle) const {
  auto framePosition = getFramePosition(frame);
  const auto width = frameSize_.getX();
  const auto height = frameSize_.getY();
  SDL_Rect src{width * framePosition.getX(), height * framePosition.getY(),
               width, height};
  SDL_RenderCopyEx(renderer_, texture_, &src, &dest, angle, nullptr, flip_);
}

void Texture::close() {
  if (texture_ != nullptr) {
    SDL_DestroyTexture(texture_);
    texture_ = nullptr;
    size_.set(0, 0);
  }
}
