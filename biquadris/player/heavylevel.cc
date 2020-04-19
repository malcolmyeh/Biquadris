// #include "heavylevel.h"

// HeavyLevel::HeavyLevel(std::shared_ptr<Player> player, bool isDecorated)
//     : PlayerDecorator{player, isDecorated} {}

// bool HeavyLevel::moveBlock(char direction, int value)
// {
//     bool check;
//     if (direction == 'L' || direction == 'R')
//     {
//         check = player->moveBlock(direction, value);
//         player->moveBlock('D', 1);
//     }
//     else if (direction == 'D')
//     {
//         check = player->moveBlock('D', value + 1);
//     }

//     return check;
// }

// bool HeavyLevel::rotateBlock(std::string direction){
//     bool check = player->rotateBlock(direction);
//     player->moveBlock('D', 1);
// }

// std::shared_ptr<Player> HeavyLevel::getPlayer()
// {
//     return this->player;
// }