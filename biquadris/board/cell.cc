#include "cell.h"
#include "../display/window.h"
#include "../display/view.h"

////////////////////////////// CONSTRUCTOR //////////////////////////////
Cell::Cell(Point point, int colour, int boardNumber, Point origin)
    : point{point}, colour{colour}, boardNumber{boardNumber}, origin{origin} {}

Cell::~Cell() {}

////////////////////////////// SETTERS //////////////////////////////

void Cell::setColour(int colour) { this->colour = colour; }

void Cell::toggleBlind() { this->isBlind = !this->isBlind; }

////////////////////////////// GETTERS //////////////////////////////

int Cell::getColour() { return this->colour; }

bool Cell::isFilled() { return this->colour != Xwindow::White; }

bool Cell::getIsBlind() { return this->isBlind; }

Point Cell::getPoint() { return point; }

Point Cell::getOrigin() { return this->origin; }

int Cell::getBoardNumber() { return this->boardNumber; }

////////////////////////////// NOTIFY OBSERVERS //////////////////////////////

void Cell::drawDisplays()
{
    for (auto &display : displays)
        display.lock()->drawCell(*this);
}
