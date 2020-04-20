#include "cell.h"
#include "../display/window.h"
#include "../display/view.h"

Cell::Cell(Point point, int colour, int boardNumber, Point origin)
    : point{point}, colour{colour}, boardNumber{boardNumber}, origin{origin}
{
}

void Cell::setColour(int colour)
{
    this->colour = colour;
}

Point Cell::getPoint()
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
        display.lock()->drawCell(*this);
}
bool Cell::getIsBlind()
{
    return this->isBlind;
}

int Cell::getColour()
{
    return this->colour;
}

Point Cell::getOrigin()
{
    return this->origin;
}

int Cell::getBoardNumber()
{
    return this->boardNumber;
}