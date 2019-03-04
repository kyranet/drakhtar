#pragma once

#include "SDL.h"
#include "EventListener.h"
#include "Board.h"
#include "TurnBar.h"
#include "State.h"

class BoardController : public EventListener
{
protected:
	Board * board_;
	TurnBar * turnBar_;
public:
	BoardController(Board * board, TurnBar * turnBar);
	virtual void run(SDL_Event event);
	void onClick(SDL_Point p);
	void onHover(SDL_Point p);
};
