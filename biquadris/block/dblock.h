#ifndef DBLOCK_H
#define DBLOCK_H

#include "../point/point.h"
#include "block.h"

class DBlock : public Block {
public:
    DBlock(int colour, std::shared_ptr<Board> board, int level);
};

#endif