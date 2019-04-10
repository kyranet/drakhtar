// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#include "TeamController.h"
#include <iostream>
#include "GameObjects/Board.h"
#include "GameObjects/Box.h"
#include "GameObjects/TurnBar.h"
#include "GameObjects/Unit.h"
#include "Managers/GameManager.h"
#include "Managers/SDLAudioManager.h"
#include "Scenes/GameScene.h"
#include "Structures/Team.h"
#include "Structures/Texture.h"
#include "Structures/Tween.h"
#include "Utils/Constants.h"

TeamController::TeamController(Board *board, TurnBar *turnBar, GameScene *scene)
    : board_(board), turnBar_(turnBar), scene_(scene), ListenerOnClick(board) {
  activeUnit_ = turnBar_->getFrontUnit();
}
/*
void TeamController::run(const SDL_Event event) {
        // Captures mouse event
        ListenerOnClick::run(event);

        // If no actions left, reset and skip turn
        if (hasMoved_ && hasAttacked_) {
                advanceTurn();
        }
}
*/
