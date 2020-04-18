#include "holdblockboard.h"

#include "../display/window.h"
#include "../block/block.h"
#include <memory>
#include <iostream>

HoldBlockBoard::HoldBlockBoard() : Board{2, 4, Point{6, 23}} {}

HoldBlockBoard::HoldBlockBoard(HoldBlockBoard *holdBlockBoard)
{
    boardNumber = holdBlockBoard->boardNumber;
    cellGrid = holdBlockBoard->cellGrid;
    displays = holdBlockBoard->displays;
}

void HoldBlockBoard::setBlock(std::shared_ptr<Block> block)
{
    this->block = block;
}
