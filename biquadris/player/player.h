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
    Player(Player *other);
    Player(std::shared_ptr<Player> player);
    Player();

    // Setters
    virtual void setCurrentBlock(std::shared_ptr<Block> block);
    virtual void setNextBlock(std::shared_ptr<Block> block);
    virtual void setHoldBlock();
    void setLevel(int level);
    void toggleCanSpecial();
    void toggleBlind();

    // Getters
    virtual bool hasHoldBlock();
    bool getCanSpecial();
    bool getIsLost();
    bool getIsDecorated();
    bool getRowCleared();
    virtual std::shared_ptr<Block> getCurrentBlock();
    virtual std::shared_ptr<Block> getNextBlock();
    virtual std::shared_ptr<Block> getHoldBlock();
    virtual std::shared_ptr<MainBoard> getMainBoard();
    virtual std::shared_ptr<NextBlockBoard> getNextBlockBoard();
    virtual std::shared_ptr<HoldBlockBoard> getHoldBlockBoard();
    virtual std::shared_ptr<Score> getScore();

    // Block functions
    virtual bool moveBlock(char direction, int magnitude = 1);
    virtual bool rotateBlock(std::string direction);
    virtual void dropBlock();
    virtual void checkRow();
    virtual bool currentPlaced();
    void level4Effect();

    // Undecorate function if Player is Decorator
    virtual std::shared_ptr<Player> getPlayer();
};
#endif