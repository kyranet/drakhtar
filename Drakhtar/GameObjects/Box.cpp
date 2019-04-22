// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#include "Box.h"

#include "Board.h"
#include "Controllers/UnitsController.h"
#include "GameObjects/TurnBar.h"
#include "Managers/Input.h"
#include "Managers/TextureManager.h"
#include "Managers/TurnManager.h"
#include "Scenes/Scene.h"
#include "Structures/Team.h"
#include "Unit.h"

Box::Box(Scene* scene, const Vector2D<int>& pos, const Vector2D<int>& size,
         const Vector2D<int>& boardIndex, Unit* unit)
    : GameObject(scene, nullptr, pos, size),
      boardIndex_(boardIndex),
      content_(unit),
      size_(std::move(size)) {
  cellTextures_[static_cast<int>(TextureInd::BASE)] =
      TextureManager::get("UI-cellFrame");
  cellTextures_[static_cast<int>(TextureInd::HOVER)] =
      TextureManager::get("UI-cellHover");
  cellTextures_[static_cast<int>(TextureInd::MOVABLE)] =
      TextureManager::get("UI-cellInRange");
  cellTextures_[static_cast<int>(TextureInd::ENEMY)] =
      TextureManager::get("UI-enemyInRange");
  cellTextures_[static_cast<int>(TextureInd::ACTIVE)] =
      TextureManager::get("UI-activeUnit");
  cellTexture_ = TextureInd::BASE;
}

SDL_Rect Box::getRect() const {
  return {position_.getX(), position_.getY(), size_.getX(), size_.getY()};
}

// Renders itself and its content
void Box::render() const {
  const auto texture = cellTextures_[static_cast<int>(cellTexture_)];
  if (hovered_) {
    cellTextures_[static_cast<int>(TextureInd::HOVER)]->render(
        getRect(), texture->getAnimation()[texture->getFrame()]);
  } else {
    texture->render(getRect(), texture->getAnimation()[texture->getFrame()]);
  }
  if (!isEmpty()) {
    getContent()->render();
  }
}

void Box::update() {
  const auto area = getRect();
  hovered_ = Input::isMouseInside(&area);

  if (!isEmpty()) {
    getContent()->update();
  }
}

// ---------- Getters and Setters ----------
bool Box::isEmpty() const { return content_ == nullptr; }

Vector2D<int> Box::getIndex() const { return boardIndex_; }

Unit* Box::getContent() const { return content_; }

void Box::setContent(Unit* content) { content_ = content; }

TextureInd Box::getCurrentTexture() const { return cellTexture_; }

void Box::setCurrentTexture(TextureInd cellTexture) {
  cellTexture_ = cellTexture;
}

void Box::destroyContent() {
  const auto unit = getContent();
  unit->kill();
  unit->getTeam()->getController()->getTurnManager()->remove(unit);
  getScene()->removeGameObject(unit);
  setContent(nullptr);
}
