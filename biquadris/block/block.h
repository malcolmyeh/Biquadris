#ifndef BLOCK_H
#define BLOCK_H

#include "../point/point.h"
#include <unordered_set>

class Block
{
protected:
    char type;
    std::vector<Point> points; // the points that the piece is occupying
    // Point anchor;
    int recWidth;
    int recHeight;
    Board *board;
public:
    Block(char type, Board *board);
    bool move(char direction);
    bool rotate(char direction);
    bool drop();
}

#endif