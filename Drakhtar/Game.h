#pragma once

#include "SDL.h"
#include "SDL_ttf.h"
#include "State.h"
#include "Texture.h"
#include "GameStateMachine.h"
#include "Constants.h"

using uint = unsigned int;

const uint NUMBER_TEXTURES = 10;

struct TextureInfo
{
	string path;
	uint columns;
	uint rows;
};

enum Textures {
	BLUE_ARCHER,
	BLUE_CAVALRY,
	FIRST_BATTLE,
	CELL_FRAME,
	DIALOG_BLOCK,
	NARRATOR,
	THASSA,
	VALAR,
	RED,
	CELL_FRAME
};

const TextureInfo TEXTURES[NUMBER_TEXTURES] {
	TextureInfo{"../images/Units/BlueArcher.png", 2, 1},
	TextureInfo{"../images/BlueCavalry.png", 1, 1},
	TextureInfo{"../images/Maps/FirstBattle.png", 1, 1},
	TextureInfo{"../images/UI/cellFrame.png", 1, 1},
	TextureInfo{"../images/UI/dialogueBackground.png", 1, 1},
	TextureInfo{"../images/Portraits/characterPlaceholder.png", 1, 1},
	TextureInfo{"../images/Portraits/characterPlaceholder.png", 1, 1},
	TextureInfo{"../images/Portraits/characterPlaceholder.png", 1, 1},
	TextureInfo{"../images/red.JPG", 1, 1},
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

