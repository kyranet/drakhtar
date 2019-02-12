#include "Board.h"

Board::Board(Texture* cf, int r, int c, int cs) : GameObject(cf, (800 - (cs * c)) / 2, (600 - (cs * r)) / 2, cs * c, cs * r) {
	rows = r;
	cols = c;
	cellSize = cs;
	cellFrame = cf;
	
	// Crea el tablero
	board = new GameObject**[rows];
	for (int i = 0; i < rows; i++) {
		board[i] = new GameObject*[cols];
	}
	
	// Rellena el tablero de nullptrs
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			board[i][j] = nullptr;
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
	int marginX = (800 - (cellSize * cols)) / 2;
	int marginY = (600 - (cellSize * rows)) / 2;
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			cellFrame->render({ marginX + j * cellSize, marginY + i * cellSize, cellSize, cellSize });
			if (board[i][j] != nullptr) {
				board[i][j]->render();
			}
		}
	}
}