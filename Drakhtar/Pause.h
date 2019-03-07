#pragma once
#include "Button.h"
#include "SDL.h"
#include "GameState.h"

class Pause :  public GameState
{
private:
	SDL_Renderer* renderer_ = nullptr;
	Button* Resume;
	Button* Options;
	list<GameObject*> gameObjectsPause_;
public:
	Pause(SDL_Renderer* renderer);
	virtual ~Pause();
	void _preload();
	void _render();
	void _handleEvents(SDL_Event& e);
	static void resumeGame(SDL_Renderer* renderer);
	static void optionsGame( SDL_Renderer* renderer);
};

