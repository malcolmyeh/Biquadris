#include "nextblockboard.h"

#include "../display/window.h"
#include "../block/block.h"
#include <memory>
#include <iostream>

NextBlockBoard::NextBlockBoard() : Board{2, 4, Point{1, 23}, 0} {}

NextBlockBoard::NextBlockBoard(int boardNumber) :
 Board{2, 4, Point{1, 23}, boardNumber} {}

NextBlockBoard::NextBlockBoard(NextBlockBoard *nextBlockBoard)
{
    boardNumber = nextBlockBoard->boardNumber;
    cellGrid = nextBlockBoard->cellGrid;
    displays = nextBlockBoard->displays;
}