#include "dblock.h"
#include "block.h"
#include "../display/window.h"

DBlock::DBlock(int level) : Block{Xwindow::Brown, level} {
    std::vector<Point> v = {{0, 3}};
    this->points = v;
    this->minRec = v;
    this->recWidth = 1;
    this->recHeight = 1;
    this->topLeft = {0, 3};
    drawBlock(this->colour);
}