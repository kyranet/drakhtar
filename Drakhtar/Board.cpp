#include "Board.h"

// El constructor calcula la posición de la cuadrícula en función del número de casillas y la centra en la ventana
Board::Board(Texture* cellTexture, int r, int c, float cellSize) : GameObject(cellTexture, (800 - (cellSize * c)) / 2, (600 - (cellSize * r)) / 2, cellSize * c, cellSize * r) {
	rows = r;
	cols = c;

	// Calcula los márgenes horizontales y verticales
	float marginX = (800 - (cellSize * cols)) / 2;
	float marginY = (600 - (cellSize * rows)) / 2;

	// Crea el tablero
	board = new Box**[rows];
	for (int i = 0; i < rows; i++) {
		board[i] = new Box*[cols];
	}

	// Rellena el tablero de cajas vacías
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			vector2d pos = { marginX + j * cellSize, marginY + i * cellSize };
			board[i][j] = new Box(cellTexture, pos, { cellSize, cellSize }, nullptr);
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