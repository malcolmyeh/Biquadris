#ifndef PLAYER_H
#define PLAYER_H

#include <memory>

class Block;

class Score;

class Board;

class Player
{
    std::shared_ptr<Block> currentBlock;
    std::shared_ptr<Block> nextBlock;
    std::shared_ptr<Score> score;
    std::shared_ptr<Board> board;
    bool canSpecial = false;
    int level;
    bool isBlind = false;

public:
    Player(std::shared_ptr<Board> board, std::shared_ptr<Score> score);
    
    void setCurrentBlock(std::shared_ptr<Block> block);
    void setNextBlock(std::shared_ptr<Block> block);
    bool moveBlock(char direction);
    bool rotateBlock(std::string direction);
    void dropBlock();
    bool getCanSpecial();
    void toggleCanSpecial();
    void checkRow();
    void toggleBlind();
    bool currentPlaced();
    void setLevel(int level);
    std::shared_ptr<Board> getBoard();
};
#endif