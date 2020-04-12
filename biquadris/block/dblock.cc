#include "dblock.h"
#include "block.h"
#include "../display/window.h"

DBlock::DBlock(int colour, std::shared_ptr<Board> board, int level) : Block{colour, board, level} {
    std::vector<Point> v = {{0, 3}};
    this->points = v;
    this->minRec = v;
    this->recWidth = 1;
    this->recHeight = 1;
    this->topLeft = {0, 3};
    for (auto a : v) 
        this->board->fillCell(a, Xwindow::Brown); // type and blindness and colour and display
}