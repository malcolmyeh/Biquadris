#include "cell.h"
#include "../display/window.h"
#include "../display/view.h"

Cell::Cell(std::shared_ptr<Point> point, int colour, std::shared_ptr<Board> board)
    : Subject{board}, point{point}, colour{colour}{}
void Cell::setColour(int colour)
{
    this->colour = colour;
}

std::shared_ptr<Point> Cell::getPoint()
{
    return point;
}

Cell::~Cell()
{
}

bool Cell::isFilled()
{
    return this->colour != Xwindow::White;
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