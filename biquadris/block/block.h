#ifndef BLOCK_H
#define BLOCK_H

#include "../point/point.h"
#include <unordered_set>

class Block
{
protected:
    char type;
    std::vector<Point> points; // the points that the piece is occupying
    std::vector<Point> minRec; // matrix of minimum rectangle
    int recWidth;
    int recHeight;
    Point topLeft;
    Board *board;
public:
    Block(char type, Board *board);
    bool move(char direction);
    bool rotate(std::string direction);
    bool drop();
};

// NOTE: how do we know when a piece is "set"? So that we can release the next one?

#endif