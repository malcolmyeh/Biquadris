#ifndef CELL_H
#define CELL_H

#include "../subject/subject.h"
#include "../point/point.h"
#include <memory>

struct Point;

class Cell : public Subject
{
    bool isBlind = false;
    std::shared_ptr<Point> point;
    int colour;
    int boardNumber;

public:
    Cell(std::shared_ptr<Point> point, int colour, int boardNumber);
    ~Cell();
    void setColour(int colour);
    int getColour();
    int getBoardNumber();
    bool isFilled();
    void toggleBlind();
    void drawDisplays() override;
    bool getIsBlind();
    std::shared_ptr<Point> getPoint();
};

#endif