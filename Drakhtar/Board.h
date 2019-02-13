#pragma once

#include "GameObject.h"
#include "Box.h"

class Board : public GameObject{
protected:
	int rows, cols;
	Box*** board;
public:
	Board(Texture* cf, int r, int c, float cs);
	virtual ~Board();

	virtual void render() const;
};

