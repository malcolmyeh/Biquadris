#include "level3.h"

Level3::Level3(std::string file) : Level{3, file} {}
Level3::Level3(std::vector<char> sequence)
 : Level{3, sequence} {}

Level3::~Level3() {}

std::shared_ptr<Block> Level3::createBlock()
{
    std::shared_ptr<Block> block;
    if (random)
    {
        switch (rand() % 9)
        {
        case 0:
        case 1:
            block = std::make_shared<SBlock>(levelNumber);
            break;
        case 2:
        case 3:
            block = std::make_shared<ZBlock>(levelNumber);
            break;
        case 4:
            block = std::make_shared<IBlock>(levelNumber);
            break;
        case 5:
            block = std::make_shared<JBlock>(levelNumber);
            break;
        case 6:
            block = std::make_shared<LBlock>(levelNumber);
            break;
        case 7:
            block = std::make_shared<OBlock>(levelNumber);
            break;
        case 8:
            block = std::make_shared<TBlock>(levelNumber);
            break;
        }
    }
    else
    {
        if (sequencePosition >= sequence.size())
        {
            sequencePosition = 0;
        }
        switch (sequence.at(sequencePosition))
        {
        case 'I':
            block = std::make_shared<IBlock>(levelNumber);
            break;
        case 'J':
            block = std::make_shared<JBlock>(levelNumber);
            break;
        case 'L':
            block = std::make_shared<LBlock>(levelNumber);
            break;
        case 'O':
            block = std::make_shared<OBlock>(levelNumber);
            break;
        case 'S':
            block = std::make_shared<SBlock>(levelNumber);
            break;
        case 'Z':
            block = std::make_shared<ZBlock>(levelNumber);
            break;
        case 'T':
            block = std::make_shared<TBlock>(levelNumber);
            break;
        }
        ++sequencePosition;
    }
    return block;
}