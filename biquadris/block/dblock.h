#ifndef DBLOCK_H
#define DBLOCK_H

#include "../point/point.h"

class DBlock : public Block {
public:
    DBlock(int colour, Board *board, int level);
};

#endif