#include "graphicsdisplay.h"
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <iostream>
#include <cstdlib>
#include <string>
#include <unistd.h>
#include "window.h"
#include <iostream>


#include "../board/board.h"

GraphicsDisplay::GraphicsDisplay(int cellSize) : cellSize{cellSize}
{
    boardWidth = 11 * cellSize;
    boardHeight = 18 * cellSize;
    scoreHeight = 3 * cellSize;
    nextHeight = 4 * cellSize;
    padding = cellSize;
    totalWidth = (2 * boardWidth) + (3 * padding);
    totalHeight = scoreHeight + boardHeight + nextHeight + (2 * padding);

    xw = std::make_unique<Xwindow>(totalWidth, totalHeight);
    // set font?

    // initialize area/text that is static
    drawScoreArea(1);
    drawScoreArea(2);
    drawNextBlockArea();
}


void GraphicsDisplay::drawScoreArea(int boardNumber){
    int x = padding;
    if (boardNumber == 2){
        x = totalWidth - padding - boardWidth;
    }
    xw->fillRectangle(x, padding, boardWidth, scoreHeight, Xwindow::White);
    drawOutline(x, padding, boardWidth, scoreHeight);
    xw->drawString(x+padding, 2*padding, "Level: ", Xwindow::Black);
    xw->drawString(x+padding, 3*padding, "Score: ", Xwindow::Black);
}

void GraphicsDisplay::drawNextBlockArea()
{
    drawOutline(padding, totalHeight - nextHeight - padding, boardWidth, nextHeight);
    drawOutline(totalWidth - boardWidth - padding, totalHeight - nextHeight - padding, boardWidth, nextHeight);
    xw->drawString((2 * padding), totalHeight - nextHeight, "Next: ", Xwindow::Black);
    xw->drawString(totalWidth - boardWidth, totalHeight - nextHeight, "Next: ", Xwindow::Black);
}

void GraphicsDisplay::drawCell(Cell &cell)
{
    int x = cell.getPoint()->getX() * cellSize + padding;
    int y = cell.getPoint()->getY() * cellSize + padding + scoreHeight;
    if (cell.getBoard()->getBoardNumber() == 2)
        x += boardWidth + padding;
    if (cell.getIsBlind())
        drawBlindCell(x, y);
    else if (cell.isFilled())
        drawNormalCell(x, y, cell.getColour());
    else
        drawNormalCell(x, y, Xwindow::White);
}

void GraphicsDisplay::drawOutline(int x, int y, int width, int height)
{
    xw->drawLine(x, y, x + width, y);
    xw->drawLine(x, y, x, y + height);
    xw->drawLine(x + width, y, x + width, y + height);
    xw->drawLine(x, y + height, x + width, y + height);
}

void GraphicsDisplay::drawNormalCell(int x, int y, int colour)
{
    xw->fillRectangle(x, y, cellSize, cellSize, colour);
    drawOutline(x, y, cellSize, cellSize);
}

void GraphicsDisplay::drawBlindCell(int x, int y)
{
    xw->fillRectangle(x, y, cellSize, cellSize, Xwindow::Black);
}

void GraphicsDisplay::eraseCell(int x, int y)
{
    xw->fillRectangle(x, y, cellSize, cellSize, Xwindow::White);
}

void GraphicsDisplay::drawScore(Score &score)
{
    int x = padding * 4;
    if (score.getBoard()->getBoardNumber() == 2)
        x += boardWidth + padding;
    drawScoreArea(score.getBoard()->getBoardNumber());
    xw->drawString(x, padding * 2, score.getLevel(), Xwindow::Black);
    xw->drawString(x, padding * 3, score.getScore(), Xwindow::Black);
}