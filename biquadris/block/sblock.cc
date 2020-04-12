#include "sblock.h"

SBlock::SBlock(int level) : Block{Xwindow::Green, level}
{
    std::vector<Point> v = {{1, 2}, {2, 2}, {0, 3}, {1, 3}};
    this->points = v;
    this->recWidth = 3;
    this->recHeight = 2;
    this->topLeft = {0, 2};
    for (int x = 0; x < this->recWidth; ++x)
    {
        for (int y = 0; y < this->recHeight; ++y)
        {
            Point p{this->topLeft.getX() + x, this->topLeft.getY() + y};
            this->minRec.emplace_back(p);
        }
    }
    drawBlock(this->colour);
}