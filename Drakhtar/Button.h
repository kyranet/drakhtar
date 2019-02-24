#pragma once

#include "checkML.h"
#include <functional>
#include "Texture.h"
#include "GameObject.h"

class Game;

using CallBackOnClick = void(Game* game);

class Button : public GameObject
{
protected:
	int x, y, w, h;	
	Texture* texture;
	Game *game;
	CallBackOnClick *cb;

public:
	Button(Texture* t, int x, int y, int w, int h, void(*callback)(Game* game), Game* game);
	~Button(){}
	
	void render() {};
	
	bool handleEvents(SDL_Event& e);
	void update() {};
};

