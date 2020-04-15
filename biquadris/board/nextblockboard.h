#ifndef NEXTBLOCKBOARD_H
#define NEXTBLOCKBOARD_H
#include "board.h"
#include "../point/point.h"
#include <vector>
#include <memory>

class NextBlockBoard : public Board
{
    int boardNumber = 0;
    std::vector<std::vector<Cell>> cellGrid;
    std::vector<std::shared_ptr<View>> displays;

public:
    NextBlockBoard();
    NextBlockBoard(NextBlockBoard *nextBlockBoard);
};

#endif