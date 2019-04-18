// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#include "PlayerController.h"

#include <iostream>

#include "GameObjects/Board.h"
#include "GameObjects/Box.h"
#include "GameObjects/TurnBar.h"
#include "GameObjects/Unit.h"
#include "Managers/GameManager.h"
#include "Managers/Input.h"
#include "Managers/SDLAudioManager.h"
#include "Scenes/GameScene.h"
#include "Structures/Team.h"
#include "Structures/Texture.h"
#include "Structures/Tween.h"
#include "Utils/Constants.h"

PlayerController::PlayerController(Board* board, TurnBar* turnBar,
                                   GameScene* scene)
    : UnitsController(board, turnBar, scene), ListenerOnClick(board) {
  activeUnit_->getBox()->setCurrentTexture(TextureInd::ACTIVE);
  board_->highlightCellsInRange(activeUnit_->getBox(),
                                activeUnit_->getStats().moveRange);
  board_->highlightEnemiesInRange(activeUnit_->getBox(),
                                  activeUnit_->getStats().attackRange);
}

void PlayerController::run(const SDL_Event) {
  if (!Input::isMouseButtonDown(MouseKey::LEFT)) return;

  const auto gameObject = Input::screenMouseToRay();
  if (!gameObject) return;

  // Ignore Unit's "hitboxes" and assume it's a click to the board, so get the
  // box at the mouse's coordinates
  const auto unit = dynamic_cast<Unit*>(gameObject);
  const auto box = unit ? board_->getBoxAtCoordinates(Input::getMousePosition())
                        : dynamic_cast<Box*>(gameObject);
  if (!box) return;

  if (!hasMoved_ && box->isEmpty()) {
    onClickMove(box);
  } else if (!hasAttacked_) {
    onClickAttack(box);
  }
}

void PlayerController::onClickMove(Box* boxClicked) {
  // Checks if the box clicked is within movement range
  if (board_->isInMoveRange(activeUnit_->getBox(), boxClicked,
                            activeUnit_->getStats().moveRange)) {
    const auto path = board_->findPath(activeUnit_->getBox()->getIndex(),
                                       boxClicked->getIndex());

    setActive(false);
    SDLAudioManager::getInstance()->playChannel(0, 0, 0);
    const auto unit = activeUnit_;
    scene_->getTweenManager()
        ->create()
        ->setRoute(board_->pathToRoute(path))
        ->setDuration(static_cast<int>(
            floor(static_cast<double>(path.size()) * GAME_FRAMERATE * 0.25)))
        ->setOnUpdate([unit](Vector2D<double> updated) {
          unit->setPosition({static_cast<int>(std::floor(updated.getX())),
                             static_cast<int>(std::floor(updated.getY()))});
        })
        ->setOnComplete([this, unit, boxClicked]() {
          unit->moveToBox(boxClicked);
          hasMoved_ = true;
          setActive(true);
          // If there are enemies in range, highlight them, otherwise skip turn
          if (board_->isEnemyInRange(boxClicked,
                                     unit->getStats().attackRange)) {
            board_->resetCellsToBase();
            unit->getBox()->setCurrentTexture(TextureInd::ACTIVE);
            board_->highlightEnemiesInRange(unit->getBox(),
                                            unit->getStats().attackRange);
            SDLAudioManager::getInstance()->setChannelVolume(30, 0);
            SDLAudioManager::getInstance()->playChannel(4, 0, 0);
          } else {
            advanceTurn();
          }

          // If no actions left, reset and skip turn
          if (hasMoved_ && hasAttacked_) {
            advanceTurn();
          }
        });
  } else {
    std::cout << "Out of movement range!\n";
    SDLAudioManager::getInstance()->playChannel(3, 0, 0);
  }
}

void PlayerController::onClickAttack(Box* boxClicked) {
  Unit* enemyUnit = boxClicked->getContent();
  if (enemyUnit != nullptr) {
    // Unit clicked if from a different team and in range
    if (enemyUnit->getTeam() != activeUnit_->getTeam() &&
        board_->isInRange(activeUnit_->getBox(), boxClicked,
                          activeUnit_->getStats().attackRange)) {
      activeUnit_->getTexture()->setAnimationOnce("attack");
      activeUnit_->attack(enemyUnit, false);
      SDLAudioManager::getInstance()->playChannel(5, 0, 0);

      // Enemy dies
      if (enemyUnit->getStats().health == 0) {
        if (enemyUnit->getTeam()->getColor() == Color::RED) {
          GameManager::getInstance()->addMoney(enemyUnit->getStats().prize);
        }
        boxClicked->setContent(nullptr);
        enemyUnit->getTeam()->removeUnit(enemyUnit);
        scene_->removeGameObject(enemyUnit);
      }

      // Re-highlight board
      board_->resetCellsToBase();
      activeUnit_->getBox()->setCurrentTexture(TextureInd::ACTIVE);
      board_->highlightCellsInRange(activeUnit_->getBox(),
                                    activeUnit_->getStats().moveRange);
      hasAttacked_ = true;

      // Unit dies to counter-attack
      if (activeUnit_->getStats().health == 0) {
        activeUnit_->getBox()->setContent(nullptr);
        activeUnit_->getTeam()->removeUnit(activeUnit_);
        scene_->removeGameObject(activeUnit_);
        advanceTurn();
      }

      // If no actions left, reset and skip turn
      if (hasMoved_ && hasAttacked_) {
        advanceTurn();
      }
    }
  }
}

void PlayerController::advanceTurn() {
  board_->resetCellsToBase();
  hasMoved_ = hasAttacked_ = false;
  turnBar_->next();
  // activeUnit_ = turnBar_->getFrontUnit();

  activeUnit_->getBox()->setCurrentTexture(TextureInd::ACTIVE);
  board_->highlightCellsInRange(activeUnit_->getBox(),
                                activeUnit_->getStats().moveRange);
  board_->highlightEnemiesInRange(activeUnit_->getBox(),
                                  activeUnit_->getStats().attackRange);
}
