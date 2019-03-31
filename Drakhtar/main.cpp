// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#include <iostream>
#include "Managers/TextureManager.h"
#include "Managers/SDLAudioManager.h"
#include "SDL.h"
#include "Structures/Game.h"
#include "checkML.h"

int main(int argc, char *argv[]) {
  _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF |
                 _CRTDBG_LEAK_CHECK_DF);  // Check Memory Leaks
  try {
    auto game = Game::getInstance();
    game->run();
	SDLAudioManager::destroy();
	TextureManager::destroy();
    delete game;
    return 0;
  } catch (std::exception e) {
    std::cout << e.what();
    return -1;
  }
}
