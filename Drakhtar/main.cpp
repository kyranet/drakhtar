// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#include <iostream>
#include "Game.h"
#include "SDL.h"
#include "SDL_image.h"
#include "checkML.h"

using namespace std;

int main(int argc, char *argv[]) {
  _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF |
                 _CRTDBG_LEAK_CHECK_DF);  // Check Memory Leaks
  try {
    auto game = Game::getInstance();
    game->run();
    delete game;
    return 0;
  } catch (exception e) {
    cout << e.what();
    return -1;
  }
}
