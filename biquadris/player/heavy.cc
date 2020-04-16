#include "heavy.h"

Heavy::Heavy(std::shared_ptr<Player> player) : player{player} {}

bool Heavy::moveBlock(char direction)
{
    player->moveBlock(direction);
    if (direction == 'L' || direction == 'R')
    {
        player->moveBlock('D');
        player->moveBlock('D');
    }
}