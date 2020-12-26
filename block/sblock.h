#ifndef SBLOCK_H
#define SBLOCK_H

#include "../point/point.h"
#include "block.h"

class SBlock : public Block
{
public:
    SBlock(int level);
    void reset() override;
};

#endif