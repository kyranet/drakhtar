#pragma once
#include <stack>
#include <vector>
#include "State.h"
using namespace std;
class State;
class GameStateMachine
{
protected:
	stack <State*> stateStack;
	State * currentState = nullptr;

public:
	GameStateMachine();
	virtual ~GameStateMachine(); 
	void pushState(State* state);
	void changeState(State* state);
	void popState();
	State* getCurrentState();
};

