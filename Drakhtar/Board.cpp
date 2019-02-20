#include "Board.h"
#include "Unit.h"
#include "Controller.h"

Board::Board(Texture* cellTexture, int r, int c, float cellSize)
	: GameObject(nullptr, Vector2D<int>(0, 0), Vector2D < int>(0, 0)), rows(r), cols(c)
{
	// Calculates margins to center the board on screen
	marginX = (WIN_WIDTH - (cellSize * (cols - 1))) / 2;
	marginY = (WIN_HEIGHT - (cellSize * (rows - 1))) / 2;

	// Creates the board matrix
	board = new Box**[rows];
	for (int i = 0; i < rows; i++) {
		board[i] = new Box*[cols];
	}

	// Fills the board with empty boxes
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			Vector2D<int> pos = Vector2D<int>((int)floor(marginX + j * cellSize), (int)floor(marginY + i * cellSize));
			Vector2D<int> size = Vector2D<int>((int)floor(cellSize), (int)floor(cellSize));
			Box* box = new Box(cellTexture, pos, size, Vector2D<int>(i, j), nullptr);
			box->addEventListener(new Controller(box));
			board[i][j] = box;
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

bool Board::isInRange(Vector2D<int> from, Vector2D<int> to, int range) {
	int distance = abs((to.getX() - from.getX()) + (to.getY() - to.getY()));
	if (range >= distance) {
		return true;
	} else {
		return false;
	}
}

Box* Board::getBoxAt(int x, int y) {
	return board[x][y];
}

int ** Board::getCellsInRange(Box box, int range) {
	int size = range * 2 + 1;
	int startX = box.getIndex().getX() - range;
	int startY = box.getIndex().getY() - range;

	// Creates the array
	int** cellsInRange = new int*[size];
	for (int i = 0; i < rows; i++) {
		cellsInRange[i] = new int[size];
	}

	// Fills the array
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			// Current cell is out of the board
			if (i + startX < 0 || j + startY < 0) {
				cellsInRange[i][j] = outOfBoard;

			// Current cell is out of the movement range
			} else if(abs(box.getIndex().getX() - i + startX) + abs(box.getIndex().getY() - j + startY) > range) {
				cellsInRange[i][j] = outOfRange;

			// Current cell is in the board and in range
			} else {
				Unit* unit = board[i + startX][j + startY]->getContent();

				// Current cell is empty
				if (unit == nullptr) { cellsInRange[i][j] = empty; }

				// Current cell is occupied
				else {
					if (unit->getTeam() == box.getContent()->getTeam()) { cellsInRange[i][j] = ally; }	// Ally
					else { cellsInRange[i][j] = enemy; }	// Enemy
				}
			}
		}
	}

	return cellsInRange;
}

Vector2D<int> Board::getCellIndexFromCoordinates(Vector2D<int> coordinates) {
	// Coordinates are out of the board
	if (coordinates.getX() < marginX || coordinates.getY() < marginY ||
		coordinates.getX() > marginX + this->getRect().w || coordinates.getY() > marginY + this->getRect().h) {
		return Vector2D<int>(-1, -1);
		// Coordinates are inside the board
	}
	else {
		int x = (int)floor((coordinates.getX() - marginX) / cellSize);
		int y = (int)floor((coordinates.getY() - marginY) / cellSize);
		return Vector2D<int>(x, y);
	}
}

void Board::handleEvents(SDL_Event event) {
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			board[i][j]->handleEvents(event);
		}
	}
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