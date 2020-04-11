#ifndef BLOCK_H
#define BLOCK_H

#include "../point/point.h"
#include <unordered_set>
#include <vector>
#include "../display/window.h"

class Block
{
protected:
    int level;
    int colour;
    std::vector<Point> points; // the points that the piece is occupying
    std::vector<Point> minRec; // matrix of minimum rectangle
    int recWidth;
    int recHeight;
    Point topLeft;
    Board *board;
public:
    Block(int colour, Board *board, int level);
    bool move(char direction);
    bool rotate(std::string direction);
    void drop();
    bool isPlaced(); //
    bool clearPoint(int row); // get rid of all y = row. return true if block is empty
};

// NOTE: how do we know when a piece is "set"? So that we can release the next one?

#endif