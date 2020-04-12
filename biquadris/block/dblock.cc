#include "dblock.h"

DBlock::DBlock(int colour, Board *board, int level) : Block{colour, board, level} {
    std::vector<Point> v = {{0, 3}};
    this->points = v;
    this->minRec = v;
    this->recWidth = 1;
    this->recHeight = 1;
    this->topLeft = {0, 3};
    for (auto a : v) 
        this->board.fillCell(a.getX(), a.getY(), Xwindow::Brown); // type and blindness and colour and display
}