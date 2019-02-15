#include "Board.h"

Board::Board(Texture* cellTexture, int r, int c, float cellSize) : GameObject(nullptr, 0, 0, 0, 0), rows(r), cols(c) {
	// Calculates margins to center the board on screen
	float marginX = (800 - (cellSize * (cols - 1))) / 2;
	float marginY = (600 - (cellSize * (rows - 1))) / 2;

	// Creates the board matrix
	board = new Box**[rows];
	for (int i = 0; i < rows; i++) {
		board[i] = new Box*[cols];
	}

	// Fills the board with empty boxes
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			vector2d pos = { marginX + j * cellSize, marginY + i * cellSize };
			board[i][j] = new Box(cellTexture, pos, { cellSize, cellSize }, i, j, nullptr);
		}
	}
}

Board::~Board() {
	if (board != nullptr) {
		for (int r = 0; r < rows; r++) {
			for (int c = 0; c < cols; c++) {
				delete board[r][c];
			}
			delete board[r];
		}
		delete[] board;
		board = nullptr;
	}
}

void Board::render() const {
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			if (board[i][j] != nullptr) {
				board[i][j]->render();
			}
		}
	}
}

bool Board::isInRange(vector2d from, vector2d to, int range) {
	int distance = abs((to.x - from.x) + (to.y - to.y));
	if (range >= distance) {
		return true;
	} else {
		return false;
	}
}

Box* Board::getBoxAt(int x, int y) {
	return board[x][y];
}
/*
Box ** Board::findPath(Box * start, Box * end, int steps) {
	Box** path = new Box*[steps];

	// Determines axis direction: true positive, false negative
	bool dirX, dirY;
	if (start->getIndex().x - end->getIndex().x < 0) { dirX = true; }
	if (start->getIndex().x - end->getIndex().x > 0) { dirX = false; }
	if (start->getIndex().y - end->getIndex().y < 0) { dirY = true; }
	if (start->getIndex().y - end->getIndex().y > 0) { dirY = false; }

	step(start, dirX, dirY, path, 0);

	return path;
}

void Board::step(Box * start, bool dirX, bool dirY, Box **& path, int i) {
	Box* nextStep;
	vector2d startIndex = start->getIndex();

	// Try right
	if (dirX && startIndex.x + 1 < cols) {
		if (getBoxAt(startIndex.x + 1, startIndex.y)->getContent() == nullptr) {
			nextStep = getBoxAt(startIndex.x + 1, startIndex.y);
		}
	}

	// Try left
	if (!dirX && startIndex.x + 1 < cols) {
		if (getBoxAt(startIndex.x + 1, startIndex.y)->getContent() == nullptr) {
			nextStep = getBoxAt(startIndex.x + 1, startIndex.y);
		}
	}
}
*/