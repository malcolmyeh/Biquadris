#include "oblock.h"

OBlock::OBlock(char type, Board *board) : Block{type, board} {
    std::vector<Point> v = {{0, 2}, {1, 2}, {0, 3}, {1, 3}};
    this->points = v;
    this->recWidth = 2;
    this->recHeight = 2;
    for (auto a : v)
        this->board.fillCell(a.getX(), a.getY(), 1);
}