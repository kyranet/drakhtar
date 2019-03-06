#include "Board.h"
#include "Unit.h"

Board::Board(Texture* cellTexture, int r, int c, float cs)
	: GameObject(nullptr, Vector2D<int>(0, 0), Vector2D < int>(0, 0)), rows(r), cols(c), cellSize(cs)
{
	// Calculates margins to center the board on screen
	marginX = (WIN_WIDTH - (cs * (cols - 1))) / 2;
	marginY = (WIN_HEIGHT - (cs * (rows - 1))) / 2;

	// Creates the board matrix
	board = new Box**[rows];
	for (int i = 0; i < rows; i++) {
		board[i] = new Box*[cols];
	}

	// Fills the board with empty boxes
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			Vector2D<int> pos = Vector2D<int>((int)floor(marginX + j * cs), (int)floor(marginY + i * cs));
			Vector2D<int> size = Vector2D<int>((int)floor(cs), (int)floor(cs));
			Box* box = new Box(cellTexture, pos, size, Vector2D<int>(i, j), nullptr);
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

void Board::handleEvents(SDL_Event event) {
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			board[i][j]->handleEvents(event);
		}
	}
}

Box* Board::getBoxAt(int x, int y) {
	return board[y][x];
}

Box* Board::getBoxAtCoordinates(Vector2D<int> coordinates) {
	// Coordinates are out of the board
	if (coordinates.getX() < marginX - cellSize/2 || coordinates.getY() < marginY - cellSize/2
		|| coordinates.getX() > marginX + cols * cellSize - cellSize/2 || coordinates.getY() > marginY + rows * cellSize - cellSize/2) {
		return nullptr;
	}
	// Coordinates are inside the board
	else {
		int x = (int)floor((coordinates.getX() - marginX + cellSize/2) / cellSize);
		int y = (int)floor((coordinates.getY() - marginY + cellSize/2) / cellSize);
		return getBoxAt(x, y);
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