#include "GameStateMachine.h"



GameStateMachine::GameStateMachine()
{
}


GameStateMachine::~GameStateMachine()
{
	currentState = nullptr;
}

void GameStateMachine::pushState(State* state) {
	stateStack.push(state);// error de lectura
	currentState = stateStack.top();
}
void GameStateMachine::changeState(State* state) {
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
State * GameStateMachine::getCurrentState() {
	return currentState;
}
