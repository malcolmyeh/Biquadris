#include "board.h"
#include "../display/window.h"
#include <memory>
#include <iostream>

void Board::clear()
{
    for (auto r : cellGrid)
        r.clear();
    cellGrid.clear();
}

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

void Board::init(int boardNumber)
{
    this->boardNumber = boardNumber;
    for (int r = 0; r < 18; ++r)
    {
        std::vector<Cell> row;
        for (int c = 0; c < 11; ++c)
        {
            std::shared_ptr<Point> point = std::make_shared<Point>(c, r);
            Cell cell(std::make_shared<Point>(c, r), Xwindow::Black, boardNumber);
            for (auto display : displays)
                cell.attach(display);
            cell.drawDisplays();
            row.emplace_back(cell);
        }
        cellGrid.emplace_back(row);
    }
}

void Board::toggleBlind()
{
    for (int r = 15; r > 6; --r)
    {
        for (int c = 8; c > 1; --c)
        {
            cellGrid[r][c].toggleBlind();
            cellGrid[r][c].drawDisplays();
        }
    }
}

void Board::refresh()
{
    for (auto r : cellGrid)
    {
        for (auto c : r)
        {
            c.drawDisplays();
        }
    }
}

void Board::fillCell(int x, int y, int colour)
{
    cellGrid[y][x].setColour(colour);
    cellGrid[y][x].drawDisplays();
}