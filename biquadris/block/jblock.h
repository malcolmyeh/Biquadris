#ifndef JBLOCK_H
#define JBLOCK_H

#include "../point/point.h"

class JBlock : public Block {
public:
    JBlock(int colour, Board *board, int level);
};

#endif