#ifndef JBLOCK_H
#define JBLOCK_H

#include "../point/point.h"

class JBlock : public Block {
public:
    JBlock(char type, Board *board);
};

#endif