#ifndef GRAPHICSDISPLAY_H
#define GRAPHICSDISPLAY_H

#include "view.h"
#include <X11/Xlib.h>
#include <iostream>
#include <string>
#include <memory>

class Xwindow;

class GraphicsDisplay : public View
{
    std::unique_ptr<Xwindow> xw;
    int cellSize;
    int boardWidth;
    int boardHeight;
    int scoreHeight;
    int nextHeight;
    int padding;
    int totalWidth;
    int totalHeight;
    int cellBorder = 3;
    int gridOffset = 2;

    void drawBoardArea();
    void drawScoreArea(int boardNumber);
    void drawNextBlockArea();
    void drawOutline(int x, int y, int width, int height);
    void drawNormalCell(int x, int y, int colour);
    void drawBlindCell(int x, int y);

public:

    GraphicsDisplay(int cellSize = 25);
    void drawCell(Cell &cell) override;
    void drawScore(Score &score) override;
    void drawMessage(Message &message) override;
    void clearMessage(Message &message) override;
};

#endif