#include "mainboard.h"
#include "../display/window.h"
#include "../block/block.h"
#include "../score/score.h"
#include "../point/point.h"
#include "board.h"
#include "cell.h"
#include <memory>
#include <iostream>

////////////////////////////// CONSTRUCTORS //////////////////////////////

MainBoard::MainBoard() : Board{18, 11, Point{0, 3}, 0}, isBlind{false} {}

MainBoard::MainBoard(int boardNumber)
    : Board{18, 11, Point{0, 3}, boardNumber}, isBlind{false} {}

MainBoard::MainBoard(MainBoard *mainBoard)
{
    boardNumber = mainBoard->boardNumber;
    cellGrid = mainBoard->cellGrid;
    displays = mainBoard->displays;
    isBlind = mainBoard->isBlind;
}

////////////////////////////// SETTERS //////////////////////////////

void MainBoard::toggleBlind()
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

void MainBoard::addBlock(std::shared_ptr<Block> block)
{
    blocks.emplace_back(block);
}

void MainBoard::removeBlock()
{
    blocks.back()->drawBlock(Xwindow::White);
    blocks.pop_back();
}

////////////////////////////// BOARD FUNCTIONS //////////////////////////////

bool MainBoard::rowIsFilled(std::vector<Cell> row)
{
    for (auto c : row)
    {
        if (!c.isFilled())
            return false;
    }
    return true;
}

// checks if each row is full, removes the point on the blocks that belong
// on that row, moves all blocks down and updates score based on the rows and
// blocks cleared
int MainBoard::checkRow(std::shared_ptr<Score> score)
{
    int rowsCleared = 0;
    // loop through each row
    for (std::vector<std::vector<Cell>>::reverse_iterator row = cellGrid.rbegin();
         row != cellGrid.rend(); ++row)
    {
        while (rowIsFilled(*row))
        {
            ++rowsCleared;
            // loop through each block
            for (auto block : blocks)
            {
                // if block has point on Y...
                if (block->clearPoint(row->front().getPoint().getY()))
                    score->updateScoreBlock(block->getLevel());
            }
            for (auto block : blocks)
                block->move('D');
            score->updateScoreRow();
        }
    }
    return rowsCleared;
}

void MainBoard::restart()
{
    blocks.clear();
    for (auto r : cellGrid)
    {
        for (auto c : r)
            c.setColour(Xwindow::White);
    }
    refresh();
}