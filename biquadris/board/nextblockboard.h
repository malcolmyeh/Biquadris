#ifndef NEXTBLOCKBOARD_H
#define NEXTBLOCKBOARD_H
#include "board.h"
#include "../point/point.h"
#include <vector>
#include <memory>

class NextBlockBoard : public Board
{
public:
    // Constructors
    NextBlockBoard();
    NextBlockBoard(int boardNumber);
    NextBlockBoard(NextBlockBoard *nextBlockBoard);
};

#endif