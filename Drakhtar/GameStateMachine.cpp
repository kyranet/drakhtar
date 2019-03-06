#include "GameStateMachine.h"



GameStateMachine::GameStateMachine()
{
}


GameStateMachine::~GameStateMachine()
{
	while (!stateStack.empty())
	{
		delete stateStack.top();
		stateStack.pop();
	}
	currentState = nullptr;
}

void GameStateMachine::pushState(GameState* state) {
	stateStack.push(state);// error de lectura
	currentState = stateStack.top();
}
void GameStateMachine::changeState(GameState* state) {
	popState();
	pushState(state);
}
void GameStateMachine::popState() {
	if (!stateStack.empty()) {
		delete stateStack.top();
		stateStack.pop();
		currentState = stateStack.top();
	}
}
GameState * GameStateMachine::getCurrentState() {
	return currentState;
}
