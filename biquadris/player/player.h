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
    std::shared_ptr<Block> generateBlock(char blockType);

public:
    Player(std::shared_ptr<Board> board, std::shared_ptr<Score> score);
    void setCurrentBlock(char blockType);
    void setNextBlock(char blockType);
    void initBlocks(char blockType1, char blockType2);
    bool moveBlock(char direction);
    bool rotateBlock(char direction);
    void dropBlock();
    bool getCanSpecial();
    void toggleCanSpecial();
    void checkRow();
    void toggleBlind();
    bool currentPlaced();
    void setLevel(int level);
};
#endif