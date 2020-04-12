#ifndef IBLOCK_H
#define IBLOCK_H

#include "../point/point.h"

class LBlock : public Block {
public:
    LBlock(int colour, Board *board, int level);
};

#endif