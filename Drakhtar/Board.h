// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#pragma once

#include "GameObject.h"
#include "Box.h"
#include "Constants.h"
#include "Matrix.h"

class Board : public GameObject
{
 protected:
    int rows, cols;
    float marginX, marginY, cellSize;
    Box ***board;
    Matrix<int> *cellsMatrix = nullptr;

 public:
    Board(Texture *cellTexture, int r, int c, float cellSize);
    virtual ~Board();

    virtual void render() const;
    virtual void handleEvents(SDL_Event event);

    Box *getBoxAt(int x, int y);
    Box *getBoxAtCoordinates(Vector2D<int> coordinates);
    bool isInRange(Box *from, Box *to, int range);
    Matrix<int> *getCellsInRange(Box *box, int range);
    bool isEnemyInRange(Box *box, int range);
    void highlightCellsInRange(Box *box, int range);
    void highlightEnemiesInRange(Box *box, int range);
    void resetCellsToBase();

    const enum objectType {
        outOfBoard,
        outOfRange,
        empty,
        ally,
        enemy
    };
};
