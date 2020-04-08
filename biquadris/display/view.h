#ifndef VIEW_H
#define VIEW_H

#include "window.h"
#include "../board/cell.h"

class Cell; 

class View
{

public:
    virtual void drawCell(Cell &cell) = 0;
    virtual void drawString(int x, int y, std::string msg,
                            int colour) = 0;
    virtual ~View() = default;
};

#endif
