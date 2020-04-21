#ifndef HEAVYPLAYER_H
#define HEAVYPLAYER_H

#include "playerdecorator.h"

// Move left or right will move Block down 2

class HeavyPlayer : public PlayerDecorator
{

public:
    HeavyPlayer(std::shared_ptr<Player> player, bool isDecorated = true);
    bool moveBlock(char direction, int magnitude = 1) override;
    std::shared_ptr<Player> getPlayer() override;
};

#endif
