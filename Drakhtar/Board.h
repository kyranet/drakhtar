#pragma once

#include "GameObject.h"

class Board : public GameObject{
protected:
	int rows, cols, cellSize;
	Texture* cellFrame;
	GameObject*** board;
public:
	Board(Texture* cf, int r, int c, int cs);
	virtual ~Board();

	virtual void render() const;
};

