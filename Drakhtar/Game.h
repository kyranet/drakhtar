#pragma once

#include "SDL.h"
#include "SDL_ttf.h"
#include "GameState.h"
#include "SDL_mixer.h"
#include "State.h"
#include "Texture.h"
#include "GameStateMachine.h"
#include "Constants.h"
#include "TextureManager.h"


typedef unsigned int uint;

class GameState;
class GameStateMachine;

class Game
{
private:
	static Game* instance;
	SDL_Window* window_ = nullptr;
	SDL_Renderer* renderer_ = nullptr;
	SDL_Event event;
	bool _exit = false;
	TextureManager* textureManager_ = TextureManager::getInstance();
	GameStateMachine* stateMachine = nullptr;
	GameState* state_ = nullptr;
	GameState* actualstate_ = nullptr;
	Game();
public:
	void run();
	virtual ~Game();
	SDL_Renderer* getRenderer();	
	static Game* getInstance();
	static GameState* currentState();
	GameStateMachine* getStateMachine();
	

};
