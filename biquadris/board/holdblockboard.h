#ifndef HOLDBLOCKBOARD_H
#define HOLDBLOCKBOARD_H
#include "board.h"
#include "../point/point.h"
#include <vector>
#include <memory>

class HoldBlockBoard : public Board
{
    int boardNumber = 0;
    std::vector<std::vector<Cell>> cellGrid;
    std::vector<std::shared_ptr<View>> displays;

public:
    HoldBlockBoard();
    HoldBlockBoard(HoldBlockBoard *holdBlockBoard);
};

#endif