#include "tblock.h"

TBlock::TBlock(int level) : Block{Xwindow::Magenta, level}
{
    std::vector<Point> v = {{0, 2}, {1, 2}, {2, 2}, {1, 3}};
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
}

void TBlock::reset()
{
    drawBlock(Xwindow::White);

    std::vector<Point> v = {{0, 2}, {1, 2}, {2, 2}, {1, 3}};
    this->points = v;
    this->recWidth = 3;
    this->recHeight = 2;
    this->topLeft = {0, 2};
    this->minRec.clear();
    for (int x = 0; x < this->recWidth; ++x)
    {
        for (int y = 0; y < this->recHeight; ++y)
        {
            Point p{this->topLeft.getX() + x, this->topLeft.getY() + y};
            this->minRec.emplace_back(p);
        }
    }
}