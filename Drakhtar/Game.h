#pragma once

#include "SDL.h"
#include "SDL_ttf.h"
#include "SDL_mixer.h"
#include "State.h"
#include "Texture.h"
#include "GameStateMachine.h"
#include "Constants.h"
#include "TextureManager.h"

typedef unsigned int uint;

class State;
class GameStateMachine;

class Game
{
private:
	static Game* instance;
	SDL_Window* window_ = nullptr;
	SDL_Renderer* renderer_ = nullptr;
	TextureManager* textureManager_ = TextureManager::getInstance();
	GameStateMachine* stateMachine = nullptr;
	State* state_ = nullptr;
	Game();
public:
	void run();
	virtual ~Game();
	SDL_Renderer* getRenderer();
	static Game* getInstance();
	static State* currentState();
};
