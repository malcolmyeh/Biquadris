#ifndef PLAYER_H
#define PLAYER_H

#include <memory>

class Block;
class Score;
class MainBoard;
class NextBlockBoard;
class HoldBlockBoard;
class Board;

class Player
{
protected:
    std::shared_ptr<Block> currentBlock;
    std::shared_ptr<Block> nextBlock;
    std::shared_ptr<Block> holdBlock;
    std::shared_ptr<Score> score;
    std::shared_ptr<MainBoard> mainBoard;
    std::shared_ptr<NextBlockBoard> nextBlockBoard;
    std::shared_ptr<HoldBlockBoard> holdBlockBoard;
    bool canSpecial = false;
    int level;
    bool isBlind = false;
    bool isLost = false;
    bool isDecorated = false; // is decorated by opponent

public:
    Player(std::shared_ptr<Score> score, std::shared_ptr<MainBoard> mainBoard,
           std::shared_ptr<NextBlockBoard> nextBlockBoard,
           std::shared_ptr<HoldBlockBoard> holdBlockBoard);
    Player(std::shared_ptr<Player> player);

    // Setters
    void setCurrentBlock(std::shared_ptr<Block> block);
    void setNextBlock(std::shared_ptr<Block> block);
    void setLevel(int level);
    void setHoldBlock();
    void toggleCanSpecial();
    void toggleBlind();

    // Getters
    bool hasHoldBlock();
    bool getCanSpecial();
    std::shared_ptr<Board> getMainBoard();
    bool getIsLost();
    bool getIsDecorated();

    // Block functions
    virtual bool moveBlock(char direction);
    bool rotateBlock(std::string direction);
    void dropBlock();
    void checkRow();
    bool currentPlaced();

    // Undecorate function if Player is Decorator
    virtual std::shared_ptr<Player> getPlayer();
};
#endif