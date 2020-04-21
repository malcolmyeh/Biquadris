#ifndef VIEW_H
#define VIEW_H

#include "window.h"
#include "../board/cell.h"
#include "../score/score.h"
#include "../message/message.h"

class Cell;
class Score;
class Message;

// Observer Class
class View
{
public:
    // Notify
    virtual void drawCell(Cell &cell) = 0;
    virtual void drawScore(Score &score) = 0;
    virtual void drawMessage(Message &message) = 0;
    virtual void clearMessage(Message &message) = 0;
    virtual ~View() = default;
};

#endif
