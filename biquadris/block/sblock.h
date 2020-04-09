#ifndef SBLOCK_H
#define SBLOCK_H

#include "../point/point.h"

class SBlock : public Block {
public:
    SBlock(char type, Board *board);
};

#endif