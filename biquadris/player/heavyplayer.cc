#include "heavyplayer.h"
#include <iostream>
HeavyPlayer::HeavyPlayer(std::shared_ptr<Player> player, bool isDecorated)
    : PlayerDecorator{player, isDecorated}
{
}

bool HeavyPlayer::moveBlock(char direction, int magnitude)
{
    bool check;
    if (direction == 'L' || direction == 'R')
    {
        check = player->moveBlock(direction, magnitude);
        player->moveBlock('D', 2);
    }
    else if (direction == 'D')
    {
        check = player->moveBlock('D', magnitude + 2);
    }
    return check;
}

std::shared_ptr<Player> HeavyPlayer::getPlayer()
{
    return this->player;
}