// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#include "PlayerController.h"

#include <iostream>

#include "Controllers/Handlers/PlayerHandler.h"
#include "GameObjects/Board.h"
#include "GameObjects/Box.h"
#include "GameObjects/Button.h"
#include "GameObjects/Commanders/Commander.h"
#include "GameObjects/TurnBar.h"
#include "GameObjects/Unit.h"
#include "Managers/GameManager.h"
#include "Managers/Input.h"
#include "Managers/SDLAudioManager.h"
#include "Managers/State.h"
#include "Managers/TextureManager.h"
#include "Scenes/GameScene.h"
#include "Structures/Team.h"
#include "Structures/Texture.h"
#include "Utils/Constants.h"

PlayerController::PlayerController(Board* board, GameScene* scene, Team* team,
                                   Team* oppositeTeam)
    : UnitsController(board, scene, team, oppositeTeam) {
  const auto handler = new PlayerHandler(this);
  handler->setActive(false);
  listeners_.push_back(handler);
  board->addEventListener(handler);
}

void PlayerController::onClickMove(Box* boxClicked) {
  if (locked_ || !tutorialDone_) return;

  // Checks if the box clicked is within movement range
  const auto to = boxClicked->getIndex();
  const auto state = getState();
  const auto stats = state->getModifiedAt(activeUnit_->getBox()->getIndex());

  if (!state->isInMoveRange(stats.position_, to, stats.moveRange_)) {
    SDLAudioManager::getInstance()->playChannel(3, 0, 0);
    return;
  }

  locked_ = true;
  SDLAudioManager::getInstance()->playChannel(0, 0, 0);
  move(activeUnit_->getBox()->getIndex(), boxClicked->getIndex());
}

void PlayerController::onClickAttack(Box* boxClicked) {
  if (!tutorialDone_) return;

  auto unit = boxClicked->getContent();

  // If the box clicked was empty, or if the unit is from the same team, skip
  if (!unit || unit->getTeam() == team_) return;

  const auto state = getState();
  const auto stats = state->getModifiedAt(activeUnit_->getBox()->getIndex());
  const auto enemyStats = state->getModifiedAt(boxClicked->getIndex());

  // If the selected unit is not in the attack range, or the attack was not
  // successful, skip
  if (!state->isInRange(stats.position_, enemyStats.position_,
                        stats.attackRange_) ||
      !state->attack(stats.position_, enemyStats.position_))
    return;

  activeUnit_->getTexture()->setAnimationOnce("attack");
  hasAttacked_ = true;
  canAttack_ = false;

  SDLAudioManager::getInstance()->playChannel(5, 0, 0);

  if (!activeUnit_) {
    // Unit dies to counter-attack
    finish();
    return;
  }

  highlightCells();
  if (!canMove_ && !canCastSkills()) {
    // If no actions left, reset and skip turn
    finish();
  }
}

void PlayerController::start() {
  UnitsController::start();
  if (!activeUnit_) return UnitsController::finish();

  skipTurnButton_ = new Button(
      scene_, TextureManager::get("Button-SkipTurn"),
      Vector2D<int>(WIN_WIDTH / 13, WIN_HEIGHT - WIN_HEIGHT / 8),
      Vector2D<int>(static_cast<int>(WIN_WIDTH / 10.5),
                    static_cast<int>(WIN_HEIGHT / 6.75)),
      [this]() { finish(); }, " ", "ButtonFont");
  scene_->addGameObject(skipTurnButton_);
  highlightCells();

  if (!canAttack_ && !canMove_ && !canCastSkills()) finish();
}

void PlayerController::finish() {
  scene_->removeGameObject(skipTurnButton_);
  for (const auto box : board_->getChildren()) {
    reinterpret_cast<Box*>(box)->setCurrentTexture(TextureInd::BASE);
  }

  UnitsController::finish();
}

bool PlayerController::getLocked() const { return locked_; }

bool PlayerController::canCastSkills() {
  if (tutorialDone_ && activeUnit_->isCommander()) {
    for (auto skill : reinterpret_cast<Commander*>(activeUnit_)->getSkills()) {
      if (skill->getRemainingCooldown() == 0) {
        highlightCells();
        return true;
      }
    }
  }
  return false;
}

void PlayerController::highlightCells() {
  // Reset board
  for (const auto box : board_->getChildren()) {
    reinterpret_cast<Box*>(box)->setCurrentTexture(TextureInd::BASE);
  }

  // Highlight active unit
  activeUnit_->getBox()->setCurrentTexture(TextureInd::ACTIVE);
  const auto from = activeUnit_->getBox()->getIndex();
  const auto state = getState();
  const auto stats = state->getModifiedAt(from);
  if (!hasMoved_) {
    const auto cells = state->getCellsInMovementRange(from, stats.moveRange_);
    if (!cells.empty()) {
      canMove_ = true;
      for (const auto& cell : cells) {
        board_->getBoxAt(cell.getX(), cell.getY())
            ->setCurrentTexture(TextureInd::MOVABLE);
      }
    } else {
      canMove_ = false;
    }
  }

  if (!hasAttacked_) {
    const auto cells =
        state->getCellsInAttackRange(from, stats.team_, stats.attackRange_);
    if (!cells.empty()) {
      canAttack_ = true;
      for (const auto& cell : cells) {
        board_->getBoxAt(cell.getX(), cell.getY())
            ->setCurrentTexture(TextureInd::ENEMY);
      }
    } else {
      canAttack_ = false;
    }
  }
}
void PlayerController::onComplete() {
  UnitsController::onComplete();

  locked_ = false;

  // If there are enemies in range, highlight them, otherwise skip turn
  highlightCells();
  if (canAttack_) {
    SDLAudioManager::getInstance()->setChannelVolume(30, 0);
    SDLAudioManager::getInstance()->playChannel(4, 0, 0);
  } else if (!canCastSkills()) {
    finish();
  }
}
