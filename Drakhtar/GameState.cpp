#include "GameState.h"


void GameState::render() {
	for (list<GameObject*>::iterator it = gameObjects.begin(); it != gameObjects.end();) {
		((*it++))->render();
	}
}

void GameState::update() {
	
}

void GameState::handleEvents() {
	
}

void GameState::run() {
	render();
	update();
	handleEvents();
}