#ifndef ZBLOCK_H
#define ZBLOCK_H

#include "../point/point.h"

class ZBlock : public Block {
public:
    ZBlock(char type, Board *board);
};

#endif