#ifndef PLAYER_H
#define PLAYER_H

#include <memory>

class Block;

class Score;

class MainBoard;

class NextBlockBoard;

class Board;

class Player
{
protected:
    std::shared_ptr<Block> currentBlock;
    std::shared_ptr<Block> nextBlock;
    std::shared_ptr<Score> score;
    std::shared_ptr<MainBoard> mainBoard;
    std::shared_ptr<NextBlockBoard> nextBlockBoard;
    bool canSpecial = false;
    int level;
    bool isBlind = false;
    bool isLost = false;

public:
    Player(std::shared_ptr<Score> score, std::shared_ptr<MainBoard> mainBoard,
           std::shared_ptr<NextBlockBoard> nextBlockBoard);
    void setCurrentBlock(std::shared_ptr<Block> block);
    void setNextBlock(std::shared_ptr<Block> block);
    virtual bool moveBlock(char direction);
    bool rotateBlock(std::string direction);
    void dropBlock();
    bool getCanSpecial();
    void toggleCanSpecial();
    void checkRow();
    void toggleBlind();
    bool currentPlaced();
    void setLevel(int level);
    std::shared_ptr<Board> getMainBoard();
    bool getIsLost();
};
#endif