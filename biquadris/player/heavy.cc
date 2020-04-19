#include "heavy.h"

Heavy::Heavy(std::shared_ptr<Player> player, bool isDecorated) {
    this->player = player;
    this->isDecorated = isDecorated;
}

bool Heavy::moveBlock(char direction)
{
    bool check = player->moveBlock(direction);
    if (direction == 'L' || direction == 'R')
    {
        player->moveBlock('D');
        player->moveBlock('D');
    }
    return check;
}

std::shared_ptr<Player> Heavy::getPlayer(){
    return this->player;
}