#ifndef HEAVYLEVEL_H
#define HEAVYLEVEL_H

#include "playerdecorator.h"

class HeavyLevel : public PlayerDecorator
{

public:
    HeavyLevel(std::shared_ptr<Player> player, bool isDecorated = false);
    bool moveBlock(char direction, int value) override;
    bool rotateBlock(std::string direction) override;
    std::shared_ptr<Player> getPlayer() override;
};

#endif

// Any Move or Rotate moves Block down 1