// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#include "Box.h"
#include "Board.h"
#include "Controllers/UnitsController.h"
#include "GameObjects/TurnBar.h"
#include "Managers/Input.h"
#include "Managers/State.h"
#include "Managers/TextureManager.h"
#include "Scenes/GameScene.h"
#include "Scenes/Scene.h"
#include "Structures/Team.h"
#include "Unit.h"

Box::Box(Scene* scene, const Vector2D<int>& pos, const Vector2D<int>& size,
         const Vector2D<uint16_t>& boardIndex)
    : GameObject(scene, nullptr, pos, size),
      boardIndex_(boardIndex),
      size_(size) {
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
  cellTextures_[static_cast<int>(TextureInd::HOVER_MOVABLE)] =
      TextureManager::get("UI-cellHoverBlue");
  cellTextures_[static_cast<int>(TextureInd::HOVER_ENEMY)] =
      TextureManager::get("UI-cellHoverRed");
  cellTexture_ = TextureInd::BASE;
}

SDL_Rect Box::getRect() const {
  return {position_.getX(), position_.getY(), size_.getX(), size_.getY()};
}

// Renders itself and its content
void Box::render() const {
  const auto texture = cellTextures_[static_cast<int>(cellTexture_)];
  if (hovered_) {
    if (cellTexture_ == TextureInd::MOVABLE) {
      cellTextures_[static_cast<int>(TextureInd::HOVER_MOVABLE)]->render(
          getRect(), texture->getAnimation()[texture->getFrame()]);
    } else if (cellTexture_ == TextureInd::ENEMY) {
      cellTextures_[static_cast<int>(TextureInd::HOVER_ENEMY)]->render(
          getRect(), texture->getAnimation()[texture->getFrame()]);
    } else {
      cellTextures_[static_cast<int>(TextureInd::HOVER)]->render(
          getRect(), texture->getAnimation()[texture->getFrame()]);
    }
  } else {
    texture->render(getRect(), texture->getAnimation()[texture->getFrame()]);
  }

  const auto unit = getContent();
  if (unit) unit->render();
}

void Box::update() {
  const auto area = getRect();
  hovered_ = Input::isMouseInside(&area);

  const auto unit = getContent();
  if (unit) {
    // TODO(kyranet): Don't use this. Stop this. Get some help.
    unit->update();
  }
}

// ---------- Getters and Setters ----------
bool Box::isEmpty() const { return getContent() == nullptr; }

Vector2D<uint16_t> Box::getIndex() const { return boardIndex_; }

TextureInd Box::getCurrentTexture() const { return cellTexture_; }

void Box::setCurrentTexture(TextureInd cellTexture) {
  cellTexture_ = cellTexture;
}

void Box::destroyContent() {
  const auto scene = reinterpret_cast<GameScene*>(getScene());
  const auto state = scene->getState();
  const auto unit = state->getUnitAt(getIndex());

  if (unit != nullptr) {
    unit->kill();
  }
}

Unit* Box::getContent() const {
  const auto scene = reinterpret_cast<GameScene*>(getScene());
  const auto state = scene->getState();
  const auto unit = state->getUnitAt(getIndex());
  return unit;
}
