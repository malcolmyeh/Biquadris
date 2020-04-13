#include "zblock.h"

ZBlock::ZBlock(int level) : Block{Xwindow::Red, level} {
    std::vector<Point> v = {{0, 2}, {1, 2}, {1, 3}, {2, 3}};
    this->points = v;
    this->recWidth = 3;
    this->recHeight = 2;
    this->topLeft = {0, 2};
    for (int x = 0; x < this->recWidth; ++x) {
        for (int y = 0; y < this->recHeight; ++y) {
            Point p{this->topLeft.getX() + x, this->topLeft.getY() + y};
            this->minRec.emplace_back(p);
        }
    }
}