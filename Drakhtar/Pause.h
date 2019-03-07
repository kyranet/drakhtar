#pragma once
#include "Button.h"
#include "SDL.h"
#include "GameState.h"
class Pause :  public GameState
{
private:
	SDL_Renderer* renderer_ = nullptr;
	Button* Play;
	Button* Options;
public:
	Pause(SDL_Renderer* renderer);
	virtual ~Pause();
	void _preload();
	static void Play_game(Game* game, SDL_Renderer* renderer);
	static void Options_game(Game* game, SDL_Renderer* renderer);
};

