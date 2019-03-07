#pragma once

#include "checkML.h"
#include <functional>
#include "Texture.h"
#include "GameObject.h"

class Game;

using CallBackOnClick = void(Game* game, SDL_Renderer* renderer);
using CallBackOnClickPause = void( SDL_Renderer* renderer);

class Button : public GameObject
{
protected:
	int x, y, w, h;	
	Texture* texture;
	Game *game;
	SDL_Renderer* renderer;
	CallBackOnClick *cb;
	CallBackOnClickPause *cbPause;
public:
	Button(Texture* t, int x, int y, int w, int h, void(*callback)(Game* game, SDL_Renderer* renderer), Game* game, SDL_Renderer* renderer);
	Button(Texture* t, int x, int y, int w, int h, void(*callback)(SDL_Renderer* renderer), SDL_Renderer* renderer);

	~Button(){}
	
	void render() {};
	
	void handleEvents(SDL_Event& e);
	void update() {};
};

