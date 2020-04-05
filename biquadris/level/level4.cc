#include "level4.h"

Level4::Level4() : Level{4} {}

void Level4::setRandom(bool b)
{
    random = b;
}

char Level4::getBlockType()
{
    char blockType;
    if (random)
    {
        switch (rand() % 9)
        {
        case 0:
        case 1:
            blockType = 'S';
            break;
        case 2:
        case 3:
            blockType = 'Z';
            break;
        case 4:
            blockType = 'I';
            break;
        case 5:
            blockType = 'J';
            break;
        case 6:
            blockType = 'L';
            break;
        case 7:
            blockType = 'O';
            break;
        case 8:
            blockType = 'T';
            break;
        }
    }
    else
    {
        if (sequencePosition >= sequence.size)
        {
            sequencePosition = 0;
        }
        blockType = sequence.at(sequencePosition);
        ++sequencePosition;
    }
    return blockType;
}