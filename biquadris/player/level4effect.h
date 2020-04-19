// #ifndef LEVEL4EFFECT_H
// #define LEVEL4EFFECT_H

// #include "heavylevel.h"

// class Level4Effect : public HeavyLevel
// {
// protected:
//     bool rowCleared = false;
//     int blocksDropped = 0;
//     void checkRow() override;
//     bool getRowCleared();
// }

// #endif


// //checkrow
//     // if (rowsCleared > 0)
//     //     rowCleared = true;



// // bool Player::getRowCleared()
// // {
// //     bool temp = rowCleared;
// //     rowCleared = false; // this will be checked only once per drop
// //     return temp;
// // }


// // bool Player::currentPlaced()
// // {
// //     if (currentBlock->isPlaced() || currentBlock->isEmpty())
// //     {
// //         ++blocksDropped;
// //         level4Effect();
// //         setCurrentBlock(nextBlock);
// //         return true;
// //     }
// //     return false;
// // }

// // // Level 4: If 5 blocks have been dropped without clearing at least one row,
// // // create and drop a Dot Block
// // void Player::level4Effect()
// // {
// //     if (level == 4)
// //     {
// //         if (!getRowCleared() && blocksDropped % 5 == 0)
// //         {
// //             std::shared_ptr<DBlock> dot = std::make_shared<DBlock>(4);
// //             isLost = dot->setMainBoard(mainBoard);
// //             mainBoard->addBlock(dot);
// //             dot->drop();
// //         }
// //     }
// // }