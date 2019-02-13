#include "Board.h"

Board::Board(Texture* cellTexture, int r, int c, float cellSize) : GameObject(nullptr, 0, 0, 0, 0) {
	rows = r;
	cols = c;

	// Calcula los márgenes horizontales y verticales
	float marginX = (800 - (cellSize * (cols - 1))) / 2;
	float marginY = (600 - (cellSize * (rows - 1))) / 2;

	// Crea el tablero
	board = new Box**[rows];
	for (int i = 0; i < rows; i++) {
		board[i] = new Box*[cols];
	}

	// Rellena el tablero de cajas vacías
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			vector2d pos = { marginX + j * cellSize, marginY + i * cellSize };
			vector2d size = { cellSize, cellSize };
			board[i][j] = new Box(cellTexture, pos, size, nullptr);
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
