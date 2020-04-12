#include "level2.h"

Level2::Level2(std::string file) : Level{2, file} {}

char Level2::getBlockType()
{
    char blockType;
    switch (rand() % 7)
    {
    case 0:
        blockType = 'I';
        break;
    case 1:
        blockType = 'J';
        break;
    case 2:
        blockType = 'L';
        break;
    case 3:
        blockType = 'O';
        break;
    case 4:
        blockType = 'S';
        break;
    case 5:
        blockType = 'T';
        break;
    case 6:
        blockType = 'Z';
        break;
    }
    return blockType;
}