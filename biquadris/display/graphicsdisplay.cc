#include "graphicsdisplay.h"
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <iostream>
#include <cstdlib>
#include <string>
#include <unistd.h>
#include "window.h"
#include <iostream>

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
    initScore();
    initNextBlock();
}

void GraphicsDisplay::initScore()
{
    // score area
    drawOutline(padding, padding, boardWidth, scoreHeight);
    drawOutline(totalWidth - padding - boardWidth, padding, boardWidth, scoreHeight);
    // score text
    xw->drawString(2 * padding, 2 * padding, "Level: ", Xwindow::Black);
    xw->drawString(2 * padding, 3 * padding, "Score: ", Xwindow::Black);
    xw->drawString(totalWidth - boardWidth, 2 * padding, "Level: ", Xwindow::Black);
    xw->drawString(totalWidth - boardWidth, 3 * padding, "Score: ", Xwindow::Black);
}

void GraphicsDisplay::initNextBlock()
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
    if (cell.getBoardNumber() == 2)
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

void GraphicsDisplay::drawString(int x, int y, std::string msg,
                                 int colour)
{
    xw->drawString(x, y, msg, colour);
}