#ifndef TBLOCK_H
#define TBLOCK_H

#include "../point/point.h"

class TBlock : public Block {
public:
    TBlock(int colour, Board *board, int level);
};

#endif