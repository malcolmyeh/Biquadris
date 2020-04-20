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
    Point origin;

    bool isBlind = false;

public:
    Cell(Point point, int colour, int boardNumber, Point origin);
    ~Cell();
    void setColour(int colour);
    int getColour();
    bool isFilled();
    void toggleBlind();
    void drawDisplays() override;
    bool getIsBlind();
    Point getPoint();
    Point getOrigin();
    int getBoardNumber();
};

#endif