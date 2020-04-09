#include "sblock.h"

SBlock::SBlock(char type) : Block{type} {
    std::vector<Point> v = {{1, 2}, {2, 2}, {0, 3}, {1, 3}};
    this->points = v;
    this->recWidth = 3;
    this->recHeight = 2;
}