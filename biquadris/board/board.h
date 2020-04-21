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
    // Constructors
    Board();
    Board(int boardNumber);
    Board(int rows, int cols, Point origin, int boardNumber);
    Board(Board *board);
    ~Board();

    // Setters
    void setDisplay(std::shared_ptr<View> display);

    // Getters
    int getBoardNumber();
    Point getOrigin();
    bool isFilled(Point point);

    // Board Functions
    void init(int boardNumber);
    void refresh();
    virtual void restart();
    void fillCell(Point point, int colour);
    friend std::ostream &operator<<(std::ostream &out, const Board &b);
};

#endif