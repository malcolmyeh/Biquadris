#include "cell.h"
// #include "../point/point.h"
#include "../display/window.h"
#include "../display/view.h"

Cell::Cell(std::shared_ptr<Point> point, int colour, int boardNumber)
    : point{point}, colour{colour}, boardNumber{boardNumber} {}
void Cell::setColour(int colour)
{
    this->colour = colour;
}

std::shared_ptr<Point> Cell::getPoint()
{
    return point;
}

int Cell::getBoardNumber()
{
    return boardNumber;
}

Cell::~Cell()
{
}

bool Cell::isFilled()
{
    return this->colour != Xwindow::Black;
}
void Cell::toggleBlind()
{
    this->isBlind = !this->isBlind;
}
void Cell::drawDisplays()
{
    for (auto &display : displays)
        display->drawCell(*this);
}
bool Cell::getIsBlind()
{
    return this->isBlind;
}

int Cell::getColour()
{
    return this->colour;
}