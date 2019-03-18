// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#include "Box.h"
#include "Unit.h"
#include "TextureManager.h"

Box::Box(Texture *t, Vector2D<int> pos, Vector2D<int> size, Vector2D<int> bi, Unit *go)
    : GameObject(t, pos, size), boardIndex(bi), content(go)
{
    cellTextures[base] = t;
    cellTextures[hover] = TextureManager::get("UI-cellHover");
    cellTextures[movable] = TextureManager::get("UI-cellInRange");
    currentTexture = base;
}

Box::~Box()
{
    content = nullptr;
}

// Renders itself and its content
void Box::render()
{
    cellTextures[currentTexture]->render(getRect(), texture_->getAnimation()[texture_->getFrame()]);
    if (content != nullptr)
    {
        content->render();
    }
}

void Box::handleEvents(SDL_Event event)
{
    SDL_Point p = {event.motion.x, event.motion.y};
    if (SDL_PointInRect(&p, &getRect()))
    {
        currentTexture = hover;
    }
    else if (currentTexture == hover)
    {
        currentTexture = base;
    }
}

Vector2D<int> Box::getIndex()
{
    return boardIndex;
}

Unit *Box::getContent()
{
    return content;
}

void Box::setContent(Unit *object)
{
    content = object;
}

bool Box::isEmpty()
{
    return content == nullptr;
}

int Box::getCurrentTexture() const
{
    return currentTexture;
}

void Box::setCurrentTexture(int textureInd)
{
    currentTexture = textureInd;
}
