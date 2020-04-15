#include "mainboard.h"
#include "../display/window.h"
#include "../block/block.h"
#include "../score/score.h"
#include "../point/point.h"
#include "board.h"
#include "cell.h"
#include <memory>
#include <iostream>

MainBoard::MainBoard() : Board{18, 11, Point{0, 3}}, isBlind{false} {}

MainBoard::MainBoard(MainBoard *mainBoard)
{
    boardNumber = mainBoard->boardNumber;
    cellGrid = mainBoard->cellGrid;
    displays = mainBoard->displays;
    isBlind = mainBoard->isBlind;
}

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

bool MainBoard::rowIsFilled(std::vector<Cell> row)
{
    for (auto c : row)
    {
        if (!c.isFilled())
            return false;
    }
    return true;
}

int MainBoard::checkRow(std::shared_ptr<Score> score)
{
    int rowsCleared = 0;
    for (std::vector<std::vector<Cell>>::reverse_iterator row = cellGrid.rbegin(); row != cellGrid.rend(); ++row)
    {
        while (rowIsFilled(*row))
        {
            ++rowsCleared;
            for (auto block : blocks)
            {
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

void MainBoard::addBlock(std::shared_ptr<Block> block){
    blocks.emplace_back(block);
}