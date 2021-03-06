#ifndef BLOCK_H
#define BLOCK_H

#include "../point/point.h"
#include <unordered_set>
#include <vector>
#include "../display/window.h"
#include <utility>
#include "../board/mainboard.h"
#include "../board/nextblockboard.h"
#include "../board/holdblockboard.h"
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
    std::weak_ptr<MainBoard> mainBoard;
    std::weak_ptr<NextBlockBoard> nextBlockBoard;
    std::weak_ptr<HoldBlockBoard> holdBlockBoard;
    int level;
    
    // protected method for the loops at the end of each ctor
public:
    Block(int colour, int level);
    bool move (char direction, int magnitude = 1);
    bool rotate(std::string direction);
    void drop();
    bool isPlaced();
    bool clearPoint(int row); // get rid of all y = row. return true if block is empty
    int getLevel();
    int getColour();
    bool setMainBoard(std::shared_ptr<MainBoard> mainBoard);
    void setNextBlockBoard(std::shared_ptr<NextBlockBoard> nextBlockBoard);
    void setHoldBlockBoard(std::shared_ptr<HoldBlockBoard> holdBlockBoard);
    void drawBlock(int colour);
    bool isEmpty();
    bool isValid(); // checks if any of the Points are already filled, to be called right after
                    // creation before it gets drawn
    std::shared_ptr<MainBoard> getMainBoard();
    std::shared_ptr<NextBlockBoard> getNextBlockBoard();
    std::shared_ptr<HoldBlockBoard> getHoldBlockBoard();

    virtual void reset() = 0; // resets Block to original position and orientation
};

#endif