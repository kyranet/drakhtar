// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#include "Box.h"
#include "TextureManager.h"
#include "Unit.h"

Box::Box(Texture *t, Vector2D<int> pos, Vector2D<int> size, Vector2D<int> bi,
         Unit *go)
    : GameObject(t, pos, size), boardIndex(bi), content(go) {
  cellTextures[BASE_TEX] = t;
  cellTextures[HOVER_TEX] = TextureManager::get("UI-cellHover");
  cellTextures[MOVABLE_TEX] = TextureManager::get("UI-cellInRange");
  cellTextures[ENEMY_TEX] = TextureManager::get("UI-enemyInRange");
  cellTextures[ACTICE_TEX] = TextureManager::get("UI-activeUnit");
  currentTexture = BASE_TEX;
}

Box::~Box() { content = nullptr; }

// Renders itself and its content
void Box::render() {
  cellTextures[currentTexture]->render(
      getRect(), texture_->getAnimation()[texture_->getFrame()]);
  if (content != nullptr) {
    content->render();
  }
}

void Box::handleEvents(SDL_Event event) {
  // Changes cell texture on mouse hover
  SDL_Point p = {event.motion.x, event.motion.y};
  if (SDL_PointInRect(&p, &getRect())) {
    currentTexture = HOVER_TEX;
  } else if (currentTexture == HOVER_TEX) {
    currentTexture = BASE_TEX;
  }
}

// ---------- Getters and Setters ----------

Vector2D<int> Box::getIndex() { return boardIndex; }

Unit *Box::getContent() { return content; }

void Box::setContent(Unit *object) { content = object; }

bool Box::isEmpty() { return content == nullptr; }

int Box::getCurrentTexture() const { return currentTexture; }

void Box::setCurrentTexture(int textureInd) { currentTexture = textureInd; }
