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
    nextHeight = 5 * cellSize;
    padding = cellSize;
    totalWidth = (2 * boardWidth) + (3 * padding);
    totalHeight = scoreHeight + boardHeight + nextHeight + (3 * padding);

    xw = std::make_unique<Xwindow>(totalWidth, totalHeight);

    // initialize area/text that is static
    drawBoardArea();
    drawScoreArea(1);
    drawScoreArea(2);
    drawNextBlockArea();
}

void GraphicsDisplay::drawBoardArea()
{
    drawOutline(padding, padding + scoreHeight, boardWidth, boardHeight);
    drawOutline(2 * padding + boardWidth, padding + scoreHeight, boardWidth, boardHeight);
    for (int i = cellSize; i < boardWidth; i += cellSize)
    {
        xw->drawLine(padding + i, padding + scoreHeight, padding + i,
                     padding + scoreHeight + boardHeight);
        xw->drawLine(2 * padding + boardWidth + i, padding + scoreHeight,
                     2 * padding + boardWidth + i, padding + scoreHeight + boardHeight);
    }
    for (int i = cellSize; i < boardHeight; i += cellSize)
    {
        xw->drawLine(padding, padding + scoreHeight + i, padding + boardWidth,
                     padding + scoreHeight + i);
        xw->drawLine(padding + boardWidth + padding, padding + scoreHeight + i,
                     totalWidth - padding, padding + scoreHeight + i);
    }
}

void GraphicsDisplay::drawScoreArea(int boardNumber)
{
    int x = padding;
    if (boardNumber == 2)
    {
        x = totalWidth - padding - boardWidth;
    }
    xw->fillRectangle(x, padding, boardWidth, scoreHeight, Xwindow::White);
    drawOutline(x, padding, boardWidth, scoreHeight);
    xw->drawString(x + padding, 2 * padding, "Level: ", Xwindow::Black);
    xw->drawString(x + padding, 3 * padding, "Score: ", Xwindow::Black);
}

void GraphicsDisplay::drawNextBlockArea()
{
    drawOutline(padding, totalHeight - nextHeight - 2 * padding, boardWidth, nextHeight);
    drawOutline(totalWidth - boardWidth - padding, totalHeight - nextHeight - 2 * padding,
                boardWidth, nextHeight);
    xw->drawString((2 * padding), totalHeight - nextHeight - padding, "Next: ",
                   Xwindow::Black);
    xw->drawString(totalWidth - boardWidth, totalHeight - nextHeight - padding, "Next: ",
                   Xwindow::Black);
    xw->drawString(2 * padding + boardWidth / 2, totalHeight - nextHeight - padding, "Hold: ",
                   Xwindow::Black);
    xw->drawString(totalWidth - boardWidth / 2, totalHeight - nextHeight - padding, "Hold: ",
                   Xwindow::Black);
}

void GraphicsDisplay::drawCell(Cell &cell)
{
    Point adjusted = cell.getPoint() + cell.getOrigin();
    int x = adjusted.getX() * cellSize + padding;
    int y = adjusted.getY() * cellSize + padding;
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
    xw->fillRectangle(x + gridOffset, y + gridOffset, cellSize - cellBorder,
                      cellSize - cellBorder, colour);
}

void GraphicsDisplay::drawBlindCell(int x, int y)
{
    xw->fillRectangle(x + gridOffset, y + gridOffset, cellSize - cellBorder,
                      cellSize - cellBorder, Xwindow::Black);
}

void GraphicsDisplay::drawScore(Score &score)
{
    int x = padding * 4;
    if (score.getBoardNumber() == 2)
        x += boardWidth + padding;
    drawScoreArea(score.getBoardNumber());
    xw->drawString(x, padding * 2, score.getLevel(), Xwindow::Black);
    xw->drawString(x, padding * 3, score.getScore(), Xwindow::Black);
}

void GraphicsDisplay::drawHighScore(Score &score)
{
    int x1 = padding * 4;
    int x2 = padding;
    if (score.getBoardNumber() == 2)
    {
        x1 += boardWidth + padding;
        x2 = totalWidth - padding - boardWidth;
    }
    xw->fillRectangle(x2, padding, boardWidth/2, scoreHeight, Xwindow::White);
    drawOutline(x2, padding, boardWidth, scoreHeight);
    xw->drawString(x2 + padding, 2 * padding, "HiScr: ", Xwindow::Black);
    xw->drawString(x2 + padding, 3 * padding, "Score: ", Xwindow::Black);

    xw->drawString(x1, padding * 2, score.getHighScore(), Xwindow::Black);
    xw->drawString(x1, padding * 3, score.getScore(), Xwindow::Black);
}

void GraphicsDisplay::drawMessage(Message &message)
{
    int x = 2 * padding + boardWidth / 2;
    int y = 2 * padding;
    if (message.getBoardNumber() == 2)
        x += boardWidth + padding;
    for (unsigned int i = 0; i < message.getText().size(); ++i)
        xw->drawString(x, y + i * cellSize / 2, message.getText()[i], Xwindow::Black);
}

void GraphicsDisplay::clearMessage(Message &message)
{
    int x1 = 2 * padding + boardWidth / 2;
    int x2 = padding;
    if (message.getBoardNumber() == 2)
    {
        x1 += boardWidth + padding;
        x2 += boardWidth + padding;
    }
    xw->fillRectangle(x1, padding, boardWidth / 2, scoreHeight, Xwindow::White);
    drawOutline(x2, padding, boardWidth, scoreHeight);
}