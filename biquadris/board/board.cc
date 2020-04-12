#include "board.h"
#include "../display/window.h"
#include "../block/block.h"
#include "../score/score.h"
#include <memory>
#include <iostream>

Board::Board() {}

Board::Board(Board *board)
{
    boardNumber = board->boardNumber;
    cellGrid = board->cellGrid;
    displays = board->displays;
    isBlind = board->isBlind;
}

int Board::getBoardNumber()
{
    return boardNumber;
}

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
            Cell cell(std::make_shared<Point>(c, r), Xwindow::Black, std::make_shared<Board>(this));
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

void Board::fillCell(Point point, int colour)
{
    cellGrid[point.getY()][point.getX()].setColour(colour);
    cellGrid[point.getY()][point.getX()].drawDisplays();
}

bool Board::isFilled(Point point)
{
    return cellGrid[point.getY()][point.getX()].isFilled();
}

bool Board::rowIsFilled(std::vector<Cell> row)
{
    for (auto c : row)
    {
        if (!c.isFilled())
            return false;
    }
    return true;
}

int Board::checkRow(std::shared_ptr<Score> score)
{
    int rowsCleared = 0;
    for (auto row = cellGrid.rbegin(); row != cellGrid.rend(); ++row)
    {
         if (rowIsFilled(*row))
        {
            ++rowsCleared;
            for (auto block : blocks){
                if (block->clearPoint(row->front().getPoint()->getY()))
                    score->updateScoreBlock(block->getLevel());
                block->move('D');
            }
            score->updateScoreRow();
            --row;
        }
    }
}

void Board::addBlock(std::shared_ptr<Block> block){
    blocks.emplace_back(block);
}