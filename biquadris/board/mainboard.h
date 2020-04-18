#ifndef MAINBOARD_H
#define MAINBOARD_H

#include "board.h"
#include <vector>
#include <memory>

class Block;
class Score;

class MainBoard : public Board
{
    std::vector<std::shared_ptr<Block>> blocks;
    bool isBlind = false;
    bool rowIsFilled(std::vector<Cell> row);

public:
    MainBoard();
    MainBoard(MainBoard *mainBoard);
    void toggleBlind();
    int checkRow(std::shared_ptr<Score> score);
    void addBlock(std::shared_ptr<Block> block);
    void removeBlock();
};

#endif