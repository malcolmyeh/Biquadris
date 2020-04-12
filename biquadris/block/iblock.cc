#include "iblock.h"

IBlock::IBlock(int level) : Block{Xwindow::Cyan, level} {
    std::vector<Point> v = {{0, 3}, {1, 3}, {2, 3}, {3, 3}};
    this->points = v;
    this->recWidth = 4;
    this->recHeight = 1;
    this->topLeft = {0, 3};
    for (int x = 0; x < this->recWidth; ++x) {
        for (int y = 0; y < this->recHeight; ++y) {
            Point p{this->topLeft.getX() + x, this->topLeft.getY() + y};
            this->minRec.emplace_back(p);
        }
    }
    drawBlock(this->colour);
}