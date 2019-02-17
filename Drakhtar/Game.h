#pragma once

#include "SDL.h"
#include "State.h"
#include "Texture.h"
#include "GameStateMachine.h"

using uint = unsigned int;

const uint NUMBER_TEXTURES = 3;

struct TextureInfo
{
	string path;
	uint columns;
	uint rows;
};

enum Textures {
	BLUE_ARCHER,
	FIRST_BATTLE,
	CELL_FRAME
};

const TextureInfo TEXTURES[NUMBER_TEXTURES] {
	TextureInfo{"../images/BlueArcher.png", 2, 1},
	TextureInfo{"../images/Maps/FirstBattle.png", 1, 1},
	TextureInfo{"../images/UI/cellFrame.png", 1, 1}
};

class State;
class GameStateMachine;

class Game
{
private:
	SDL_Window* window_ = nullptr;
	SDL_Renderer* renderer_ = nullptr;
	Texture** textures_ = nullptr;
	GameStateMachine * stateMachine = nullptr;
	State* state_ = nullptr;
public:
	Game();
	void run();
	virtual ~Game();
	Texture** getTextures();
	SDL_Renderer* getRenderer();
};

