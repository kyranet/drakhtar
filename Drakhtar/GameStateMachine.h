// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#pragma once

#include <stack>
#include <vector>
#include "State.h"
#include "MainMenu.h"

using namespace std;
class GameState;

class GameStateMachine
{
 protected:
    stack<GameState *> stateStack;
    GameState *currentState = nullptr;

 public:
    GameStateMachine();
    virtual ~GameStateMachine();
    void pushState(GameState *state);
    void changeState(GameState *state);
    void popState();
    GameState *getCurrentState();
};
