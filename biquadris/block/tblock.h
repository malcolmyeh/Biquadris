#ifndef TBLOCK_H
#define TBLOCK_H

#include "../point/point.h"
#include "block.h"

class TBlock : public Block {
public:
    TBlock(int colour, std::shared_ptr<Board> board, int level);
};

#endif