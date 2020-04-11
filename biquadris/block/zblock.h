#ifndef ZBLOCK_H
#define ZBLOCK_H

#include "../point/point.h"

class ZBlock : public Block {
public:
    ZBlock(int colour, Board *board, int level);
};

#endif