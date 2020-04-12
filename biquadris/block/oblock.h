#ifndef OBLOCK_H
#define OBLOCK_H

#include "../point/point.h"
#include "block.h"

class OBlock : public Block {
public:
    OBlock(int colour, std::shared_ptr<Board> board, int level);
};

#endif