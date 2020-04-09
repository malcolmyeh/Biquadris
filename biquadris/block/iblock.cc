#include "iblock.h"

IBlock::IBlock(char type) : Block{type} {
    std::vector<Point> v = {{0, 3}, {1, 3}, {2, 3}, {3, 3}};
    this->points = v;
    this->recWidth = 4;
    this->recHeight = 1;
}