// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#include "Texture.h"
#include "Errors/SDLError.h"
#include "Font.h"
#include "Managers/TextureManager.h"
#include "SDL_image.h"
#include "Utils/TimePool.h"

Texture::Texture() : size_(0, 0), frameSize_(0, 0) {}

Texture::Texture(SDL_Renderer* r)
    : renderer_(r), size_(0, 0), frameSize_(0, 0) {}

Uint16 Texture::getColumnAmount() const { return columnAmount_; }

Uint16 Texture::getRowAmount() const { return rowAmount_; }

Uint16 Texture::getFrame() const { return frame_; }

Uint16 Texture::getFrameRate() const { return animation_.frameRate; }

Vector2D<Uint16> Texture::getSize() const { return size_; }

Vector2D<Uint16> Texture::getFrameSize() const { return frameSize_; }

std::vector<Uint16> Texture::getAnimation() const { return animation_.frames; }

SDL_Texture* Texture::getTexture() const { return texture_; }

SDL_Renderer* Texture::getRenderer() const { return renderer_; }

SDL_RendererFlip Texture::getFlip() const { return flip_; }

Texture::~Texture() {
  close();
  animations_.clear();
}

Vector2D<Uint16> Texture::getFramePosition(const Uint16 frame) const {
  return Vector2D<Uint16>(frame % columnAmount_,
                          Uint16(floor(static_cast<double>(frame) /
                                       static_cast<double>(columnAmount_))));
}

Texture* Texture::setTexture(SDL_Texture* const& texture) {
  if (texture != texture_) {
    if (texture_ != nullptr) SDL_DestroyTexture(texture_);
    texture_ = texture;
  }

  return this;
}

Texture* Texture::setColumnAmount(const Uint16 columns) {
  columnAmount_ = columns;
  return this;
}

Texture* Texture::setRowAmount(const Uint16 rows) {
  rowAmount_ = rows;
  return this;
}

Texture* Texture::setFrameSize(Vector2D<Uint16> const& frameSize) {
  frameSize_ = frameSize;
  return this;
}

Texture* Texture::setFlip(SDL_RendererFlip const& flip) {
  flip_ = flip;
  return this;
}

Texture* Texture::loadFromImage(const std::string& filename,
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

Texture* Texture::loadFromText(Font* font, const std::string& text,
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

Texture* Texture::addAnimation(const std::string& name,
                               const std::vector<Uint16>& frames,
                               const Uint16 frameRate) {
  animations_.insert(std::pair<std::string, AnimationTextureInfo>(
      name, {name, frames,
             frameRate == 0 ? Uint16(frames.size() > 1 ? frames.size() : 0)
                            : frameRate}));
  return this;
}

void Texture::setAnimation(const std::string& name) {
  if (hasAnimation(name)) {
    const auto previous = animation_;
    const auto next = animations_[name];
    animation_ = next;
    frame_ = 0;
    delete pool_;
    pool_ = animation_.frameRate
                ? new TimePool(1000 / animation_.frameRate, SDL_GetTicks())
                : nullptr;
  } else {
    throw DrakhtarError(
        "Cannot set an animation that has not been previously added.");
  }
}

void Texture::setAnimationOnce(const std::string& name) {
  previousAnimation_ = animation_.name;
  setAnimation(name);
}

bool Texture::hasAnimation(const std::string& name) const {
  return animations_.count(name) != 0;
}

void Texture::tick() {
  // If no pool is available, omit
  if (pool_ == nullptr) return;

  if (!pool_->next(SDL_GetTicks())) return;

  const auto size = animation_.frames.size();
  // Requires at least two frames to "tick"
  if (size < 2) return;

  // If it is the last tick, set to 0, else add one
  if (++frame_ == size) {
    frame_ = 0;
    if (!previousAnimation_.empty()) {
      const auto nextAnimation = previousAnimation_;
      previousAnimation_ = "";
      setAnimation(nextAnimation);
    }
  }
}

void Texture::render(const Vector2D<int>& position) const {
  const SDL_Rect dest{position.getX(), position.getY(), size_.getX(),
                      size_.getY()};
  render(dest);
}

void Texture::render(const SDL_Rect& dest, double, SDL_Rect* clip) const {
  if (texture_ != nullptr) {
    if (clip == nullptr) {
      SDL_Rect defaultClip = {0, 0, size_.getX(), size_.getY()};
      clip = &defaultClip;
    }
    SDL_RenderCopy(renderer_, texture_, clip, &dest);
  }
}

void Texture::renderFrame(SDL_Rect const& dest, const Uint16 frame,
                          const double angle) const {
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
