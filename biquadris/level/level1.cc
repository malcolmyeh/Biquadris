#include "level1.h"

Level1::Level1(std::string file) : Level{1, file} {}

char Level1::getBlockType()
{
    char blockType;
    switch (rand() % 12)
    {
    case 0:
    case 1:
        blockType = 'I';
        break;
    case 2:
    case 3:
        blockType = 'J';
        break;
    case 4:
    case 5:
        blockType = 'L';
        break;
    case 6:
    case 7:
        blockType = 'O';
        break;
    case 8:
    case 9:
        blockType = 'T';
        break;
    case 10:
        blockType = 'S';
        break;
    case 11:
        blockType = 'Z';
        break;
    }
    return blockType;
}