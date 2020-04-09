#include "jblock.h"

JBlock::JBlock(char type, Board *board) : Block{type, board} {
    std::vector<Point> v = {{0, 2}, {0, 3}, {1, 3}, {2, 3}};
    this->points = v;
    this->recWidth = 3;
    this->recHeight = 2;
    for (auto a : v)
        this->board.fillCell(a.getX(), a.getY(), 1);
}