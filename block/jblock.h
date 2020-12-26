#ifndef JBLOCK_H
#define JBLOCK_H

#include "../point/point.h"
#include "block.h"

class JBlock : public Block
{
public:
    JBlock(int level);
    void reset() override;
};

#endif