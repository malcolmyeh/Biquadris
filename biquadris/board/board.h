#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include <memory>
#include "../point/point.h"
#include "cell.h"

class Point;
class Cell;
class View;
class Block;
class Score;

class Board
{

protected:
    std::vector<std::vector<Cell>> cellGrid;
    std::vector<std::shared_ptr<View>> displays;
    int rows;
    int cols;
    Point origin; // Where the Board is located on the Display
    int boardNumber;

public:
    Board();
    Board(int boardNumber);
    Board(int rows, int cols, Point origin, int boardNumber);
    Board(Board *board);
    void clear();
    void setDisplay(std::shared_ptr<View> display);
    void init(int boardNumber);
    int getBoardNumber();
    void refresh();
    void restart();
    void fillCell(Point point, int colour);
    friend std::ostream &operator<<(std::ostream &out, const Board &b);
    Point getOrigin();

    bool isFilled(Point point);
};

#endif