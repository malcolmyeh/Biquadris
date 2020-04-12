#ifndef IBLOCK_H
#define IBLOCK_H

#include "../point/point.h"
#include "block.h"

class IBlock : public Block {
public:
    IBlock(int level);
};

#endif