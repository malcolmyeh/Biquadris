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
    xw->fillRectangle(padding, padding, boardWidth, scoreHeight, Xwindow::Blue);
    xw->fillRectangle(totalWidth - padding - boardWidth, padding, boardWidth, scoreHeight, Xwindow::Red);
    // score text
    xw->drawString(2 * padding, 2 * padding, "Level: ", Xwindow::White);
    xw->drawString(2 * padding, 3 * padding, "Score: ", Xwindow::White);
    xw->drawString(totalWidth - boardWidth, 2 * padding, "Level: ", Xwindow::White);
    xw->drawString(totalWidth - boardWidth, 3 * padding, "Score: ", Xwindow::White);
}

void GraphicsDisplay::initNextBlock()
{
    xw->fillRectangle(padding, totalHeight - nextHeight - padding, boardWidth, nextHeight, Xwindow::Blue);
    xw->fillRectangle(totalWidth - boardWidth - padding, totalHeight - nextHeight - padding, boardWidth, nextHeight, Xwindow::Red);
    xw->drawString((2 * padding), totalHeight - nextHeight, "Next: ", Xwindow::White);
    xw->drawString(totalWidth - boardWidth, totalHeight - nextHeight, "Next: ", Xwindow::White);
}

void GraphicsDisplay::drawCell(Cell &cell)
{
    int x = cell.getPoint()->getX() * cellSize + padding;
    int y = cell.getPoint()->getY() * cellSize + padding + scoreHeight;
    if (cell.getBoardNumber() == 2)
    {
        x += boardWidth + padding;
    }
    if (cell.getIsBlind())
    {
        xw->fillRectangle(x, y, cellSize, cellSize, Xwindow::Brown);
        // maybe make a draw question block function
    }
    else if (cell.isFilled())
    {
        xw->fillRectangle(x, y, cellSize, cellSize, cell.getColour());
    }
    else {
        xw->fillRectangle(x, y, cellSize, cellSize, Xwindow::Black);
    }
}

void GraphicsDisplay::drawString(int x, int y, std::string msg,
                            int colour)
{
    xw->drawString(x, y, msg, colour);
}