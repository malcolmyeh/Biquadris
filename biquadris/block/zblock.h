#ifndef ZBLOCK_H
#define ZBLOCK_H

#include "../point/point.h"
#include "block.h"

class ZBlock : public Block
{
public:
    ZBlock(int level);
    void reset() override;
};

#endif