// #include "level4effect.h"
// #include "../board/mainboard.h"
// #include "../block/block.h"
// #include "../block/dblock.h"
// #include <iostream>
// Level4Effect::Level4Effect(std::shared_ptr<Player> player, bool isDecorated)
//     : PlayerDecorator{player, isDecorated} {
//     }

// void Level4Effect::checkRow()
// {
//     int rowsCleared = getMainBoard()->checkRow(getScore());
//     if (rowsCleared >= 2)
//         canSpecial = true;
//     if (rowsCleared > 0)
//         rowCleared = true;
// }

// bool Level4Effect::currentPlaced()
// {
//     if (getCurrentBlock()->isPlaced() || getCurrentBlock()->isEmpty())
//     {
//         ++blocksDropped;
//         if (!rowCleared && blocksDropped % 5 == 0)
//         {
//             std::shared_ptr<DBlock> dot = std::make_shared<DBlock>(4);
//             isLost = dot->setMainBoard(getMainBoard());
//             getMainBoard()->addBlock(dot);
//             dot->drop();
//         }
//         setCurrentBlock(getNextBlock());
//         return true;
//     }
//     return false;
// }

// void Level4Effect::dropBlock()
// {
//     player->dropBlock();
//     ++blocksDropped;
// }

// bool Level4Effect::rotateBlock(std::string direction){
//     return player->rotateBlock(direction);
// }

// bool Level4Effect::moveBlock(char direction, int magnitude){
//     return player->moveBlock(direction, magnitude);
// }