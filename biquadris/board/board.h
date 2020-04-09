#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include <memory>
#include "cell.h"



class View;

class Board {
    int boardNumber;
    std::vector<std::vector<Cell>> cellGrid;

    std::vector<std::shared_ptr<View>> displays;

    bool isBlind = false;
    public:
        // ~Board(); // do we need?
        void clear(); // ^^
        void setDisplay(std::shared_ptr<View> display);
        void toggleBlind();      
        void init(int boardNumber);
        void refresh();
        void fillCell(Point point, int colour);
        bool isFilled(Point point);
        friend std::ostream &operator<<(std::ostream &out, const Board &b);

};

#endif