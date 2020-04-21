#include "board.h"
#include "cell.h"
#include "../display/window.h"

#include <memory>
#include <iostream>

////////////////////////////// CONSTRUCTOR //////////////////////////////

Board::Board() {}

Board::Board(int boardNumber) : boardNumber{boardNumber} {}

Board::Board(int rows, int cols, Point origin, int boardNumber)
    : rows{rows}, cols{cols}, origin{origin}, boardNumber{boardNumber} {}

Board::Board(Board *board)
{
    boardNumber = board->boardNumber;
    cellGrid = board->cellGrid;
    displays = board->displays;
    rows = board->rows;
    cols = board->cols;
    origin = board->origin;
}

Board::~Board()
{
    for (auto r : cellGrid)
        r.clear();
    cellGrid.clear();
}

////////////////////////////// SETTERS //////////////////////////////

// Links all Cells to given Display
void Board::setDisplay(std::shared_ptr<View> display)
{
    for (unsigned int r = 0; r < cellGrid.size(); ++r)
    {
        for (unsigned int c = 0; c < cellGrid[r].size(); ++c)
        {
            cellGrid[r][c].attach(display);
        }
    }
    displays.emplace_back(display);
}

////////////////////////////// GETTERS //////////////////////////////

int Board::getBoardNumber()
{
    return boardNumber;
}

Point Board::getOrigin()
{
    return this->origin;
}

bool Board::isFilled(Point point)
{
    return cellGrid[point.getY()][point.getX()].isFilled();
}

////////////////////////////// BOARD FUNCTIONS //////////////////////////////

// Initialize Board, creates and attaches Cells to Displays
void Board::init(int boardNumber)
{
    this->boardNumber = boardNumber;
    for (int r = 0; r < rows; ++r)
    {
        std::vector<Cell> row;
        for (int c = 0; c < cols; ++c)
        {
            Cell cell(Point{c, r}, Xwindow::White, boardNumber, origin);
            for (auto display : displays)
                cell.attach(display);
            cell.drawDisplays();
            row.emplace_back(cell);
        }
        cellGrid.emplace_back(row);
    }
}

// Redraws all Cells
void Board::refresh()
{
    for (auto r : cellGrid)
    {
        for (auto c : r)
            c.drawDisplays();
    }
}

void Board::restart()
{
    for (auto r : cellGrid)
    {
        for (auto c : r)
            c.setColour(Xwindow::White);
    }
    refresh();
}

// Fill Cell at given Point
void Board::fillCell(Point point, int colour)
{
    if (cellGrid[point.getY()][point.getX()].getColour() != colour)
        cellGrid[point.getY()][point.getX()]
            .setColour(colour);
    cellGrid[point.getY()][point.getX()].drawDisplays();
}
