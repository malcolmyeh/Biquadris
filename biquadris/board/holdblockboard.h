#ifndef HOLDBLOCKBOARD_H
#define HOLDBLOCKBOARD_H
#include "board.h"
#include "../point/point.h"
#include <vector>
#include <memory>

class HoldBlockBoard : public Board
{
    std::vector<std::vector<Cell>> cellGrid;
    std::vector<std::shared_ptr<View>> displays;
    std::shared_ptr<Block> block;

public:
    HoldBlockBoard();
    HoldBlockBoard(int boardNumber);
    HoldBlockBoard(HoldBlockBoard *holdBlockBoard);
    void setBlock(std::shared_ptr<Block> block);
};

#endif