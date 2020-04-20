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
    std::shared_ptr<Block> getCurrentBlock() override;
    std::shared_ptr<Block> getNextBlock() override;
    std::shared_ptr<Block> getHoldBlock() override;
    std::shared_ptr<MainBoard> getMainBoard() override;
    std::shared_ptr<NextBlockBoard> getNextBlockBoard() override;
    std::shared_ptr<HoldBlockBoard> getHoldBlockBoard() override;
    std::shared_ptr<Score> getScore() override;
    void setCurrentBlock(std::shared_ptr<Block> block) override;
    void setNextBlock(std::shared_ptr<Block> block) override;
    void setHoldBlock() override;
    void dropBlock() override;
};

#endif