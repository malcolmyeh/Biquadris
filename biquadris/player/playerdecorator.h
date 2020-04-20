#ifndef PLAYERDECORATOR_H
#define PLAYERDECORATOR_H

#include "player.h"

class PlayerDecorator : public Player
{
protected:
    std::shared_ptr<Player> player;
    bool hasHold = false;

public:
    PlayerDecorator(std::shared_ptr<Player> player, bool isDecorated);
    void setCurrentBlock(std::shared_ptr<Block> block) override;
    void setNextBlock(std::shared_ptr<Block> block) override;
    void setHoldBlock() override;
    void setLevel(int level) override;
    void toggleCanSpecial() override;
    void toggleBlind() override;

    bool hasHoldBlock() override;
    bool getCanSpecial() override;
    bool getIsLost() override;
    bool getIsDecorated() override;
    bool getRowCleared() override;

    std::shared_ptr<Block> getCurrentBlock() override;
    std::shared_ptr<Block> getNextBlock() override;
    std::shared_ptr<Block> getHoldBlock() override;
    std::shared_ptr<MainBoard> getMainBoard() override;
    std::shared_ptr<NextBlockBoard> getNextBlockBoard() override;
    std::shared_ptr<HoldBlockBoard> getHoldBlockBoard() override;
    std::shared_ptr<Score> getScore() override;

    void dropBlock() override;
    int getLevel() override;
    bool moveBlock(char direction, int magnitude = 1) override;
    bool rotateBlock(std::string direction)override;
    void checkRow()override;
    bool currentPlaced()override;
    void level4Effect()override;

    // Undecorate function if Player is Decorator
    std::shared_ptr<Player> getPlayer()override;
};

#endif