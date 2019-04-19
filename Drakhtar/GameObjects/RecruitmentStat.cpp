// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.
#include "RecruitmentStat.h"

#include "../Managers/FontManager.h"
#include "../Managers/TextureManager.h"
#include "../Scenes/Scene.h"
#include "../Structures/Font.h"
#include "../Utils/Constants.h"
#include "../Utils/Vector2D.h"
#include "GameObjects/Button.h"
#include "GameObjects/Unit.h"
#include "Text.h"
RecruitmentStat::RecruitmentStat(Scene* scene, const SDL_Rect BoxArea,
                                 StoreUnit* controller)
    : GameObject(scene, nullptr, Vector2D<int>(WIN_WIDTH / 2, WIN_HEIGHT / 2),
                 Vector2D<int>(1, 1)),
      currentSelected_(controller) {
  auto pos = currentSelected_->unit->getPosition();
  const auto boxImage = new Button(
      scene, TextureManager::get("UI-tutorialBackground"),
      Vector2D<int>(pos.getX() + 510, pos.getY()),
      Vector2D<int>(BoxArea.w, BoxArea.h), [this]() { setActive(false); });
  addChild(boxImage);

  std::string statText_ = fillText();
  const auto statTextSprite =
      new Text(scene_, FontManager::get("Retron2000"),
               Vector2D<int>(
                   boxImage->getPosition().getX() - boxImage->getRect().w / 30,
                   boxImage->getPosition().getY() - boxImage->getRect().h / 20),
               {0, 0, 0, 1}, statText_, BoxArea.w * 0.9);
  addChild(statTextSprite);
  active_ = true;
}

void RecruitmentStat::render() const {
  if (active_) {
    GameObject::render();
  }
}

std::string RecruitmentStat::fillText() {
  const auto unit = reinterpret_cast<Unit*>(currentSelected_->unit);
  std::string text = "Unit type: " + currentSelected_->type + "\n";
  text += "Total amount: " + std::to_string(currentSelected_->amount_) + "\n";
  text += "Attack-> " + std::to_string(unit->getBaseStats().attack) + "\n";
  text += "Defense-> " + std::to_string(unit->getBaseStats().defense) + "\n";
  text += "Speed-> " + std::to_string(unit->getBaseStats().speed) + "\n";
  return text;
}

void RecruitmentStat::updateText() { fillText(); }

RecruitmentStat::~RecruitmentStat() {}
