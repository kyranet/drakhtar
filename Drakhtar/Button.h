#pragma once

#include "checkML.h"
#include <functional>
#include "Text.h"
#include "Game.h"

class Button : public Text
{
private:
	SDL_Color _inColor;
	SDL_Color _outColor;
	bool _mouseIn = false;
	function<void()> _callback;

public:
	Button(Font * font, int x, int y, int width, int height,
		SDL_Color inColor, SDL_Color outColor, string text, function<void()> callback)
		: Text(renderer, font, (x, y), outColor, text), _inColor(inColor), _outColor(outColor), _callback(callback) {};
	~Button() {};
	virtual void handleEvents(SDL_Event event);
};

