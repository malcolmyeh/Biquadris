#ifndef VIEW_H
#define VIEW_H

#include "window.h"
#include "../board/cell.h"
#include "../score/score.h"

class Cell; 
class Score;

class View
{

public:
    virtual void drawCell(Cell &cell) = 0;
    virtual void drawScore(Score &score) = 0;
    virtual ~View() = default;
};

#endif
