#include "oblock.h"

OBlock::OBlock(char type) : Block{type} {
    std::vector<Point> v = {{0, 2}, {1, 2}, {0, 3}, {1, 3}};
    this->points = v;
    this->recWidth = 2;
    this->recHeight = 2;
}