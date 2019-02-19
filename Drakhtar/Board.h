#pragma once

#include "GameObject.h"
#include "Box.h"
#include "Constants.h"

class Board : public GameObject{
protected:
	int rows, cols;
	Box*** board;
public:
	Board(Texture * cellTexture, int r, int c, float cellSize);
	virtual ~Board();

	virtual void render() const;
	bool isInRange(Vector2D<int> from, Vector2D<int> to, int range);
	Box* getBoxAt(int x, int y);
	int** getCellsInRange(Box box, int range);
	//Box** findPath(Box* start, Box* end, int steps);
	//void step(Box * start, bool dirX, bool dirY, Box** &path, int i);

	const enum objectType {
		outOfBoard,
		outOfRange,
		empty,
		ally,
		enemy
	};
};

