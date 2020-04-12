#ifndef IBLOCK_H
#define IBLOCK_H

#include "../point/point.h"

class IBlock : public Block {
public:
    IBlock(int colour, Board *board, int level);
};

#endif