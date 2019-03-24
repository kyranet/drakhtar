// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#pragma once
#include "ResourceManager.h"
#include "../Structures/Texture.h"
#include <stack>

struct AnimationTextureInfo
{
    string name;
    vector<ushort> frames;
};

class TextureInfo
{
 public:
    TextureInfo(string name, string path, ushort columns, ushort rows, SDL_RendererFlip flip = SDL_FLIP_NONE)
        : name(name), path(path), columns(columns), rows(rows), flip(flip) {}
    ~TextureInfo() { animations.clear(); }
    string name;
    string path;
    ushort columns;
    ushort rows;
    SDL_RendererFlip flip;
    vector<AnimationTextureInfo> animations;
    TextureInfo *addAnimation(string name, vector<ushort> frames)
    {
        animations.push_back({name, frames});
        return this;
    }
};

class TextureManager : public ResourceManager<Texture *>
{
 private:
    static TextureManager *instance;
    TextureManager();
    ~TextureManager();
    stack<TextureInfo *> stack_;

 public:
    TextureInfo *add(string name, string path, ushort columns, ushort rows, SDL_RendererFlip flip = SDL_FLIP_NONE);
    void init(SDL_Renderer *renderer);
    void tick();
    static Texture *get(string name);
    static TextureManager *getInstance();
    static void destroy();
};
