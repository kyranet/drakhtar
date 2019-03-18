// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#pragma once
#include "checkML.h"
#include "SDL.h"
#include "SDL_image.h"
#include "Vector2D.h"
#include "Font.h"
#include <string>
#include <vector>
#include <map>

using namespace std;

typedef unsigned int uint;
typedef uint16_t ushort;

class Texture
{
 private:
    SDL_Texture *texture_ = nullptr;
    SDL_Renderer *renderer_ = nullptr;
    Vector2D<ushort> size_;
    Vector2D<ushort> frameSize_;
    uint columnAmount_ = 1;
    uint rowAmount_ = 1;
    map<string, vector<ushort>> animations_;
    vector<ushort> animation_;
    ushort frame_ = 0;
    SDL_RendererFlip flip_ = SDL_FLIP_NONE;

 public:
    Texture() {}
    explicit Texture(SDL_Renderer *r) : renderer_(r) {}
    virtual ~Texture();

    ushort getColumnAmount() const { return columnAmount_; }
    ushort getRowAmount() const { return rowAmount_; }
    ushort getFrame() const { return frame_; }
    Vector2D<ushort> getSize() const { return size_; }
    Vector2D<ushort> getFrameSize() const { return frameSize_; }
    Vector2D<ushort> getFramePosition(ushort frame) const
    {
        return Vector2D<ushort>(frame % columnAmount_, (ushort)floor(frame / columnAmount_));
    }
    vector<ushort> getAnimation() const { return animation_; }
    SDL_Texture *getTexture() const { return texture_; }
    SDL_Renderer *getRenderer() const { return renderer_; }
    SDL_RendererFlip getFlip() const { return flip_; }

    Texture *setTexture(SDL_Texture *const &texture);
    Texture *setColumnAmount(ushort columns);
    Texture *setRowAmount(ushort rows);
    Texture *setFrameSize(Vector2D<ushort> const &frameSize);
    Texture *setFlip(SDL_RendererFlip const &flip);
    Texture *loadFromImage(string filename, ushort rowAmount = 1, ushort columnAmount = 1);
    Texture *loadFromText(Font *font, string text, SDL_Color const color = {0, 0, 0, 255});
    void addAnimation(string name, vector<ushort> const &frames);
    void setAnimation(string name);
    bool hasAnimation(string name);
    void tick();
    void render(Vector2D<int> position) const;
    void render(SDL_Rect const &dest, double angle = 0, SDL_Rect *clip = nullptr) const;
    void renderFrame(SDL_Rect const &dest, ushort frame, double angle = 0) const;
    void close();
};
