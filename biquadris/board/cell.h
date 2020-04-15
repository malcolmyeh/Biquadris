#ifndef CELL_H
#define CELL_H

#include "../subject/subject.h"
#include "../point/point.h"
#include "../board/board.h"
#include <memory>

// struct Point;
class Point;
class Board;
class Cell : public Subject
{
    bool isBlind = false;
    // std::shared_ptr<Point> point;
    int colour;
    Point point;

public:
    // Cell(std::shared_ptr<Point> point, int colour, std::shared_ptr<Board> board);
    Cell(Point point, int colour, std::shared_ptr<Board> board);
    ~Cell();
    void setColour(int colour);
    int getColour();
    bool isFilled();
    void toggleBlind();
    void drawDisplays() override;
    bool getIsBlind();
    // std::shared_ptr<Point> getPoint();
    Point getPoint();
};

#endif