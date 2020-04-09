#include "tblock.h"

TBlock::TBlock(char type) : Block{type} {
    std::vector<Point> v = {{0, 2}, {1, 2}, {2, 2}, {1, 3}};
    this->points = v;
    this->recWidth = 3;
    this->recHeight = 2;
    for (auto a : v)
        this->board.fillCell(a.getX(), a.getY(), 1);
}