// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#include <iostream>
#include "Managers/Input.h"
#include "Managers/SDLAudioManager.h"
#include "Managers/TextureManager.h"
#include "SDL.h"
#include "Structures/Game.h"
#include "checkML.h"

int main(int argc, char *argv[]) {
  _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF |
                 _CRTDBG_LEAK_CHECK_DF);  // Check Memory Leaks
  try {
    const auto game = Game::getInstance();
    game->run();
    SDLAudioManager::destroy();
    TextureManager::destroy();
    Input::destroy();
    delete game;
    return 0;
  } catch (std::exception e) {
    std::cout << e.what();
    return -1;
  }
}
