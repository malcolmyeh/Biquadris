#ifndef LBLOCK_H
#define LBLOCK_H

#include "../point/point.h"
#include "block.h"

class LBlock : public Block
{
public:
    LBlock(int level);
    void reset() override;
};

#endif