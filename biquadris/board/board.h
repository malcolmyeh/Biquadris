#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include <memory>
#include "cell.h"

class Cell;
class View;
class Block;
class Score;

class Board
{
    int boardNumber = 0;
    std::vector<std::vector<Cell>> cellGrid;
    std::vector<std::shared_ptr<View>> displays;
    std::vector<std::shared_ptr<Block>> blocks;
    bool isBlind = false;
    bool rowIsFilled(std::vector<Cell> row);

public:
    Board();
    Board(Board *board);
    // ~Board(); // do we need?
    void clear(); // ^
    void setDisplay(std::shared_ptr<View> display);
    void toggleBlind();
    void init(int boardNumber);
    int getBoardNumber();
    void refresh();
    void fillCell(Point point, int colour);
    bool isFilled(Point point);
    friend std::ostream &operator<<(std::ostream &out, const Board &b);
    int checkRow(std::shared_ptr<Score> score);
    void addBlock(std::shared_ptr<Block> block);
};

#endif