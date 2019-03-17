// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#include "TextureManager.h"
#include "DrakhtarError.h"

TextureManager *TextureManager::instance = nullptr;

TextureManager *TextureManager::getInstance()
{
    if (instance == nullptr)
    {
        instance = new TextureManager();
    }

    return instance;
}

TextureManager::TextureManager() {}

TextureInfo *TextureManager::add(string name, string path, ushort columns, ushort rows, SDL_RendererFlip flip)
{
    auto info = new TextureInfo(name, path, columns, rows, flip);
    stack_.push(info);
    return info;
}

void TextureManager::init(SDL_Renderer *renderer)
{
    while (!stack_.empty())
    {
        auto info = stack_.top();
        auto texture = (new Texture(renderer))->loadFromImage(info->path, info->rows, info->columns);
        texture->setFlip(info->flip);

        // Add all the queued animations
        for (auto animation : info->animations)
            texture->addAnimation(animation.name, animation.frames);

        // If there was no default animation override, add it
        if (!texture->hasAnimation("default"))
        {
            ushort frames = texture->getColumnAmount() * texture->getRowAmount();
            vector<ushort> animation(frames);
            for (ushort i = 0; i < frames; i++)
                animation[i] = i;
            texture->addAnimation("default", animation);
        }

        texture->setAnimation("default");

        // Insert the texture to the map, pop the stack, and delete the temporary information
        map_.insert(pair<string, Texture *>(info->name, texture));
        stack_.pop();
        delete info;
    }
}

void TextureManager::tick()
{
    if (instance == nullptr)
        return;
    for (auto pair : map_)
    {
        pair.second->tick();
    }
}

Texture *TextureManager::get(string name)
{
    return getInstance()->map_[name];
}

TextureManager::~TextureManager()
{
    while (!stack_.empty())
        stack_.pop();
    for (auto pair : map_)
        delete pair.second;
    map_.clear();
}

void TextureManager::destroy()
{
    if (instance != nullptr)
    {
        delete instance;
        instance = nullptr;
    }
}
