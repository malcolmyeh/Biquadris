#ifndef OBLOCK_H
#define OBLOCK_H

#include "../point/point.h"

class OBlock : public Block {
public:
    OBlock(int colour, Board *board, int level);
};

#endif