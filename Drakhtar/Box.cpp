// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#include "Box.h"
#include "TextureManager.h"
#include "Unit.h"

Box::Box(Scene *scene, Vector2D<int> pos, Vector2D<int> size,
         Vector2D<int> boardIndex, Unit *unit)
    : GameObject(scene, nullptr, pos, size),
      boardIndex_(boardIndex),
      content_(unit) {
  cellTextures_[static_cast<int>(TextureInd::BASE)] = TextureManager::get("UI-cellFrame");
  cellTextures_[static_cast<int>(TextureInd::HOVER)] = TextureManager::get("UI-cellHover");
  cellTextures_[static_cast<int>(TextureInd::MOVABLE)] = TextureManager::get("UI-cellInRange");
  cellTextures_[static_cast<int>(TextureInd::ENEMY)] = TextureManager::get("UI-enemyInRange");
  cellTextures_[static_cast<int>(TextureInd::ACTIVE)] = TextureManager::get("UI-activeUnit");
  cellTexture_ = TextureInd::BASE;
}

// Renders itself and its content
void Box::render() {
  cellTextures_[static_cast<int>(cellTexture_)]->render(
      getRect(), texture_->getAnimation()[texture_->getFrame()]);
  if (!isEmpty()) {
    getContent()->render();
  }
}

void Box::handleEvents(SDL_Event event) {
  // Changes cell texture on mouse hover
  SDL_Point p = {event.motion.x, event.motion.y};
  if (SDL_PointInRect(&p, &getRect())) {
    cellTexture_ = TextureInd::HOVER;
  } else if (cellTexture_ == TextureInd::HOVER) {
    cellTexture_ = TextureInd::BASE;
  }
}

// ---------- Getters and Setters ----------
bool Box::isEmpty() const { return content_ == nullptr; }

Vector2D<int> Box::getIndex() const { return boardIndex_; }

Unit *Box::getContent() const { return content_; }

void Box::setContent(Unit *content) { content_ = content; }

TextureInd Box::getCurrentTexture() const { return cellTexture_; }

void Box::setCurrentTexture(TextureInd cellTexture) {
  cellTexture_ = cellTexture;
}
