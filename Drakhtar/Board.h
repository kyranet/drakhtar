#pragma once

#include "GameObject.h"
#include "Box.h"
#include "Constants.h"

class Board : public GameObject{
protected:
	int rows, cols;
	float marginX, marginY, cellSize;
	Box*** board;
public:
	Board(Texture * cellTexture, int r, int c, float cellSize);
	virtual ~Board();

	virtual void render() const;
	virtual void handleEvents(SDL_Event event);

	Box* getBoxAt(int x, int y);
	Box* getBoxAtCoordinates(Vector2D<int> coordinates);
	bool isInRange(Vector2D<int> from, Vector2D<int> to, int range);
	int** getCellsInRange(Box box, int range);

	const enum objectType {
		outOfBoard,
		outOfRange,
		empty,
		ally,
		enemy
	};
};

