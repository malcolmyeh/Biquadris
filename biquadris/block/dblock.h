#ifndef DBLOCK_H
#define DBLOCK_H

#include "../point/point.h"

class DBlock : public Block {
public:
    DBlock(char type, Board *board);
}

#endif