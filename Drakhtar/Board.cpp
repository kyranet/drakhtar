// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#include "Board.h"
#include "Unit.h"

Board::Board(Texture *cellTexture, int r, int c, float cs)
    : GameObject(nullptr, Vector2D<int>(0, 0), Vector2D<int>(0, 0)), rows(r), cols(c), cellSize(cs)
{
    // Calculates margins to center the board on screen
    marginX = (WIN_WIDTH - (cs * (cols - 1))) / 2;
    marginY = (WIN_HEIGHT - (cs * (rows - 1))) / 2;

    // Creates the board matrix
    board = new Box **[rows];
    for (int i = 0; i < rows; i++)
    {
        board[i] = new Box *[cols];
    }

    // Fills the board with empty boxes
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            auto pos = Vector2D<int>(static_cast<int>(floor(marginX + j * cs)),
                                     static_cast<int>(floor(marginY + i * cs)));
            auto size = Vector2D<int>(static_cast<int>(floor(cs)),
                                      static_cast<int>(floor(cs)));
            auto box = new Box(cellTexture, pos, size, Vector2D<int>(j, i), nullptr);
            board[i][j] = box;
        }
    }
}

Board::~Board()
{
    if (board != nullptr)
    {
        for (int r = 0; r < rows; r++)
        {
            for (int c = 0; c < cols; c++)
            {
                delete board[r][c];
            }
            delete board[r];
        }
        delete[] board;
        board = nullptr;
    }
    delete cellsMatrix;
}

void Board::render() const
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            if (board[i][j] != nullptr)
            {
                board[i][j]->render();
            }
        }
    }
}

void Board::handleEvents(SDL_Event event)
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            board[i][j]->handleEvents(event);
        }
    }
}

Box *Board::getBoxAt(int x, int y)
{
    return board[y][x];
}

Box *Board::getBoxAtCoordinates(Vector2D<int> coordinates)
{
    // Coordinates are out of the board
    if (coordinates.getX() < marginX - cellSize / 2 ||
        coordinates.getY() < marginY - cellSize / 2 ||
        coordinates.getX() > marginX + cols * cellSize - cellSize / 2 ||
        coordinates.getY() > marginY + rows * cellSize - cellSize / 2)
    {
        return nullptr;
    }
    // Coordinates are inside the board
    else
    {
        int x = static_cast<int>(floor((coordinates.getX() - marginX + cellSize / 2) / cellSize));
        int y = static_cast<int>(floor((coordinates.getY() - marginY + cellSize / 2) / cellSize));
        return getBoxAt(x, y);
    }
}

bool Board::isInRange(Box *from, Box *to, int range)
{
    Vector2D<int> fromCoords = from->getIndex();
    Vector2D<int> toCoords = to->getIndex();

    int distanceX = abs((toCoords.getX() - fromCoords.getX()));
    int distanceY = abs((toCoords.getY() - fromCoords.getY()));
    int totalDistance = distanceX + distanceY;

    return range >= totalDistance;
}

Matrix<int> *Board::getCellsInRange(Box *box, int range)
{
    // Reset the cells matrix
    if (cellsMatrix != nullptr)
    {
        delete cellsMatrix;
    }

    int size = range * 2 + 1;
    int startX = box->getIndex().getX() - range;
    int startY = box->getIndex().getY() - range;
    cellsMatrix = new Matrix<int>(size, size);

    // Fills the array
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            // Current cell is out of the board
            if (j + startX < 0 || i + startY < 0 || j + startX >= cols || i + startY >= rows)
            {
                cellsMatrix->setElement(j, i, outOfBoard);

                // Current cell is out of the movement range
            }
            else if (!isInRange(box, getBoxAt(j + startX, i + startY), range))
            {
                cellsMatrix->setElement(j, i, outOfRange);

                // Current cell is in the board and in range
            }
            else
            {
                Unit *unit = board[i + startY][j + startX]->getContent();

                // Current cell is empty
                if (unit == nullptr)
                {
                    cellsMatrix->setElement(j, i, empty);
                }

                // Current cell is occupied
                else
                {
                    if (unit->getTeam() == box->getContent()->getTeam())
                    {
                        // Ally
                        cellsMatrix->setElement(j, i, ally);
                    }
                    else
                    {
                        // Enemy
                        cellsMatrix->setElement(j, i, enemy);
                    }
                }
            }
        }
    }
    return cellsMatrix;
}

bool Board::isEnemyInRange(Box *box, int range)
{
    cellsMatrix = getCellsInRange(box, range);
    int size = range * 2 + 1;
    bool enemyFound = false;
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            if (cellsMatrix->getElement(i, j) == enemy)
            {
                enemyFound = true;
            }
        }
    }

    return enemyFound;
}

void Board::setTextureToCellsInRange(Box *box, int range, int textInd)
{
    cellsMatrix = getCellsInRange(box, range);
    int size = range * 2 + 1;
    int startX = box->getIndex().getX() - range;
    int startY = box->getIndex().getY() - range;

    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            if (cellsMatrix->getElement(i, j) == empty)
            {
                if (getBoxAt(i + startX, j + startY)->getCurrentTexture() != 1)
                {
                    getBoxAt(i + startX, j + startY)->setCurrentTexture(textInd);
                }
            }
        }
    }
}

void Board::resetCellsToBase()
{
    for (int i = 0; i < cols; i++)
    {
        for (int j = 0; j < rows; j++)
        {
            board[j][i]->setCurrentTexture(Box::base);
        }
    }
}

