#include "iblock.h"

IBlock::IBlock(char type, Board *board) : Block{type, board} {
    std::vector<Point> v = {{0, 3}, {1, 3}, {2, 3}, {3, 3}};
    this->points = v;
    this->recWidth = 4;
    this->recHeight = 1;
    for (auto a : v)
        this->board.fillCell(a.getX(), a.getY(), 1);
}