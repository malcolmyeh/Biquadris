#ifndef JBLOCK_H
#define JBLOCK_H

#include "../point/point.h"
#include "block.h"

class JBlock : public Block {
public:
    JBlock(int colour, std::shared_ptr<Board> board, int level);
};

#endif