#ifndef BLOCK_H
#define BLOCK_H

#include "../point/point.h"
#include <unordered_set>
#include <vector>
#include "../display/window.h"
#include <utility>
#include "../board/board.h"
#include <algorithm>

class Block
{
protected:
    int colour;
    std::vector<Point> points; // the points that the piece is occupying
    std::vector<Point> minRec; // matrix of minimum rectangle
    int recWidth;
    int recHeight;
    Point topLeft;
    std::shared_ptr<Board> board;
    int level;
    // protected method for the loops at the end of each ctor
public:
    Block(int colour, int level);
    bool move(char direction); // change the colour
    bool rotate(std::string direction);
    void drop();
    bool isPlaced();          //
    bool clearPoint(int row); // get rid of all y = row. return true if block is empty
    int getLevel();
    void setBoard(std::shared_ptr<Board> board);
    void drawBlock(int colour);
    bool isEmpty();

    /// TESTING ///
    void printCellCoordinates();
    //////////////
};

// NOTE: how do we know when a piece is "set"? So that we can release the next one?

/*

EXTRA CREDIT: MAKE A STASH WHERE YOU CAN SAVE A PIECE

*/

#endif