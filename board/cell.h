#ifndef CELL_H
#define CELL_H

#include "../subject/subject.h"
#include "../point/point.h"
#include "../board/board.h"
#include <memory>

class Point;
class Board;
class Cell : public Subject
{
    Point point;
    int colour;
    int boardNumber;
    Point origin; // Board offset
    bool isBlind = false;

public:
    // Constructor
    Cell(Point point, int colour, int boardNumber, Point origin);
    ~Cell();

    // Setters
    void setColour(int colour);
    void toggleBlind();

    // Getters
    int getColour();
    bool isFilled();
    bool getIsBlind();
    Point getPoint();
    Point getOrigin();
    int getBoardNumber();

    // Notify Observers
    void drawDisplays() override;
};

#endif