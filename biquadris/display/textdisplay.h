#ifndef TEXTDISPLAY_H
#define TEXTDISPLAY_H

#include "view.h"
#include <iostream>
#include <vector>

class TextDisplay : public View
{
    std::vector<std::vector<char>> charGrid;
    void drawStatic(std::string str, int y);

public:
    TextDisplay();
    void drawCell(Cell &cell) override;
    void drawScore(Score &score) override;
    friend std::ostream &operator<<(std::ostream &out, const TextDisplay &td);
};

#endif