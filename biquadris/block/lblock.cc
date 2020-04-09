#include "lblock.h"

LBlock::LBlock(char type) : Block{type} {
    std::vector<Point> v = {{2, 2}, {0, 3}, {1, 3}, {2, 3}};
    this->points = v;
    this->recWidth = 3;
    this->recHeight = 2;
}