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

public:
    GraphicsDisplay(int cellSize = 25);
    void initScore();
    void initNextBlock();
    void drawCell(Cell &cell) override;
    void drawString(int x, int y, std::string msg,
                    int colour) override;
};

#endif