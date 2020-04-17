#ifndef HEAVY_H
#define HEAVY_H

#include "player.h"

class Heavy : public Player
{
protected:
    std::shared_ptr<Player> player;

public:
    Heavy(std::shared_ptr<Player> player, bool isDecorated = false);
    bool moveBlock(char direction) override;
    std::shared_ptr<Player> getPlayer() override;
};

#endif