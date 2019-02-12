#pragma once

#include "SDL.h"
#include "State.h"
#include "Texture.h"

using uint = unsigned int;

const uint NUMBER_TEXTURES = 3;

struct TextureInfo
{
	string path;
	uint columns;
	uint rows;
};

const TextureInfo TEXTURES[NUMBER_TEXTURES] {
	TextureInfo{"../images/BlueArcher.png", 1, 1},
	TextureInfo{"../images/FirstBattle.png", 1, 1},
	TextureInfo{"../images/UI/cellFrame.png", 1, 1}
};

class State;

class Game
{
private:
	SDL_Window* window_ = nullptr;
	SDL_Renderer* renderer_ = nullptr;
	Texture** textures_ = nullptr;
	State* state_ = nullptr;
public:
	Game();
	void run();
	virtual ~Game();
	Texture** getTextures();
};

